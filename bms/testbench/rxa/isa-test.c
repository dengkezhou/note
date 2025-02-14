#include <stdio.h>
#include <stdarg.h>
#include <common.h>
#include <rxa.h>
#include <hash.h>
#include <cache.h>
#include "aes1rx1.h"
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <getopt.h>
#include "input2M.h"


#define RXA_ISA_PASS 1
#define RXA_ISA_FAIL -1

#define TEST_CASE(_name, _started)                                             \
  {                                                                            \
    .name = #_name, .type = RXA_ISA_##_name, .param = 0, .started = _started,  \
    .result = 0, .dev = NULL                                                   \
  }

case_cmd_t instrs[] = {
	  TEST_CASE(RXAES1RX4, false), TEST_CASE(RXAES4RX4, false),
		TEST_CASE(RXAES1RX4_HASH, false), TEST_CASE(RXAES1RX4_MUTI, false),
    TEST_CASE(NOP, false),       TEST_CASE(LD, false),
    TEST_CASE(ST, false),        TEST_CASE(VSTQ, false),
    TEST_CASE(VLD, false),       TEST_CASE(VLDQ_XOR, false),
    TEST_CASE(VLD_W, false),     TEST_CASE(VLDQ_W, false),
    TEST_CASE(PRFC, false),      TEST_CASE(XOR, false),
    TEST_CASE(ROR, false),       TEST_CASE(RORI, false),
    TEST_CASE(SWAP, false),      TEST_CASE(ADDSL, false),
    TEST_CASE(ADDI, false),      TEST_CASE(NEG, false),
    TEST_CASE(ADD, false),       TEST_CASE(SUB, false),
    TEST_CASE(MUL, false),       TEST_CASE(MULH, false),
    TEST_CASE(MULHU, false),     TEST_CASE(VADD_D, false),
    TEST_CASE(VSUB_D, false),    TEST_CASE(VMUL_D, false),
    TEST_CASE(VDIV_D, false),    TEST_CASE(VXOR, false),
    TEST_CASE(VSWAP, false),     TEST_CASE(VSQRT_D, false),
    TEST_CASE(VCVT_D_W, false),  TEST_CASE(RXSFRM, false),
    TEST_CASE(RXSSP, false),     TEST_CASE(RXSMXA, false),
    TEST_CASE(RXB, false),       TEST_CASE(BGT, false),
    TEST_CASE(BRK, false),       TEST_CASE(RXBLK2B, false),
};
int instrnums = ARRAY_SIZE(instrs);

uint8_t blake2b_input[] = {
    0x07, 0x07, 0xf7, 0xa4, 0xf0, 0xd6, 0x05, 0xb3, 0x03, 0x26, 0x08,
    0x16, 0xba, 0x3f, 0x10, 0x90, 0x2e, 0x1a, 0x14, 0x5a, 0xc5, 0xfa,
    0xd3, 0xaa, 0x3a, 0xf6, 0xea, 0x44, 0xc1, 0x18, 0x69, 0xdc, 0x4f,
    0x85, 0x3f, 0x00, 0x2b, 0x2e, 0xea, 0x00, 0x00, 0x00, 0x00, 0x77,
    0xb2, 0x06, 0xa0, 0x2c, 0xa5, 0xb1, 0xd4, 0xce, 0x6b, 0xbf, 0xdf,
    0x0a, 0xca, 0xc3, 0x8b, 0xde, 0xd3, 0x4d, 0x2d, 0xcd, 0xee, 0xf9,
    0x5c, 0xd2, 0x0c, 0xef, 0xc1, 0x2f, 0x61, 0xd5, 0x61, 0x09};

#define OFFSCIPHERDECR 0x80
#define OFFSCIPHERIN   0x100
#define OFFSCIPHEROUT  0x600

#define getDescOffset(len) ((len + 15) & (~0xf))
#define isPbuf(id, addr)                                                       \
  ((addr >= ITCS_RXA_IRAM_ADDR(id)) &&                                         \
   (addr <= (ITCS_RXA_IRAM_ADDR(id) + 0x4000)))
#define isScratchpad(id, addr)                                                 \
  ((addr >= ITCS_RXA_DRAM_ADDR(id)) &&                                         \
   (addr <= (ITCS_RXA_DRAM_ADDR(id) + 0x200000)))

// desc addr in pbuf or scrapad memory, so need unsigned long to int
static int getDescAddr(int id, uint32_t addr) {
  if (isPbuf(id, addr))
    return (addr - ITCS_RXA_IRAM_ADDR(id));

  if (isScratchpad(id, addr))
    return (addr - ITCS_RXA_DRAM_ADDR(id) + 0x200000);

  return -1;
}

