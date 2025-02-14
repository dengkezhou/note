#ifndef __RANDOMX_API_H__
#define __RANDOMX_API_H__

#include <cvector.h>
#include <uint256.h>
#include <jrx_core.h>

enum {
	RXA_RUNNING,
	RXA_FINISH
};

typedef struct rxa_mining_param {
	bool softAes;
	bool miningMode;
	bool jit;
	bool secure;
	bool noBatch;
	bool fastCache;
	bool rxaMode;
	int noncesCount;
	int threadCount;
	int initThreadCount;
	int32_t seedValue;
} rxa_mining_param_t;

typedef struct rxa_work {
	int work_id;
	char blob[76];
	uint64_t difficult;
	uint32_t e_nonce;
	uint32_t extradifficult;
} rxa_work_t;

typedef struct rxa_thread {
	bool inited;
	uint256_t result;
	rxa_work_t *work;
	int id;
	bool quit;
} rxa_thread_t;

typedef struct rxa_mining {
	cvector vms;
	rxa_work_t work;
	rxa_thread_t thread[RXA_MAX];
	jrx_machine_t *mc[RXA_MAX];
	randomx_cache *cache;
	randomx_dataset *dataset;
} rxa_mining_t;

#define PA(offset)  param.offset
#define MI(offset)  mining->offset
#define TH(offset)  thread->offset
#define WK(offset)  work->offset

rxa_mining_t *rxa_mining_init(int threadCount, bool fastcache, int noncesCount);
void rxa_mining_exit(rxa_mining_t *mining);
void rxa_mining_update_work(rxa_mining_t *mining, rxa_work_t *work);
int rxa_mining_get_nonces(rxa_mining_t *mining);
int rxa_mining_start(rxa_mining_t *mining);
void rxa_mining_stop(rxa_mining_t *mining);
int rxa_mining_status(rxa_mining_t *mining);
#endif
