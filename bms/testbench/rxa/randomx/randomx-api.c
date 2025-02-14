#include <blake2/endian.h>
#include <cvector.h>
#include <dataset.h>
#include <jrx_core.h>
//#include <pthread.h>
#include <randomx.h>
#include <rxa.h>
#include <stats-utils.h>
#include <stdatomic.h>
#include <stdio.h>
#include <time.h>
#include <uint256.h>
#include <utility.h>
#include <virtual_machine.h>
#include <malloc.h>
#include <common.h>
#include <div64.h>
#include <randomx-api.h>

static rxa_mining_param_t param = {
	.softAes = true,
	.miningMode = true,
	.jit = true,
	.secure = false,
	.noBatch = false,
	.fastCache = false,
	.rxaMode = true,
	.noncesCount = 3,
	.threadCount = 1,
	.initThreadCount = 1,
	.seedValue = 0,
};

static void rxa_mining_thread(rxa_thread_t *thread, randomx_vm *vm, uint32_t startNonce, uint256_t *result,
          uint32_t noncesCount) {
	rxa_work_t *work = TH(work);
  uint64_t hash[RANDOMX_HASH_SIZE / sizeof(uint64_t)];
  uint256_t hashresult;
  uint8_t blockTemplate[76];
  memcpy(blockTemplate, WK(blob), sizeof(blockTemplate));
  void *noncePtr = blockTemplate + 39;
  int nonce      = startNonce;
	
	if (!work)
		return;

	while (!work->work_id)
		udelay(10);

  if (!PA(noBatch)) {
    store32(noncePtr, nonce);
    randomx_calculate_hash_first(vm, blockTemplate, sizeof(blockTemplate));
  }
  while (nonce < noncesCount) {
		if (TH(quit))
			break;

    if (!PA(noBatch))
      nonce += 1;

    store32(noncePtr, nonce);
    PEOO();
    POKE(pvx, "one nonce");
    (!PA(noBatch) ? randomx_calculate_hash_next : randomx_calculate_hash)(
        vm, blockTemplate, sizeof(blockTemplate), &hash);
    readu256BE((uint8_t *)hash, &hashresult);
		printu256(&hashresult);
    xor256(result, &hashresult, result);
    if (PA(noBatch))
      nonce += 1;
		
		
    PEEK(pvx);
    //perf_flush(1, "one nonce");
  }

  perf_flush(2, "summary");

	TH(inited) = false;
}