static int isa_cipherUpdate(rxa_device_t *dev, uint32_t *code, int crypto_mode, const uint8_t *in,
                            int inlen, uint8_t *out, int outlen, void *priv) {
  rxa_cipher_decr_t *decr = (rxa_cipher_decr_t *)(code + OFFSCIPHERDECR / 4);
  uint32_t aes1rstate[]   = {0xd7983aad, 0xcc82db47, 0x9fa856de, 0x92b52c0d,
                           0xace78057, 0xf59e125a, 0x15c7b798, 0x338d996e,
                           0xe8a07ce4, 0x5079506b, 0xae62c7d0, 0x6a770017,
                           0x7e994948, 0x79a10005, 0x07ad828d, 0x630a240c};
  uint32_t aes1rxkey[]    = {0x06890201, 0x90dc56bf, 0x8b24949f, 0xf6fa8389,
                          0xed18f99b, 0xee1043c6, 0x51f4e03c, 0x61b263d1};
  uint32_t aes1rkey[]     = {0xb4f44917, 0xdbb5552b, 0x62716609, 0x6daca553,
                         0x0da1dc4e, 0x1725d378, 0x846a710d, 0x6d7caf07,
                         0x3e20e345, 0xf4c0794f, 0x9f947ec6, 0x3f1262f1,
                         0x49169154, 0x16314c88, 0xb1ba317c, 0x6aef8135};
  uint32_t aes1rmutikey[] = {
      0xb4f44917, 0xdbb5552b, 0x62716609, 0x6daca553, 0x0da1dc4e, 0x1725d378,
      0x846a710d, 0x6d7caf07, 0x3e20e345, 0xf4c0794f, 0x9f947ec6, 0x3f1262f1,
      0x49169154, 0x16314c88, 0xb1ba317c, 0x6aef8135, 0x06890201, 0x90dc56bf,
      0x8b24949f, 0xf6fa8389, 0xed18f99b, 0xee1043c6, 0x51f4e03c, 0x61b263d1};
  uint32_t aes4rkey[] = {
      0x99e5d23f, 0x2f546d2b, 0xd1833ddb, 0x6421aadd, 0xa5dfcde5, 0x06f79d53,
      0xb6913f55, 0xb20e3450, 0x171c02bf, 0x0aa4679f, 0x515e7baf, 0x5c3ed904,
      0xd8ded291, 0xcd673785, 0xe78f5d08, 0x85623763, 0x229effb4, 0x3d518b6d,
      0xe3d6a7a6, 0xb5826f73, 0xb272b7d2, 0xe9024d4e, 0x9c10b3d9, 0xc7566bf3,
      0xf63befa7, 0x2ba9660a, 0xf765a38b, 0xf273c9e7, 0xc0b0762d, 0x0c06d1fd,
      0x915839de, 0x7a7cd609};

  memset(decr, 0, sizeof(rxa_cipher_decr_t));
  /* Common settings */
  decr->crypto_type = crypto_mode;
  decr->keylen      = 0;
  if (crypto_mode == RXA_AES1RX4_MUTI) {
		decr->inaddrl   = getDescAddr(0, (unsigned long)code + OFFSCIPHERIN);
    decr->inlen     = 64;
		memcpy((uint8_t *)code + OFFSCIPHERIN, priv, decr->inlen);
		decr->privaddrl = 0x200000;
    decr->privlen   = inlen;
		memcpy(rxa_get_spad(dev), in, decr->privlen);
	} else if (crypto_mode == RXA_AES1RX4_HASH) {
		decr->inaddrl = 0x200000;
		decr->inlen = inlen;
		memcpy(rxa_get_spad(dev), in, decr->inlen);
  } else {
    decr->inaddrl =
        getDescAddr(0, (unsigned long)code + OFFSCIPHERIN); //(uint64_t)in;
    decr->inlen = inlen;
    memcpy((uint8_t *)code + OFFSCIPHERIN, in, decr->inlen);

    decr->privaddrl = (unsigned long)priv;
    // decr->privlen  = 0;
  }
  decr->outaddrl   = getDescAddr(0, (unsigned long)out);
  decr->outlen     = outlen;
  decr->next_decrl = 0;

  switch (crypto_mode) {
  case RXA_BLAKE2B:
    RXAC(RXA_ISA_RXBLK2B, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_AES1RX4:
    decr->keyaddrl =
        getDescAddr(0, (unsigned long)code + OFFSCIPHERIN +
                           getDescOffset(inlen)); //(uint64_t)aes1rkey;
    decr->keylen = sizeof(aes1rkey);
    memcpy((void *)((unsigned long)code + OFFSCIPHERIN + getDescOffset(inlen)),
           aes1rkey, decr->keylen);
    RXAC(RXA_ISA_RXAES1RX4, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_AES1RX4_HASH:
    decr->keyaddrl   = getDescAddr(0, (unsigned long)code + OFFSCIPHERIN);
    decr->keylen     = sizeof(aes1rxkey);
		memcpy((void *)((unsigned long)code + OFFSCIPHERIN),
				  aes1rxkey, decr->keylen);
		decr->stateaddrl = getDescAddr(0, (unsigned long)code + OFFSCIPHERIN + getDescOffset(decr->keylen));
    decr->statelen   = sizeof(aes1rstate);
		memcpy((void *)((unsigned long)code + OFFSCIPHERIN + getDescOffset(decr->keylen)),
				  aes1rstate, decr->statelen);
    RXAC(RXA_ISA_RXAES1RX4, 0, 0, 0, 1);
		RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_AES1RX4_MUTI:
		decr->keyaddrl   = getDescAddr(0, (unsigned long)code + OFFSCIPHERIN + getDescOffset(decr->inlen));
    decr->keylen     = sizeof(aes1rmutikey);
		memcpy((void *)((unsigned long)code + OFFSCIPHERIN + getDescOffset(decr->inlen)), aes1rmutikey, decr->keylen);
		printf("RXA_AES1RX4_MUTI: %p, %d\n", (void *)((unsigned long)code + OFFSCIPHERIN + getDescOffset(decr->inlen)), decr->keylen);
		decr->stateaddrl = getDescAddr(0, (unsigned long)code + OFFSCIPHERIN + getDescOffset(decr->inlen) + getDescOffset(decr->keylen));
    decr->statelen   = sizeof(aes1rstate);
		memcpy((void *)((unsigned long)code + OFFSCIPHERIN + getDescOffset(decr->inlen) + getDescOffset(decr->keylen)), aes1rstate, decr->statelen);
    RXAC(RXA_ISA_RXAES1RX4, 0, 0, 0, 2);
		RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_AES4RX4:
    decr->keyaddrl =
        getDescAddr(0, (unsigned long)code + OFFSCIPHERIN +
                           getDescOffset(inlen)); //(unsigned long)aes4rkey;
    decr->keylen = sizeof(aes4rkey);
    memcpy((void *)((unsigned long)code + OFFSCIPHERIN + getDescOffset(inlen)),
           aes4rkey, decr->keylen);
    RXAC(RXA_ISA_RXAES4RX4, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  default:
    printf("Not support this cipher mode: %d\n", crypto_mode);
    return -1;
  }

  // set cmd
  RXAC(RXA_ISA_END, 0, 0, 0, 0);
  RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
#if 0
  printf("decr: %p\n", decr);
  printf("crypto_type: %d\n", decr->crypto_type);
  printf("keyaddr: 0x%08lx, len 0x%x\n", decr->keyaddr, decr->keylen);
  printf("stateaddr: 0x%08lx, len 0x%x\n", decr->stateaddr, decr->statelen);
  printf("inaddr: 0x%08lx, len 0x%x\n", decr->inaddr, decr->inlen);
  printf("outaddr: 0x%08lx, len 0x%x\n", decr->outaddr, decr->outlen);
  printf("privaddr: 0x%08lx, len 0x%x\n", decr->privaddr, decr->privlen);
  printf("next_decr: 0x%08lx\n", decr->next_decr);
#endif
  return 0;
}

int rxa_isa_test_prepare(case_cmd_t *cmd) {
  uint64_t dbg[2] = {0};
  uint32_t *code;
  rxa_device_t *dev = cmd->dev;

  if (!cmd)
    return -1;

  rxa_set_privdata(dev, cmd);
  // get program addr
  code = rxa_get_code(dev);
  switch (cmd->type) {
  case RXA_ISA_LD: {
    uint64_t *sram = rxa_get_sram(dev);
    uint64_t *spad = rxa_get_spad(dev);

    *(++sram) = 0x1234567812345678;
    *(++spad) = 0x8765432187654321;
    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SRAM, 8 >> 3);
    RXAC(RXA_ISA_LD, x2, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_ST: {
    uint64_t *spad = rxa_get_spad(dev);
    *(++spad)      = 0x1234567812345678;
    *(++spad)      = 0x8765432187654321;
    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_ST, x0, x1, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VLD: {
    uint64_t *spad = rxa_get_spad(dev);

    spad++;
    *(++spad) = 0x8765432187654321;
    *(++spad) = 0x1234567812345678;
    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VLDQ_XOR: {
    uint64_t *spad = rxa_get_spad(dev);
    int i;
    spad++;
    // set v1~v4
    for (i = 0; i < 4; i++) {
      *(++spad) = 0x1111111111111111 << i;
      *(++spad) = 0x1111111111111111 << i;
    }
    // set spad data
    for (i = 0; i < 4; i++) {
      *(++spad) = 0x1234567812345678 + i;
      *(++spad) = 0x8765432187654321 + i;
    }
    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VLD, v2, x0, RXAI_OFFS_SPAD, 32 >> 3);
    RXAC(RXA_ISA_VLD, v3, x0, RXAI_OFFS_SPAD, 48 >> 3);
    RXAC(RXA_ISA_VLD, v4, x0, RXAI_OFFS_SPAD, 64 >> 3);
    RXAC(RXA_ISA_VLDQ_XOR, v1, x0, RXAI_OFFS_SPAD, 80 >> 3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VSTQ: {
    // VSTQ must 128bit align
    uint64_t *spad = rxa_get_spad(dev);
    int i          = 0;

    spad++;
    for (i = 0; i < 4; i++)
      *(++spad) = 0x1111111111111111 << i;

    for (i = 0; i < 4; i++)
      *(++spad) = 0x8888888888888888 >> i;

    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VLD, v2, x0, RXAI_OFFS_SPAD, 32 >> 3);
    RXAC(RXA_ISA_VSTQ, x0, v1, RXAI_OFFS_SPAD, 48 >> 3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VLD_W: {
    uint64_t *spad = rxa_get_spad(dev);

    *(++spad) = 0x8765432112345678;

    RXAC(RXA_ISA_VLD_W, v2, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VLDQ_W: {
    uint64_t *spad = rxa_get_spad(dev);

    spad++;
    for (int i = 0; i < 4; i++)
      *(++spad) = 0x1111111111111111 << i;

    RXAC(RXA_ISA_VLDQ_W, v2, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_PRFC: {
    uint64_t *ddr = rxa_get_ddr(dev);
    printf("ddr %p\n", ddr);
    ddr += 8;
    printf("ddr1 %p\n", ddr);
    for (int i = 0; i < 8; i++)
      *(ddr++) = 0x1111111111111111 << (i % 4);
#ifdef CONFIG_CACHE
    itcs_dcache_flush();
    printf("itcs_dcache_flush\n");
#endif
    RXAC(RXA_ISA_PRFC, x0, x0, 31, 64 >> 6);
    RXAC(RXA_ISA_WPRFC, 0, 0, 0, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_XOR: {
    uint64_t *spad = rxa_get_spad(dev);

    *(++spad) = 0x8765432112345678;
    *(++spad) = 0x8765432187654321;

    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x2, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x3, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x4, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_XOR, x2, x1, RXAI_RS_FULL, 0);
    RXAC(RXA_ISA_XOR, x3, x1, RXAI_RS_LO32, 0);
    RXAC(RXA_ISA_XOR, x4, x1, RXAI_RS_HI32, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_ROR:
    dbg[0] = 0x1234567812345678;
    rxa_dbg_writeq(dev, x1, dbg);
    rxa_dbg_writeq(dev, x3, dbg);
    dbg[0] = 0x6;
    rxa_dbg_writeq(dev, x2, dbg);

    RXAC(RXA_ISA_ROR, x1, x2, RXAI_R_LEFT, 0);
    RXAC(RXA_ISA_ROR, x3, x2, RXAI_R_RIGHT, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_ISA_RORI:
    dbg[0] = 0x1234567812345678;
    rxa_dbg_writeq(dev, x1, dbg);

    RXAC(RXA_ISA_RORI, x1, x0, 0, 6);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_ISA_SWAP:
    dbg[0] = 0x1234567812345678;
    rxa_dbg_writeq(dev, x1, dbg);
    dbg[0] = 0x8765432187654321;
    rxa_dbg_writeq(dev, x2, dbg);

    RXAC(RXA_ISA_SWAP, x1, x2, 0, 6);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_ISA_ADDSL: {
    uint64_t *spad = rxa_get_spad(dev);

    *(++spad) = 0x1111111111111111;
    *(++spad) = 0x2222222211111111;

    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x2, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x3, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x4, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_ADDSL, x2, x1, RXAI_RS_FULL, 6);
    RXAC(RXA_ISA_ADDSL, x3, x1, RXAI_RS_LO32, 6);
    RXAC(RXA_ISA_ADDSL, x4, x1, RXAI_RS_HI32, 6);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_ADDI:
    dbg[0] = 0x1111111111111111;
    rxa_dbg_writeq(dev, x1, dbg);
    dbg[0] = 0x2222222222222222;
    rxa_dbg_writeq(dev, x2, dbg);

    RXAC(RXA_ISA_ADDI, x2, x1, 0x1eef, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_ISA_SUB: {
    uint64_t *spad = rxa_get_spad(dev);

    *(++spad) = 0x3333333333333333;
    *(++spad) = 0x2222222211111111;

    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x2, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x3, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x4, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_SUB, x2, x1, RXAI_RS_FULL, x2);
    RXAC(RXA_ISA_SUB, x3, x1, RXAI_RS_LO32, x3);
    RXAC(RXA_ISA_SUB, x4, x1, RXAI_RS_HI32, x4);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_NEG:
    dbg[0] = 0x1111111111111111;
    rxa_dbg_writeq(dev, x1, dbg);

    RXAC(RXA_ISA_NEG, x1, x0, 0, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_ISA_MUL: {
    uint64_t *spad = rxa_get_spad(dev);

    *(++spad) = 0xffffffffffffffff;
    *(++spad) = 0xf222222211111111;

    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x2, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x3, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x4, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_MUL, x2, x1, RXAI_RS_FULL, x2);
    RXAC(RXA_ISA_MUL, x3, x1, RXAI_RS_LO32, x3);
    RXAC(RXA_ISA_MUL, x4, x1, RXAI_RS_HI32, x4);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_MULH:
    dbg[0] = 0xffffffffffffffff;
    rxa_dbg_writeq(dev, x1, dbg);
    dbg[0] = 0xf111111111111111;
    rxa_dbg_writeq(dev, x2, dbg);

    RXAC(RXA_ISA_MULH, x2, x1, 0, x2);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    break;
  case RXA_ISA_MULHU:
    dbg[0] = 0xffffffffffffffff;
    rxa_dbg_writeq(dev, x1, dbg);
    dbg[0] = 0xf111111111111111;
    rxa_dbg_writeq(dev, x2, dbg);

    RXAC(RXA_ISA_MULHU, x2, x1, 0, x2);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_ISA_VXOR: {
    uint64_t *spad = rxa_get_spad(dev);

    spad++;
    for (int i = 0; i < 4; i++)
      *(++spad) = 0x1111111111111111 << i;

    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VLD, v2, x0, RXAI_OFFS_SPAD, 32 >> 3);
    RXAC(RXA_ISA_VXOR, v2, v1, 0, v2);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VSWAP: {
    uint64_t *spad = rxa_get_spad(dev);

    spad++;
    for (int i = 0; i < 2; i++)
      *(++spad) = 0x1111111111111111 << i;

    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VSWAP, v1, 0, 0, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VADD_D: {
    uint64_t *spad = rxa_get_spad(dev);

    spad++;
    for (int i = 0; i < 4; i++)
      *(++spad) = 0x1111111111111111 << i;

    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VLD, v2, x0, RXAI_OFFS_SPAD, 32 >> 3);
    RXAC(RXA_ISA_VADD_D, v2, v1, 0, v2);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VSUB_D: {
    uint64_t *spad = rxa_get_spad(dev);

    spad++;
    for (int i = 0; i < 4; i++)
      *(++spad) = 0x1111111111111111 << i;

    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VLD, v2, x0, RXAI_OFFS_SPAD, 32 >> 3);
    RXAC(RXA_ISA_VSUB_D, v2, v1, 0, v2);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VMUL_D: {
    uint64_t *spad = rxa_get_spad(dev);

    spad++;
    for (int i = 0; i < 4; i++)
      *(++spad) = 0x1111111111111111 << i;

    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VLD, v2, x0, RXAI_OFFS_SPAD, 32 >> 3);
    RXAC(RXA_ISA_VMUL_D, v2, v1, 0, v2);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VDIV_D: {
    uint64_t *spad = rxa_get_spad(dev);

    spad++;
    for (int i = 0; i < 4; i++)
      *(++spad) = 0x1111111111111111 << i;

    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VLD, v2, x0, RXAI_OFFS_SPAD, 32 >> 3);
    RXAC(RXA_ISA_VDIV_D, v2, v1, 0, v2);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VSQRT_D: {
    uint64_t *spad = rxa_get_spad(dev);

    spad++;
    for (int i = 0; i < 2; i++)
      *(++spad) = 0x1111111111111111 << i;

    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VSQRT_D, v1, v1, 0, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_VCVT_D_W: {
    uint64_t *spad = rxa_get_spad(dev);

    *(++spad) = 0x1111111122222222;

    RXAC(RXA_ISA_VLD_W, v1, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_VCVT_D_W, v2, v1, 0, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_RXSFRM: {
    uint64_t *spad = rxa_get_spad(dev);

    dbg[0] = 0x1;
    rxa_dbg_writeq(dev, x1, dbg);

    spad++;
    for (int i = 0; i < 2; i++)
      *(++spad) = 0x1111111111111111 << i;

    RXAC(RXA_ISA_VLD, v1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VSQRT_D, v1, v1, 0, 0);
    RXAC(RXA_ISA_RXSFRM, 0, x1, 0, 0);
    RXAC(RXA_ISA_VLD, v2, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_VSQRT_D, v2, v2, 0, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_RXSSP: {
    uint64_t *spad = rxa_get_spad(dev);
    char cfgr[4]   = {4, 6, 8, 10};
    rxa_set_cfg_r(dev, cfgr);
    for (int i = 0; i < 2; i++)
      *(++spad) = 0x1111111111111111 << i;
    *(++spad) = 0x1234567887654321;

    RXAC(RXA_ISA_LD, x4, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x6, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 24 >> 3);
    RXAC(RXA_ISA_RXSSP, x2, x1, x3, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_RXSMXA: {
    uint64_t *spad = rxa_get_spad(dev);
    char cfgr[4]   = {4, 6, 8, 10};

    rxa_set_cfg_r(dev, cfgr);
    for (int i = 0; i < 2; i++)
      *(++spad) = 0x1111111111111111 << i;
    *(++spad) = 0x1234567887654321;

    RXAC(RXA_ISA_LD, x8, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x10, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 24 >> 3);
    RXAC(RXA_ISA_RXSMXA, x1, 0, 0, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_RXB: {
    uint64_t *spad = rxa_get_spad(dev);

    *(++spad) = 0x1111111111100000;
    *(++spad) = 0x1234567800000000;

    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x2, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x3, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_RXB, x2, x1, (0 | (2 << 1)), 8 >> 2);
    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_RXB, x2, x1, (1 | (2 << 1)), 8 >> 2);
    RXAC(RXA_ISA_LD, x3, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_BGT: {
    uint64_t *spad = rxa_get_spad(dev);

    *(++spad) = 0x22222222;
    *(++spad) = 0x3333333311111111;

    RXAC(RXA_ISA_LD, x1, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_LD, x2, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x3, x0, RXAI_OFFS_SPAD, 16 >> 3);
    RXAC(RXA_ISA_LD, x4, x0, RXAI_OFFS_SPAD, 16 >> 3);
    // jump 8
    RXAC(RXA_ISA_BGT, x1, x2, (RXAI_RS_FULL | (2 << 2)), 0);
    RXAC(RXA_ISA_LD, x2, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_BGT, x1, x3, (RXAI_RS_HI32 | (2 << 2)), 0);
    RXAC(RXA_ISA_LD, x3, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_BGT, x1, x4, (RXAI_RS_LO32 | (2 << 2)), 0);
    RXAC(RXA_ISA_LD, x4, x0, RXAI_OFFS_SPAD, 8 >> 3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
  } break;
  case RXA_ISA_BRK:
    break;
  case RXA_ISA_NOP:
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_ISA_ADD:
    dbg[0] = 0x1111111111111111;
    rxa_dbg_writeq(dev, x1, dbg);
    dbg[0] = 0x2222222222222222;
    rxa_dbg_writeq(dev, x2, dbg);
    dbg[0] = 0x3333333333333333;
    rxa_dbg_writeq(dev, x3, dbg);

    RXAC(RXA_ISA_ADD, x1, x2, 0, x3);
    RXAC(RXA_ISA_END, 0, 0, 0, 0);
    RXAC(RXA_ISA_NOP, 0, 0, 0, 0);
    break;
  case RXA_ISA_RXBLK2B:
    isa_cipherUpdate(dev, code, RXA_BLAKE2B, blake2b_input,
                     ARRAY_SIZE(blake2b_input), (uint8_t *)code + OFFSCIPHEROUT,
                     64, NULL);
    rxa_set_cipher_offs(dev, rxa_get_code_offs(dev) + OFFSCIPHERDECR);
    break;
	/* RXA_ISA_RXAES1RX4_HASH, RXA_ISA_RXAES1RX4_MUTI */
  case RXA_ISA_RXAES1RX4: {
    uint64_t input[8] = {0xb83e2ba259125651, 0x2c57fa674095e608,
                         0x72232e4c6bdeb9d2, 0x2ccc119d298cd97f,
                         0xb8207b1ebc72a4ee, 0x55f004a65316e74a,
                         0x8ab66225da696282, 0xaf25506e100f88c6}; 
		uint64_t priv[8] = {0x8c7ea1cdc1a4e1bb, 0x77aef93802424537, 
			                  0xe240052a5172854e, 0xe95acbecfb8745ec, 
												0xbad8d77d55558edc, 0xe689c33cb5ca0921, 
												0xd4bc6cfe4db610e9, 0xde6b421554caf4e1};
		if (!cmd->param)		
    	isa_cipherUpdate(dev, code, RXA_AES1RX4, (uint8_t *)input, 64,
                       rxa_get_spad(dev), 0x200000, NULL);
		else if (cmd->param == 1) // input2M
			isa_cipherUpdate(dev, code, RXA_AES1RX4_HASH, (uint8_t *)NULL, 0x200000, (uint8_t *)code + OFFSCIPHEROUT, 64, NULL);
		else if (cmd->param == 2)
			isa_cipherUpdate(dev, code, RXA_AES1RX4_MUTI, (uint8_t *)NULL, 0x200000, (uint8_t *)code + OFFSCIPHEROUT, 64, priv);

    rxa_set_cipher_offs(dev, rxa_get_code_offs(dev) + OFFSCIPHERDECR);
  } break;
  case RXA_ISA_RXAES4RX4: {
    uint64_t input[8] = {0x25a4424b727ab1b2, 0xb53a90c9f56f1bc9,
                         0xe8027504fed70bc4, 0x70152fd1377f234d,
                         0x85b20930f22cf15b, 0xae1f977a841fdb02,
                         0x8a756cec33c0d189, 0x2fd5f1128e94c44};
    isa_cipherUpdate(dev, code, RXA_AES4RX4, (uint8_t *)input, 64,
                     (uint8_t *)code + OFFSCIPHEROUT, 2176, NULL);
    rxa_set_cipher_offs(dev, rxa_get_code_offs(dev) + OFFSCIPHERDECR);
  } break;
  default:
    printf("Do not support this case: %s\n", cmd->name);
    return -1;
  }
	// for sync is
	asm("sync.is");
  return 0;
}

bool check_reg(rxa_device_t *dev, int reg, uint64_t cval0, uint64_t cval1) {
  uint64_t dbg[2] = {0};

  if (limits(x0, x31)) {
    rxa_dbg_readq(dev, reg, dbg);
    printf("0x%lx == 0x%lx\n", dbg[0], cval0);
    return (cval0 == dbg[0]);
  } else if (limits(v0, v31)) {
    rxa_dbg_readq(dev, reg, dbg);
    printf("%d: 0x%lx%lx\n", reg, dbg[1], dbg[0]);
    return (cval0 == dbg[0] && cval1 == dbg[1]);
  }
  return false;
}

bool check_sram(rxa_device_t *dev, int mode, int offs, uint64_t cval) {
  if (mode == RXAI_OFFS_SRAM) {
    return (*((uint64_t *)rxa_get_sram(dev) + (offs >> 3)) == cval);
  } else {
    return (*((uint64_t *)rxa_get_spad(dev) + (offs >> 3)) == cval);
  }
}

int rxa_isa_test_verfication(case_cmd_t *cmd) {
  rxa_device_t *dev = cmd->dev;
  if (!cmd)
    return -1;

  switch (cmd->type) {
  case RXA_ISA_NOP:
    cmd->result = RXA_ISA_PASS;
    break;
  case RXA_ISA_LD:
    if (check_reg(dev, x1, 0x1234567812345678, 0) &&
        check_reg(dev, x2, 0x8765432187654321, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_ST: {
    if (check_sram(dev, RXAI_OFFS_SPAD, 16, 0x1234567812345678))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
  } break;
  case RXA_ISA_VLD:
    if (check_reg(dev, v1, 0x8765432187654321, 0x1234567812345678))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VLDQ_XOR:
    if (check_reg(dev, v1, 0x325476903254769, 0x9674523096745230) &&
        check_reg(dev, v2, 0x3016745A3016745B, 0xA5476103A5476100) &&
        check_reg(dev, v3, 0x5670123C5670123E, 0xC3210765C3210767) &&
        check_reg(dev, v4, 0x9ABCDEF09ABCDEF3, 0xFEDCBA90FEDCBAC))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VSTQ:
    printf("RXA_ISA_VSTQ\n");
    if (check_sram(dev, RXAI_OFFS_SPAD, 48, 0x1111111111111111) &&
        check_sram(dev, RXAI_OFFS_SPAD, 56, (0x1111111111111111 << 1)) &&
        check_sram(dev, RXAI_OFFS_SPAD, 64, (0x1111111111111111 << 2)) &&
        check_sram(dev, RXAI_OFFS_SPAD, 72, (0x1111111111111111 << 3)))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VLD_W:
    if (check_reg(dev, x4, (uint64_t)0x12345678, 0) &&
        check_reg(dev, x5, 0x87654321, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VLDQ_W:
    if (check_reg(dev, x4, 0x11111111, 0) &&
        check_reg(dev, x5, 0x11111111, 0) &&
        check_reg(dev, x6, 0x11111111 << 1, 0) &&
        check_reg(dev, x7, 0x11111111 << 1, 0) &&
        check_reg(dev, x8, 0x11111111 << 2, 0) &&
        check_reg(dev, x9, 0x11111111 << 2, 0) &&
        check_reg(dev, x10, (uint64_t)0x11111111 << 3, 0) &&
        check_reg(dev, x11, (uint64_t)0x11111111 << 3, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_PRFC: {
    uint32_t offs_prfc = dev->cfg->offs_prfc;
    if (check_sram(dev, RXAI_OFFS_SRAM, offs_prfc, 0x1111111111111111) &&
        check_sram(dev, RXAI_OFFS_SRAM, offs_prfc + 8,
                   0x1111111111111111 << 1) &&
        check_sram(dev, RXAI_OFFS_SRAM, offs_prfc + 16,
                   0x1111111111111111 << 2) &&
        check_sram(dev, RXAI_OFFS_SRAM, offs_prfc + 24,
                   0x1111111111111111 << 3) &&
        check_sram(dev, RXAI_OFFS_SRAM, offs_prfc + 32, 0x1111111111111111) &&
        check_sram(dev, RXAI_OFFS_SRAM, offs_prfc + 40,
                   0x1111111111111111 << 1) &&
        check_sram(dev, RXAI_OFFS_SRAM, offs_prfc + 48,
                   0x1111111111111111 << 2) &&
        check_sram(dev, RXAI_OFFS_SRAM, offs_prfc + 56,
                   0x1111111111111111 << 3))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
  } break;
  case RXA_ISA_XOR:
    if (check_reg(dev, x2, 0x95511559, 0) &&
        check_reg(dev, x3, 0x8765432195511559, 0) &&
        check_reg(dev, x4, 0x789abcde00000000, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_ROR:
    if (check_reg(dev, x1, 0x8D159E048D159E04, 0) &&
        check_reg(dev, x3, 0xE048D159E048D159, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_RORI:
    if (check_reg(dev, x1, 0xE048D159E048D159, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_SWAP:
    if (check_reg(dev, x1, 0x8765432187654321, 0) &&
        check_reg(dev, x2, 0x1234567812345678, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_ADDSL:
    if (check_reg(dev, x2, 0x9999999555555551, 0) &&
        check_reg(dev, x3, 0x1111111555555551, 0) &&
        check_reg(dev, x4, 0x1111111999999991, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_ADDI:
    if (check_reg(dev, x2, 0x1111111111113000, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_ADD:
    if (check_reg(dev, x1, 0x5555555555555555, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_SUB:
    if (check_reg(dev, x2, 0x1111111122222222, 0) &&
        check_reg(dev, x3, 0x3333333322222222, 0) &&
        check_reg(dev, x4, 0x3333333311111111, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_NEG:
    if (check_reg(dev, x1, 0xeeeeeeeeeeeeeeef, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_MUL:
    if (check_reg(dev, x2, 0xdddddddeeeeeeef, 0) &&
        check_reg(dev, x3, 0xffffffffeeeeeeef, 0) &&
        check_reg(dev, x4, 0xdddddde, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_MULH:
    if (check_reg(dev, x2, 0x0, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_MULHU:
    if (check_reg(dev, x2, 0xf111111111111110, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VXOR:
    if (check_reg(dev, v2, 0x5555555555555555, 0xaaaaaaaaaaaaaaaa))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VSWAP:
    if (check_reg(dev, v1, 0x2222222222222222, 0x1111111111111111))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VADD_D:
    if (check_reg(dev, v2, 0x4444444444444444, 0x2222222222222222))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VSUB_D:
    if (check_reg(dev, v2, 0x4444444444444444, 0xa222222222222222))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VMUL_D:
    if (check_reg(dev, v2, 0x15659e26af37c048, 0x8000000000000000))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VDIV_D:
    if (check_reg(dev, v2, 0x7323000000000000, 0xa655a5a5a5a5a5a5))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VSQRT_D:
    if (check_reg(dev, v1, 0x28808654a2d4f6da, 0x310816b6ac96ad6a))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_VCVT_D_W:
    if (check_reg(dev, v2, 0x41c1111111000000, 0x41b1111111000000))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_RXSFRM:
    if (check_reg(dev, v1, 0x28808654a2d4f6da, 0x310816b6ac96ad6a) &&
        check_reg(dev, v2, 0x28808654a2d4f6da, 0x310816b6ac96ad69))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_RXSSP:
    if (check_reg(dev, x2, 0x167000, 0) && check_reg(dev, x3, 0x76540, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_RXSMXA:
    if (check_reg(dev, x1, 0xB456701212345678, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_RXB:
    if (check_reg(dev, x1, 0x1111111111100000, 0) &&
        check_reg(dev, x3, 0x1234567800000000, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_BGT:
    if (check_reg(dev, x2, 0x22222222, 0) &&
        check_reg(dev, x3, 0x22222222, 0) &&
        check_reg(dev, x4, 0x3333333311111111, 0))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
    break;
  case RXA_ISA_RXBLK2B: {
    uint64_t cmp[8] = {0xb83e2ba259125651, 0x2c57fa674095e608,
                       0x72232e4c6bdeb9d2, 0x2ccc119d298cd97f,
                       0xb8207b1ebc72a4ee, 0x55f004a65316e74a,
                       0x8ab66225da696282, 0xaf25506e100f88c6};
    uint8_t *code   = rxa_get_code(dev);
#if 1
    for (int i = 0; i < 8; i++) {
      printf("%p: 0x%16lx\n", code + OFFSCIPHEROUT + 8 * i,
             *((uint64_t *)(code + OFFSCIPHEROUT + 8 * i)));
    }
#endif
    if (!memcmp(cmp, code + OFFSCIPHEROUT, 64))
      cmd->result = RXA_ISA_PASS;
    else
      cmd->result = RXA_ISA_FAIL;
  } break;
	/* RXA_ISA_RXAES1RX4_HASH, RXA_ISA_RXAES1RX4_MUTI */
  case RXA_ISA_RXAES1RX4: {
    uint64_t cmp[8] = {0x25a4424b727ab1b2, 0xb53a90c9f56f1bc9,
                       0xe8027504fed70bc4, 0x70152fd1377f234d,
                       0x85b20930f22cf15b, 0xae1f977a841fdb02,
                       0x8a756cec33c0d189, 0x2fd5f1128e94c44};
		uint64_t hcmp[8] = {0xbd099f6d4203eb93, 0x69e9426dae427b1a,
                        0x751040814b30d84a, 0xbb96b16ef23479c6,
                        0xfd302e12cce17c2b, 0x387999174918d91d,
                        0x6a7fa04cadab76c4, 0xa574a2f160ad2499};
		uint64_t hash[8] = {0x99524d43988da11f, 0x85b3df988c773cf8, 
			                  0x5db64018817c4538, 0xa8c9a3c8a1825ae6, 
												0xe3d3823b02fab87c, 0x9463274f1ce681f5, 
												0x82d77013ef79054d, 0xad2107a878e6049f}; 
    uint32_t tmp;
    uint8_t *code = rxa_get_code(dev);
	
		if (!cmd->param) {
			if (memcmp(cmp, code + OFFSCIPHERIN, 64)) {
				cmd->result = RXA_ISA_FAIL;
				break;
			}
			cmd->result = RXA_ISA_PASS;
#if 0
			for (int i = 0; i < (0x200000 / 8); i++) {
				printf("0x%016lx ", *((uint64_t *)0x18000000 + i));
				if (!((i + 1) % 8))
					printf("\n");
			}
			printf("\n");
#endif
#ifdef CONFIG_COMPILE_FPGA
			lib_hash_init("crc32", 0x200000);
			lib_hash_data(rxa_get_spad(dev), 0x200000);
			lib_hash_value(&tmp);
			printf("CRC: 0x%x\n", tmp);
			if (tmp != 0x57677004) {
				cmd->result = RXA_ISA_FAIL;
				break;
			}
#endif
		} else if (cmd->param == 1) {
			if (memcmp(hash, code + OFFSCIPHEROUT, 64)) {
				cmd->result = RXA_ISA_FAIL;
				break;
			}
		} else if (cmd->param == 2) {
			if (memcmp(hcmp, code + OFFSCIPHERIN, 64)) {
				printf("OFFSCIPHERIN \n");
				cmd->result = RXA_ISA_FAIL;
				break;
			}
			if (memcmp(hash, code + OFFSCIPHEROUT, 64)) {
				cmd->result = RXA_ISA_FAIL;
				break;
			}
#ifdef CONFIG_COMPILE_FPGA
			lib_hash_init("crc32", 0x200000);
			lib_hash_data(rxa_get_spad(dev), 0x200000);
			lib_hash_value(&tmp);
			printf("CRC: 0x%x\n", tmp);
			if (tmp != 0x266172e5) {
				cmd->result = RXA_ISA_FAIL;
				break;
			}
#endif
			if (memcmp(hash, code + OFFSCIPHEROUT, 64)) {
				printf("OFFSCIPHEROUT,\n");
				cmd->result = RXA_ISA_FAIL;
				break;
			}
		}
    cmd->result = RXA_ISA_PASS;
  } break;
  case RXA_ISA_RXAES4RX4: {
    uint8_t *code = rxa_get_code(dev);
		uint32_t tmp;
#if 0
    for (int i = 264; i < 272; i++) {
      printf("0x%lx ", *((uint64_t *)(code + OFFSCIPHEROUT + 8 * i)));
      if (!((i + 1) % 8))
        printf("\n");
    }
#endif
		lib_hash_init("crc32", 0x880);
		lib_hash_data(code + OFFSCIPHEROUT, 0x880);
		lib_hash_value(&tmp);
		printf("CRC: 0x%x\n", tmp);
		if (tmp != 0xabd5a44e) {
			cmd->result = RXA_ISA_FAIL;
			break;
		}
    cmd->result = RXA_ISA_PASS;
  } break;
  default:
    printf("Do not support this case: %d\n", cmd->type);
    return -1;
  }

  printf("%s: %s\n", cmd->name, (cmd->result > 0) ? "Pass" : "Fail");
  return (cmd->result ? 0 : -1);
}

case_cmd_t *rxa_get_isa_cmd(char *name) {
  for (int i = 0; i < ARRAY_SIZE(instrs); i++) {
    printf("instrs[i].name %s, name %s\n", instrs[i].name, name);
		if (!strcmp(instrs[i].name, name)) {
			if (instrs[i].type == RXA_ISA_RXAES1RX4) {
				if (!strcmp(name, "RXAES1RX4_HASH"))
					instrs[i].param = 1;
				else if (!strcmp(name, "RXAES1RX4_MUTI"))
					instrs[i].param = 2;
			}
			return (&instrs[i]);
		}
  }

  return NULL;
}

void rxa_isa_test_callback(void *data) {
  case_cmd_t *cmd = (case_cmd_t *)data;
  rxa_isa_test_verfication(cmd);
}

int rxa_single_isa_test(rxa_device_t *dev, char *name) {
  case_cmd_t *cmd = NULL;

  cmd = rxa_get_isa_cmd(name);
  if (!cmd)
    return -1;

  printf("Test %s\n", cmd->name);
  /* init case_cmd_t cmd */
  cmd->started = false;
  cmd->result  = 0;
  cmd->dev     = dev;

  if (rxa_isa_test_prepare(cmd) < 0)
    return -1;

  rxa_start(dev);
  cmd->started = true;

  while (!cmd->result)
    udelay(5);

  return ((cmd->result > 0) ? 0 : -1);
}
