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

#define rx_err(x...)  printf(x)
#define rx_dbg(x...)  printf(x)
#define rx_info(x...) printf(x)

uint8_t blockTemplate_[] = {
    0x07, 0x07, 0xf7, 0xa4, 0xf0, 0xd6, 0x05, 0xb3, 0x03, 0x26, 0x08,
    0x16, 0xba, 0x3f, 0x10, 0x90, 0x2e, 0x1a, 0x14, 0x5a, 0xc5, 0xfa,
    0xd3, 0xaa, 0x3a, 0xf6, 0xea, 0x44, 0xc1, 0x18, 0x69, 0xdc, 0x4f,
    0x85, 0x3f, 0x00, 0x2b, 0x2e, 0xea, 0x00, 0x00, 0x00, 0x00, 0x77,
    0xb2, 0x06, 0xa0, 0x2c, 0xa5, 0xb1, 0xd4, 0xce, 0x6b, 0xbf, 0xdf,
    0x0a, 0xca, 0xc3, 0x8b, 0xde, 0xd3, 0x4d, 0x2d, 0xcd, 0xee, 0xf9,
    0x5c, 0xd2, 0x0c, 0xef, 0xc1, 0x2f, 0x61, 0xd5, 0x61, 0x09};

void printUsage(const char *executable) {
  rx_dbg("Usage: %s [OPTIONS]\n"
         "Supported options:\n"
         "  --help        shows this message\n"
         "  --mine        mining mode: 2080 MiB\n"
         "  --verify      verification mode: 256 MiB\n"
         "  --jit         JIT compiled mode (default: interpreter)\n"
         "  --secure      W^X policy for JIT pages (default: off)\n"
         "  --largePages  use large pages (default: small pages)\n"
         "  --softAes     use software AES (default: hardware AES)\n"
         "  --threads T   use T threads (default: 1)\n"
         "  --affinity A  thread affinity bitmask (default: 0)\n"
         "  --init Q      initialize dataset with Q threads (default: 1)\n"
         "  --nonces N    run N nonces (default: 1000)\n"
         "  --seed S      seed for cache initialization (default: 0)\n"
         "  --ssse3       use optimized Argon2 for SSSE3 CPUs\n"
         "  --avx2        use optimized Argon2 for AVX2 CPUs\n"
         "  --auto        select the best options for the current CPU\n"
         "  --noBatch     calculate hashes one by one (default: batch)\n"
         "  --fastCache	 fast mode to create cache&dataset\n",
         executable);
}

#ifdef TRACE
bool trace = true;
#else
bool trace = false;
#endif

static bool batch = false;
void mine(randomx_vm *vm, atomic_uint *atomicNonce, uint256_t *result,
          uint32_t noncesCount, int thread, int cpuid) {

  uint64_t hash[RANDOMX_HASH_SIZE / sizeof(uint64_t)];
  uint256_t hashresult;
  uint8_t blockTemplate[sizeof(blockTemplate_)];
  memcpy(blockTemplate, blockTemplate_, sizeof(blockTemplate));
  void *noncePtr = blockTemplate + 39;
  int nonce      = 0;
  if (batch) {
    store32(noncePtr, nonce);
    randomx_calculate_hash_first(vm, blockTemplate, sizeof(blockTemplate));
  }
  while (nonce < noncesCount) {
    if (batch) {
#ifdef CONFIG_CACHE
      atomic_fetch_add_explicit(atomicNonce, 1, memory_order_relaxed);
      nonce = atomic_load(atomicNonce);
#else
      nonce += 1;
#endif
    }
    store32(noncePtr, nonce);
    PEOO();
    POKE(pvx, "one nonce");
    (batch ? randomx_calculate_hash_next : randomx_calculate_hash)(
        vm, blockTemplate, sizeof(blockTemplate), &hash);
    readu256BE((uint8_t *)hash, &hashresult);
		printu256(&hashresult);
    xor256(result, &hashresult, result);
    if (!batch) {
#ifdef CONFIG_CACHE
      atomic_fetch_add_explicit(atomicNonce, 1, memory_order_relaxed);
      nonce = atomic_load(atomicNonce);
#else
      nonce += 1;
#endif
    }

    PEEK(pvx);
    //perf_flush(1, "one nonce");
  }

  perf_flush(2, "summary");
}