extern bool fastCache;
rxa_mining_t *rxa_mining_init(int threadCount, bool fastcache, int noncesCount)
{
	rxa_mining_t *mining = NULL;
	randomx_flags flags;
	char seed[4];

	jrx_register_all();
	
	PA(threadCount) = threadCount;
	PA(fastCache) = fastcache;
	PA(noncesCount) = noncesCount;
	rxaMode = PA(rxaMode);
	fastCache = PA(fastCache);

	mining = malloc(sizeof(rxa_mining_t));
	if (!mining) {
		printf("malloc mining Err\n");
		return NULL;
	}
	memset(mining, 0, sizeof(rxa_mining_t));

	store32(&seed, PA(seedValue));
	MI(vms) = cvector_create(sizeof(randomx_vm_t));

	flags = RANDOMX_FLAG_DEFAULT;
	if (!PA(softAes)) {
		flags |= RANDOMX_FLAG_HARD_AES;
		printf(" - hardware AES mode\n");
	} else
		printf(" - software AES mode\n");

	if (PA(jit)) {
		flags |= RANDOMX_FLAG_JIT;
		printf(" - JIT compiled mode ");
	} else
		printf(" - interpreted mode\n");

	if (PA(miningMode)) {
		flags |= RANDOMX_FLAG_FULL_MEM;
		printf(" - full memory mode (2080 MiB)\n");
		printf("Initializing (%d thread%s", PA(initThreadCount),
				(PA(initThreadCount) > 1) ? "s)" : ")");
	} else
		printf(" - light memory mode (256 MiB)\n");

	if (NULL == selectArgonImpl(flags)) {
		printf("Unsupported Argon2 implementation\n");
		return NULL;
	}

	if (flags & RANDOMX_FLAG_JIT) {
		for (int i = 0; i < PA(threadCount); ++i) {
			MI(mc[i]) = jrx_get_machine(i);
			if (!MI(mc[i])) {
				printf("Get Machine Err\n");
				return NULL;
			}
		}
	}

	MI(cache) = randomx_alloc_cache(MI(mc[0]), flags);
  if (MI(cache) == NULL) {
    printf("randomx_alloc_cache Error\n");
    return NULL;
  }

  randomx_init_cache(MI(cache), &seed, sizeof(seed));
  if (PA(miningMode)) {

    MI(dataset) = randomx_alloc_dataset(MI(cache), flags);
    if (MI(dataset) == NULL) {
      printf("randomx_alloc_dataset Error\n");
      return NULL;
    }

    uint32_t datasetItemCount = randomx_dataset_item_count();
    if (PA(fastCache))
      goto no_init_dataset;

    if (PA(initThreadCount) > 1) {
    } else {
      randomx_init_dataset(MI(dataset), MI(cache), 0, datasetItemCount);
    }

    if (fastCache) {
no_init_dataset:
      memcpy(MI(dataset)->memory, MI(cache)->memory, CacheSize);
    }

    randomx_release_cache(MI(cache));
    MI(cache) = NULL;
  }

  printf("Initializing %d virtual machine(s) ...\n", PA(threadCount));
  for (int i = 0; i < PA(threadCount); ++i) {
    randomx_vm *vm = randomx_create_vm(MI(mc[i]), flags, MI(cache), MI(dataset));
    if (vm == NULL) {
      printf("Cannot create VM\n");
      return NULL;
    }
    cvector_pushback(MI(vms), vm);
  }
	
  return mining;
}

int rxa_mining_start(rxa_mining_t *mining)
{
	int step = PA(noncesCount) / PA(threadCount);
	rxa_thread_t *thread = NULL;
	
	if (!mining)
		return -1;
	
	for (int i = 0; i < PA(threadCount); i++) {
		thread = &MI(thread[i]);

		if (TH(inited))
			continue;

		initu256(NULL, &TH(result));
		TH(inited) = true;
		TH(quit) = false;
		TH(work) = &MI(work);
		TH(id) = i;
		rxa_mining_thread(thread, (randomx_vm_t *)cvector_get_val(MI(vms), i), i * step, &TH(result), step);
	}
  return 0;
}

void rxa_mining_stop(rxa_mining_t *mining)
{
	rxa_thread_t *thread = NULL;

	if (!mining)
		return;
	
	for (int i = 0; i < PA(threadCount); i++) {
		thread = &MI(thread[i]);

		if (!TH(inited))
			continue;

		TH(quit) = true;
	}
}

int rxa_mining_status(rxa_mining_t *mining)
{
	rxa_thread_t *thread = NULL;

	if (!mining)
		return -1;
	
	for (int i = 0; i < PA(threadCount); i++) {
		thread = &MI(thread[i]);

		if (TH(inited))
			return RXA_RUNNING;
	}

	return RXA_FINISH;
}

void rxa_mining_update_work(rxa_mining_t *mining, rxa_work_t *work)
{
	if (!work || !mining)
		return;

	memcpy(&MI(work), work, sizeof(rxa_work_t));
}

int rxa_mining_get_nonces(rxa_mining_t *mining)
{
	return 0;
}

void rxa_mining_exit(rxa_mining_t *mining)
{
	if (!mining)
		return;

	for (int i = 0; i < cvector_length(MI(vms)); ++i)
		randomx_destroy_vm((randomx_vm_t *)cvector_get_val(MI(vms), i));

	if (PA(miningMode))
		randomx_release_dataset(MI(dataset));
	else
		randomx_release_cache(MI(cache));

	for (int i = 0; i < RXA_MAX; i++) {
		if (!MI(mc[i]))
			break;

		jrx_release_machine(MI(mc[i]));
	}
}
