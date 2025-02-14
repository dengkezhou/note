#ifndef __JRX_RXA_H__
#define __JRX_RXA_H__

#include <isa-rxa.h>
#include <jrx_base.h>
#include <jrx_core.h>
#include <rxa.h>
#include <instruction.h>

enum DRR {
  dzero    = 0,
  dsp0     = 1,
  dsp1     = 2,
  dmxa     = 3,
  dr0      = 4,
  dr1      = 5,
  dr2      = 6,
  dr3      = 7,
  dr4      = 8,
  dr5      = 9,
  dr6      = 10,
  dr7      = 11,
  dit      = 12,
  dxtmp    = 13,
  dxpool0  = 14,
  dxpool1  = 15,
  dxpool2  = 16,
  dxpool3  = 17,
  dxpool4  = 18,
  dxpool5  = 19,
  dxpool6  = 20,
  dxpool7  = 21,
  dxpool8  = 22,
  dxpool9  = 23,
  dxpool10 = 24,
  dxpool11 = 25,
  dxpool12 = 26,
  dxpool13 = 27,
  dxpool14 = 28,
  dxpool15 = 29,
  dxpool16 = 30,
  dxpool17 = 31,
  df0      = 16,
  df1      = 17,
  df2      = 18,
  df3      = 19,
  de0      = 20,
  de1      = 21,
  de2      = 22,
  de3      = 23,
  da0      = 24,
  da1      = 25,
  da2      = 26,
  da3      = 27,
  dvtmp    = 28,
  dscale   = 29,
};

#define dxpool(n) (dxpool0 + n)

enum { RXA_CONFIG_R, RXA_CONFIG_E_OR, RXA_CONFIG_DATASET, RXA_CONFIG_XPOOL, RXA_CONFIG_GREG_XPOOL, RXA_CONFIG_SCALE };

typedef struct jrx_rxa {
  jrx_data_t data;
  rxa_device_t *drv;
  rxa_cfg_t rdata;
  int literal_pos;
  int literal_end;
  int xpool_start;
  int xpool_end;
  int loop_start;
  int loop_start_t0;
  int load_start;
  int loop_end;
  uint8_t *code;
  int slots[576];
  int mode;
  void *p0, *p1, *p2, *p3;
  jrx_t *sjrx; // for x86 or rv64
  void *sjrxDev;
  bool complete;
  uint64_t xpool[32];
  int xlen;
  ProgramConfiguration_t *pcfg;
	int id;
} jrx_rxa_t;

typedef void (*InstructionGenerator)(jrx_base_t *p1, Instruction_t *, int);
int rxaCipherUpdate(void *dev, int crypto_mode, void *in, int inlen, void *out, int outlen,
                    void *priv);
rxa_device_t *getRXADevice(void *dev);
#endif