typedef struct init_mine {
  randomx_vm *vm_;
  atomic_uint *atomicNonce_;
  uint256_t *result_;
  uint32_t noncesCount_;
  int thread_;
  int cpuid_;
} init_mine_t;
#if 0
static void *run_mine(void *arg) {
  init_mine_t *data = (init_mine_t *)arg;

  mine(data->vm_, data->atomicNonce_, data->result_, data->noncesCount_,
       data->thread_, data->cpuid_);
}
#endif
typedef struct init_dataset {
  randomx_dataset_t *dataset_;
  randomx_cache_t *cache_;
  unsigned long startItem_;
  unsigned long itemCount_;
} init_dataset_t;
#if 0
static void *run_dataset(void *arg) {
  init_dataset_t *data = (init_dataset_t *)arg;

  randomx_init_dataset(data->dataset_, data->cache_, data->startItem_,
                       data->itemCount_);
}
#endif
bool fastCache;
bool rxaMode = false;
int rxa_mining_main(int argc, char **argv) {
  bool softAes, miningMode, verificationMode, help, largePages, jit, secure;
  bool ssse3, avx2, autoFlags, noBatch;
  int noncesCount, threadCount, initThreadCount;
  jrx_machine_t *mc[RXA_MAX] = {NULL};
  uint64_t threadAffinity;
  int32_t seedValue;
  unsigned long t0, t1;
  char seed[4];

  jrx_register_all();
  readOption("--softAes", argc, argv, &softAes);
  readOption("--mine", argc, argv, &miningMode);
  readOption("--verify", argc, argv, &verificationMode);
  readIntOption("--threads", argc, argv, &threadCount, 1);
  readUInt64Option("--affinity", argc, argv, &threadAffinity, 0);
  readIntOption("--nonces", argc, argv, &noncesCount, 3);
  readIntOption("--init", argc, argv, &initThreadCount, 1);
  readIntOption("--seed", argc, argv, &seedValue, 0);
  readOption("--largePages", argc, argv, &largePages);
  if (!largePages) {
    readOption("--largepages", argc, argv, &largePages);
  }
  readOption("--jit", argc, argv, &jit);
  readOption("--help", argc, argv, &help);
  readOption("--secure", argc, argv, &secure);
  readOption("--ssse3", argc, argv, &ssse3);
  readOption("--avx2", argc, argv, &avx2);
  readOption("--auto", argc, argv, &autoFlags);
  readOption("--noBatch", argc, argv, &noBatch);
  readOption("--fastCache", argc, argv, &fastCache);
  readOption("--rxa", argc, argv, &rxaMode);

  store32(&seed, seedValue);
  rx_dbg("RandomX benchmark v1.1.8\n");
  if (help) {
    printUsage(argv[0]);
    return 0;
  }
  if (!miningMode && !verificationMode) {
    rx_dbg("Please select either the fast mode (--mine) or the slow mode "
           "(--verify)\n"
           "Run '%s --help' to see all supported options\n",
           argv[0]);
    return 0;
  }
  atomic_uint atomicNonce;
#ifdef CONFIG_CACHE
  atomic_init(&atomicNonce, 0);
#endif
  uint256_t result;
  initu256(NULL, &result);
  cvector vms = cvector_create(sizeof(randomx_vm_t));
  // pthread_t thread[32];
  // init_dataset_t data[32];
  // init_mine_t mdata[32];
  randomx_dataset *dataset = NULL;
  randomx_cache *cache;
  randomx_flags flags;

  if (autoFlags) {
    initThreadCount = 1; // get_nprocs();
    flags           = randomx_get_flags();
  } else {
    flags = RANDOMX_FLAG_DEFAULT;
    if (ssse3) {
      flags |= RANDOMX_FLAG_ARGON2_SSSE3;
    }
    if (avx2) {
      flags |= RANDOMX_FLAG_ARGON2_AVX2;
    }
    if (!softAes) {
      flags |= RANDOMX_FLAG_HARD_AES;
    }
    if (jit) {
      flags |= RANDOMX_FLAG_JIT;
#ifdef RANDOMX_FORCE_SECURE
      flags |= RANDOMX_FLAG_SECURE;
#endif
    }
  }

  if (largePages) {
    flags |= RANDOMX_FLAG_LARGE_PAGES;
  }
  if (miningMode) {
    flags |= RANDOMX_FLAG_FULL_MEM;
  }
#ifndef RANDOMX_FORCE_SECURE
  if (secure) {
    flags |= RANDOMX_FLAG_SECURE;
  }
#endif

  if (flags & RANDOMX_FLAG_ARGON2_AVX2) {
    rx_dbg(" - Argon2 implementation: AVX2\n");
  } else if (flags & RANDOMX_FLAG_ARGON2_SSSE3) {
    rx_dbg(" - Argon2 implementation: SSSE3\n");
  } else {
    rx_dbg(" - Argon2 implementation: reference\n");
  }

  if (flags & RANDOMX_FLAG_FULL_MEM) {
    rx_dbg(" - full memory mode (2080 MiB)\n");
  } else {
    rx_dbg(" - light memory mode (256 MiB)\n");
  }

  if (flags & RANDOMX_FLAG_JIT) {
    rx_dbg(" - JIT compiled mode ");
    if (flags & RANDOMX_FLAG_SECURE) {
      rx_dbg("(secure)");
    }
    rx_dbg("\n");
    ;
  } else {
    rx_dbg(" - interpreted mode\n");
  }

  if (flags & RANDOMX_FLAG_HARD_AES) {
    rx_dbg(" - hardware AES mode\n");
  } else {
    rx_dbg(" - software AES mode\n");
  }

  if (flags & RANDOMX_FLAG_LARGE_PAGES) {
    rx_dbg(" - large pages mode\n");
  } else {
    rx_dbg(" - small pages mode\n");
  }

  if (threadAffinity) {
    // rx_dbg(" - thread affinity (" << mask_to_string(threadAffinity) <<
    // ")\n");
    ;
  }

  if (noBatch) {
    batch = false;
  } else {
    batch = true;
    rx_dbg(" - batch mode\n");
  }

  rx_dbg("Initializing");
  if (miningMode)
    rx_dbg(" (%d thread%s", initThreadCount,
           (initThreadCount > 1) ? "s)" : ")");
  rx_dbg(" ...\n");

  if (NULL == selectArgonImpl(flags)) {
    rx_err("Unsupported Argon2 implementation\n");
    return -1;
  }
  if ((flags & RANDOMX_FLAG_JIT) && !RANDOMX_HAVE_COMPILER) {
    rx_err("JIT compilation is not supported on this platform. Try without "
           "--jit\n");
    return -1;
  }
  if (!(flags & RANDOMX_FLAG_JIT) && RANDOMX_HAVE_COMPILER) {
    rx_dbg("WARNING: You are using the interpreter mode. Use --jit for optimal "
           "performance.\n");
  }
  t0 = get_timer_us(0);

  if (flags & RANDOMX_FLAG_JIT) {
    mc[0] = jrx_get_machine(0);
    if (!mc[0]) {
      rx_err("Get Machine Err\n");
      return -1;
    }
  }

  cache = randomx_alloc_cache(mc[0], flags);
  if (cache == NULL) {
    rx_err("randomx_alloc_cache Error\n");
    return -1;
  }

  randomx_init_cache(cache, &seed, sizeof(seed));
  if (miningMode) {
    dataset = randomx_alloc_dataset(cache, flags);
    if (dataset == NULL) {
      rx_err("randomx_alloc_dataset Error\n");
      return -1;
    }
    uint32_t datasetItemCount = randomx_dataset_item_count();
    if (fastCache)
      goto no_init_dataset;

    if (initThreadCount > 1) {
#if 0
      int perThread      = datasetItemCount / initThreadCount;
      int remainder      = datasetItemCount % initThreadCount;
      uint32_t startItem = 0;
      for (int i = 0; i < initThreadCount; ++i) {
        int count = perThread + (i == initThreadCount - 1 ? remainder : 0);
        data[i].dataset_   = dataset;
        data[i].cache_     = cache;
        data[i].startItem_ = startItem;
        data[i].itemCount_ = count;
        pthread_create(&thread[i], NULL, run_dataset, &data[i]);
        startItem += count;
      }
      for (unsigned i = 0; i < initThreadCount; ++i) {
        pthread_join(thread[i], NULL);
      }
#endif
    } else {
      randomx_init_dataset(dataset, cache, 0, datasetItemCount);
    }

    if (fastCache) {
no_init_dataset:
#ifndef CONFIG_COMPILE_RTL
      memcpy(dataset->memory, cache->memory, CacheSize);
#else
			;
#endif
    }
    randomx_release_cache(cache);
    cache = NULL;
  }

  PEOO();
  t1 = get_timer_us(0);
  rx_dbg("Memory initialized in %f s\n", lldiv((t1 - t0), 1000000));
  rx_dbg("Initializing %d virtual machine(s) ...\n", threadCount);
  for (int i = 0; i < threadCount; ++i) {
		if (i)
			mc[i] = jrx_get_machine(i);
		
    randomx_vm *vm = randomx_create_vm(mc[i], flags, cache, dataset);
    if (vm == NULL) {
      if ((flags & RANDOMX_FLAG_HARD_AES)) {
        rx_err("Cannot create VM with the selected options. Try using "
               "--softAes\n");
        return -1;
      }
      if (largePages) {
        rx_err("Cannot create VM with the selected options. Try without "
               "--largePages\n");
        return -1;
      }
      rx_err("Cannot create VM\n");
      return -1;
    }
    cvector_pushback(vms, vm);
  }

  perf_flush(1, NULL);
  perf_flush(2, NULL);
  PEOO();
  rx_dbg("Running benchmark (%d nonces) ...\n", noncesCount);
  t0 = get_timer_us(0);
  if (threadCount > 1) {
#if 0
    for (unsigned i = 0; i < cvector_length(vms); ++i) {
      int cpuid = -1;
#if 0
			if (threadAffinity)
				cpuid = cpuid_from_mask(threadAffinity, i);
#endif
      mdata[i].vm_          = (randomx_vm_t *)cvector_get_val(vms, i);
      mdata[i].atomicNonce_ = &atomicNonce;
      mdata[i].result_      = &result;
      mdata[i].noncesCount_ = noncesCount;
      mdata[i].thread_      = i;
      mdata[i].cpuid_       = cpuid;
      pthread_create(&thread[i], NULL, run_mine, &data[i]);
    }
    for (unsigned i = 0; i < cvector_length(vms); ++i) {
      pthread_join(thread[i], NULL);
    }
#endif
  } else {
    mine((randomx_vm_t *)cvector_get_val(vms, 0), &atomicNonce, &result,
         noncesCount, 0, -1);
  }

  t1             = get_timer_us(0);
  double elapsed = lldiv(t1 - t0, 1000);
  for (unsigned i = 0; i < cvector_length(vms); ++i)
    randomx_destroy_vm((randomx_vm_t *)cvector_get_val(vms, i));
  if (miningMode)
    randomx_release_dataset(dataset);
  else
    randomx_release_cache(cache);

	for (int i = 0; i < RXA_MAX; i++)
		if (mc[i])
    	jrx_release_machine(mc[i]);
		else
			break;

  rx_dbg("Calculated result: ");
  printu256(&result);
  if (noncesCount == 1000 && seedValue == 0)
    rx_dbg(
        "Reference result:  "
        "10b649a3f15c7c7f88277812f2e74b337a0f20ce909af09199cccb960771cfa1\n");
  if (!miningMode) {
    rx_dbg("Performance: %f ms per hash\n", 1000 * elapsed / noncesCount);
  } else {
    rx_dbg("Performance: %ff hashes per second\n", noncesCount / elapsed);
  }
  return 0;
}
