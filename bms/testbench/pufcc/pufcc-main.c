/*
 * Copyright (C) intchains Holding Limited
 */

/******************************************************************************
 * @file     pufcc-main.c
 * @brief    pufcc testBench
 * @version  V1.0
 * @date     11.21 2022

 * @name     pufcc-main
 * author    jason.liu
 ******************************************************************************/
#include <common.h>
#include <command.h>
#include <testbench.h>
#include <malloc.h>
#include <irq.h>
#include <asm/io.h>
#include <getopt.h>

#include "pufs_memory_map.h"
#include "pufs_common.h"
#include "pufs_ka.h"
#include "pufs_ka_test.h"
#include "pufs_crypto.h"
#include "pufs_cmac.h"
#include "pufs_cmac_test.h"
#include "pufs_rt.h"
#include "pufs_rt_test.h"
#include "pufs_dma.h"
#include "pufs_dma_test.h"
#include "pufs_kdf.h"
#include "pufs_kdf_test.h"
#include "pufs_hmac.h"
#include "pufs_hmac_test.h"
#include "pufs_sp38a.h"
#include "pufs_sp38a_test.h"
#include "pufs_sp38c.h"
#include "pufs_sp38c_test.h"
#include "pufs_sp38d.h"
#include "pufs_sp38d_test.h"
#include "pufs_sp38e.h"
#include "pufs_sp38e_test.h"
#include "pufs_sp90a.h"
#include "pufs_sp90a_test.h"
#include "pufs_ecp.h"
#include "pufs_ecp_test.h"
#include "pufs_sm2.h"
#include "pufs_sm2_test.h"
#include "pufs_chacha.h"
#include "pufs_chacha_test.h"


const static bool PUFCC_EVAL_TIME = false;
#define PUFCC_STR(arg) #arg

#define PUFCC_TEST(func) ({\
          int ret; \
          uint64_t t; \
          if (PUFCC_EVAL_TIME) \
            t = get_timer(0); \
          ret = func(); \
          if (PUFCC_EVAL_TIME) \
            printf("\n%s spend %llu ms\n", PUFCC_STR(func), get_timer(t)); \
          if(ret != SUCCESS) \
            printf("Pufcc %s Failed!\n",PUFCC_STR(func)); \
          else \
            printf("Pufcc %s Pass!\n",PUFCC_STR(func)); \
          ret == SUCCESS; \
          })

struct test_st{
    char *case_name;
    bool (*case_func) (void);
};

bool fpga_all_test(void);
static void pufcc_show_usage(void);

bool fpga_chacha20_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_chacha_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_chacha_enc_sg_test);
    ret &= PUFCC_TEST(pufs_chacha_enc_test);
    ret &= PUFCC_TEST(pufs_chacha_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_chacha_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_chacha_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_chacha_dec_sg_test);
    ret &= PUFCC_TEST(pufs_chacha_dec_test);
    ret &= PUFCC_TEST(pufs_chacha_dec_swkey_test);
    return ret;
}

bool fpga_chacha20_poly1305_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_chacha20_poly1305_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_chacha20_poly1305_enc_sg_test);
    ret &= PUFCC_TEST(pufs_chacha20_poly1305_enc_test);
    ret &= PUFCC_TEST(pufs_chacha20_poly1305_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_chacha20_poly1305_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_chacha20_poly1305_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_chacha20_poly1305_dec_sg_test);
    ret &= PUFCC_TEST(pufs_chacha20_poly1305_dec_test);
    ret &= PUFCC_TEST(pufs_chacha20_poly1305_dec_swkey_test);
    ret &= PUFCC_TEST(puf_poly1305_test);
    return ret;
}

bool fpga_cmac_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_cmac_iuf_test);
    ret &= PUFCC_TEST(pufs_cmac_sg_test);
    ret &= PUFCC_TEST(pufs_cmac_test);
    ret &= PUFCC_TEST(pufs_cmac_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_cmac_swkey_test);
    ret &= PUFCC_TEST(pufs_cmac_multi_ctx_test);
    return ret;
}

bool fpga_dma_test(void){
    bool ret = true;
    ret &= PUFCC_TEST(pufs_dma_entropy_read_test);
    ret &= PUFCC_TEST(pufs_dma_random_read_test);
    return ret;
}

bool fpga_rsa_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_rsa_verify_test);
    ret &= PUFCC_TEST(pufs_rsa_sign_test);
    ret &= PUFCC_TEST(pufs_rsa_x931_verify_test);
    ret &= PUFCC_TEST(pufs_rsa_x931_sign_test);
    ret &= PUFCC_TEST(pufs_rsa_pss_verify_test);
    ret &= PUFCC_TEST(pufs_rsa_pss_sign_test);
    ret &= PUFCC_TEST(pufs_rsa_p1v15_verify_test);
    ret &= PUFCC_TEST(pufs_rsa_p1v15_sign_test);
    return ret;
}

bool fpga_ecp_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_ecp_ecpuk_test);
    ret &= PUFCC_TEST(pufs_ecp_ecpkv_test);
    ret &= PUFCC_TEST(pufs_ecp_ecccdh_2e2s_test);
    ret &= PUFCC_TEST(pufs_ecp_ecccdh_2e_test);
    // PUFCC_TEST(pufs_ecp_ecccdh_oss_test); // E_UNSUPPORT
    ret &= PUFCC_TEST(pufs_ecp_ecdsa_verify_test);
    // PUFCC_TEST(pufs_ecp_ecdsa_verify_otpkey_test); // E_UNSUPPORT
    // PUFCC_TEST(pufs_ecp_ecdsa_sign_k_test); // E_UNSUPPORT
    ret &= PUFCC_TEST(pufs_ecp_ecdsa_sign_verify_test);
    ret &= PUFCC_TEST(pufs_ecp_eprk_gen_test);
    ret &= PUFCC_TEST(pufs_ecp_sprk_gen_test);
    return ret;
}

bool fpga_sha2_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_sha2_iuf_test);
    ret &= PUFCC_TEST(pufs_sha2_sg_test);
    ret &= PUFCC_TEST(pufs_sha2_test);
    ret &= PUFCC_TEST(pufs_sha2_multi_ctx_test);
    return ret;
}

bool fpga_sm3_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_sm3_iuf_test);
    ret &= PUFCC_TEST(pufs_sm3_sg_test);
    ret &= PUFCC_TEST(pufs_sm3_test);
    ret &= PUFCC_TEST(pufs_sm3_multi_ctx_test);
    return ret;
}

bool fpga_hmac_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_hmac_iuf_test);
    ret &= PUFCC_TEST(pufs_hmac_sg_test);
    ret &= PUFCC_TEST(pufs_hmac_test);
    ret &= PUFCC_TEST(pufs_hmac_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_hmac_swkey_test);
    ret &= PUFCC_TEST(pufs_hmac_multi_ctx_test);
    return ret;
}

bool fpga_ka_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_key_export_test);
    ret &= PUFCC_TEST(pufs_aes_kw_test);
    ret &= PUFCC_TEST(pufs_aes_kw_inv_test);
    ret &= PUFCC_TEST(pufs_aes_kwp_test);
    ret &= PUFCC_TEST(pufs_aes_kwp_inv_test);
    return ret;
}

bool fpga_kdf_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_ckdf2_test);
    ret &= PUFCC_TEST(pufs_ckdf2_swkey_test);
    ret &= PUFCC_TEST(pufs_hkdf2_test);
    ret &= PUFCC_TEST(pufs_hkdf2_swkey_test);
    ret &= PUFCC_TEST(pufs_skdf2_swkey_test);
    return ret;
}
/* 
 * In security mode, return SUCCESS in c920, return E_VERFAIL in e906.
 * In non-security mode, return E_VERFAIL in both c920 and e906.
 */
static int pufs_sec_chk(void)
{
  uint32_t * const s = (uint32_t *)PUFIOT_ADDR_START;
  uint32_t * const e = (uint32_t *)(PUFIOT_ADDR_START + PUFIOT_MAP_SIZE);
  for (uint32_t *p = s; p < e; p++) {
    if (*p != 0x0) {
      printf("Security check Failed");
      return E_VERFAIL;
    }
  }

  printf("Security check Pass\n");
  return SUCCESS;
}

bool pufs_sec_en(void)
{
  printf("Entering security mode...\n");
  writel(0x1, ITCS_S_SAP_BASE + 0x30);
  printf("Security mode enabled\n");

  return 0;
}

/* rt_factory */
bool fpga_ptm_st_wrong_test(void)   { return PUFCC_TEST(pufs_rt_ptm_status_wrong_test); }
bool fpga_ptm_st_warn_test(void)    { return PUFCC_TEST(pufs_rt_ptm_status_warning_test); }
bool fpga_uid_zeroize_test(void)    { return PUFCC_TEST(pufs_rt_uid_zeroize_test); }
bool fpga_otp_zeroize_test(void)    { return PUFCC_TEST(pufs_rt_otp_zeroize_test); }
bool fpga_puf_enroll_test(void)     { return PUFCC_TEST(pufs_rt_ptm_puf_enroll_test); }
bool fpga_auto_repair_test(void)    { return PUFCC_TEST(pufs_rt_auto_repair_test); }
bool fpga_repair_prog_test(void)    { return PUFCC_TEST(pufs_rt_repair_program_test); }
bool fpga_pif_set_flag_test(void)   { return PUFCC_TEST(pufs_rt_pif_set_flag_test); }
bool fpga_pif_uid_read_test(void)   { return PUFCC_TEST(pufs_rt_uids_read_test); }
bool fpga_puf_qty_chk_test(void)    { return PUFCC_TEST(pufs_rt_ptm_puf_qty_chk_test); }
bool fpga_puf_health_chk_test(void) { return PUFCC_TEST(pufs_rt_ptm_puf_health_chk_test); }
bool fpga_ini_off_chk_test(void)    { return PUFCC_TEST(pufs_rt_ini_off_check_test); }
bool fpga_set_pin_test(void)        { return PUFCC_TEST(pufs_rt_set_pin_test); }
bool fpga_sec_en(void)              { return PUFCC_TEST(pufs_sec_en); }
bool fpga_sec_chk(void)             { return PUFCC_TEST(pufs_sec_chk); }

static const struct test_st pufcc_rt_factory_test_table[] = {
#ifndef CONFIG_COMPILE_ASIC
  { "ptm_st_wrong",     fpga_ptm_st_wrong_test },
  { "ptm_st_warn",      fpga_ptm_st_warn_test },
  // { "ptm_st_fbid",      fpga_ptm_st_fbid_test },
  { "uid_zeroize",      fpga_uid_zeroize_test },
  { "otp_zeroize",      fpga_otp_zeroize_test },
  { "puf_enroll",       fpga_puf_enroll_test },
  { "auto_repair",      fpga_auto_repair_test },
  { "repair_prog",      fpga_repair_prog_test },
  { "pif_set_flag",     fpga_pif_set_flag_test },
  { "pif_uid_read",     fpga_pif_uid_read_test },
  { "puf_qty_chk",      fpga_puf_qty_chk_test },
  { "puf_health_chk",   fpga_puf_health_chk_test },
  { "ini_off_chk",      fpga_ini_off_chk_test },
  { "set_pin",          fpga_set_pin_test },
  { "dma",              fpga_dma_test },
  { "sec_en",           fpga_sec_en },
  { "sec_chk",          fpga_sec_chk },
#endif
  { NULL, NULL}
};

/* rt_user */
bool fpga_otp_rw_test(void)         { return PUFCC_TEST(pufs_rt_otp_read_write_test); }
bool fpga_otp_rwlck_test(void)      { return PUFCC_TEST(pufs_rt_otp_rwlck_test); }
bool fpga_ptr_rw_test(void)         { return PUFCC_TEST(pufs_rt_ptr_read_write_test); }
bool fpga_ptc_rw_test(void)         { return PUFCC_TEST(pufs_rt_ptc_read_write_test); }
bool fpga_rand_resume_test(void)    { return PUFCC_TEST(pufs_rt_rand_resume_test); }

bool fpga_rt_user_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_rt_read_mode_test);
    ret &= PUFCC_TEST(pufs_rt_rand_read_test);
    ret &= PUFCC_TEST(pufs_rt_rand_clk_test);
    // PUFCC_TEST(pufs_rt_tcm_test); // Failed
    // PUFCC_TEST(pufs_rt_auto_load_test); // E_UNSUPPORT
    ret &= PUFCC_TEST(pufs_rt_pdstb_test);
    return ret;
}

static const struct test_st pufcc_rt_user_test_table[] = {
#ifndef CONFIG_COMPILE_ASIC
  {"otp_rw",        fpga_otp_rw_test },
  {"otp_rwlck",     fpga_otp_rwlck_test },
  {"ptr_rw",        fpga_ptr_rw_test },
  {"ptc_rw",        fpga_ptc_rw_test },
  {"rand_resume",   fpga_rand_resume_test },
#endif
  { NULL, NULL}
};

bool fpga_sm2_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_sm2_dec_test);
    ret &= PUFCC_TEST(pufs_sm2_enc_test);
    ret &= PUFCC_TEST(pufs_sm2_kex_test);
    ret &= PUFCC_TEST(pufs_sm2_verify_test);
    ret &= PUFCC_TEST(pufs_sm2_sign_test);
    return ret;
}

bool fpga_aes_test(void)
{
    bool ret = true;
#ifdef PUFS_TV_FULL
    ret &= PUFCC_TEST(pufs_aes_ecb_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_enc_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_dec_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_ecb_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_enc_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_dec_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cfb_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_enc_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_dec_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_ofb_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_enc_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_dec_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_enc_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_dec_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs1_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_enc_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_dec_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs2_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_enc_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_dec_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_cbc_cs3_dec_multi_ctx_test);
#endif
    ret &= PUFCC_TEST(pufs_aes_ctr_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_enc_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_dec_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_ctr_counter_test);
    return ret;
}

bool fpga_sm4_test(void)
{
    bool ret = true;
#ifdef PUFS_TV_FULL
    ret &= PUFCC_TEST(pufs_sm4_ecb_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ecb_enc_test);
    ret &= PUFCC_TEST(pufs_sm4_ecb_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ecb_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_ecb_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_sm4_ecb_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ecb_dec_test);
    ret &= PUFCC_TEST(pufs_sm4_ecb_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ecb_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_ecb_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_enc_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_dec_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_cfb_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_enc_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_dec_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_ofb_dec_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_enc_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_dec_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_cbc_dec_multi_ctx_test);
#endif
    ret &= PUFCC_TEST(pufs_sm4_ctr_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ctr_enc_test);
    ret &= PUFCC_TEST(pufs_sm4_ctr_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ctr_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_ctr_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_sm4_ctr_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ctr_dec_test);
    ret &= PUFCC_TEST(pufs_sm4_ctr_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_sm4_ctr_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_sm4_ctr_dec_multi_ctx_test);
    return ret;
}

bool fpga_aes_ccm_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_aes_ccm_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_enc_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_dec_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_ccm_dec_multi_ctx_test);
    return ret;
}

bool fpga_aes_gcm_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_aes_gcm_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_enc_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_dec_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_gcm_dec_multi_ctx_test);
    return ret;
}

bool fpga_aes_xts_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_aes_xts_enc_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_xts_enc_sg_test);
    ret &= PUFCC_TEST(pufs_aes_xts_enc_test);
    ret &= PUFCC_TEST(pufs_aes_xts_enc_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_xts_enc_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_xts_enc_multi_ctx_test);
    ret &= PUFCC_TEST(pufs_aes_xts_dec_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_xts_dec_sg_test);
    ret &= PUFCC_TEST(pufs_aes_xts_dec_test);
    ret &= PUFCC_TEST(pufs_aes_xts_dec_swkey_iuf_test);
    ret &= PUFCC_TEST(pufs_aes_xts_dec_swkey_test);
    ret &= PUFCC_TEST(pufs_aes_xts_dec_multi_ctx_test);
    return ret;
}

bool fpga_drbg_test(void)
{
    bool ret = true;
    ret &= PUFCC_TEST(pufs_drbg_test);
    return ret;
}

#include <pufs_sp38a.h>

bool aes_prog_otpkey(void)
{
  const uint32_t key[256 / 8 / 4] = {
    0x6fcea371, 0x7b324b88, 0xcd56de72, 0x37b69993,
    0x39ca5b6e, 0x32aef480, 0x2bcfaad1, 0x2f5f1bc8,
  };
  pufs_status_t check = SUCCESS;

  if ((check = pufs_program_otp((const uint8_t*)key, sizeof(key), 0x180)) != SUCCESS)
    printf("Fail to program otp\n");

  return 0;
}


// const static uint32_t otp0[OTP_KEY_LEN / 4] = {
//     0x6fcea371, 0x7b324b88, 0xcd56de72, 0x37b69993,
//     0x39ca5b6e, 0x32aef480, 0x2bcfaad1, 0x2f5f1bc8,
// };

bool aes_read_otpkey(void)
{
  pufs_status_t check = SUCCESS;
  uint32_t otpall[OTP_LEN / 4];

  if ((check = pufs_read_otp((uint8_t *)otpall, sizeof(otpall), 0)) != SUCCESS)
    printf("Fail to read otp\n");

  (void)otpall;

  return 0;
}

bool aes_otpkey_enc_test(void)
{
  const uint32_t pt[16] = {
    0xe2bec16b, 0x969f402e, 0x117e3de9, 0x2a179373,
    0x578a2dae, 0x9cac031e, 0xac6fb79e, 0x518eaf45,
    0x461cc830, 0x11e45ca3, 0x19c1fbe5, 0xef520a1a,
    0x45249ff6, 0x179b4fdf, 0x7b412bad, 0x10376ce6,
  };
  const uint32_t iv[4] = {
    0x00010203, 0x4050607, 0x08090a0b, 0x0c0d0e0f
  };
  const uint32_t ct[16] = {
    0x7465851f, 0xba5bf8aa, 0x109e888c, 0x71fcd5ef,
    0xf301f5f0, 0xad805004, 0x18cdd122, 0x061e66a6,
    0x368a5bb7, 0x30a82744, 0x9e4ddb8f, 0x695798d7,
    0x139a1509, 0xfa3e88bd, 0xd4ca85ca, 0x22bfa1c0,
  };

#ifdef CONFIG_COMPILE_ASIC
  aes_prog_otpkey();
#endif

  pufs_status_t check = SUCCESS;
  uint32_t out[64];
  uint32_t outlen, inlen;

  inlen = sizeof(pt);

  if (((check = pufs_enc_cbc((uint8_t *)out, &outlen, (const uint8_t *)pt, inlen, AES, OTPKEY, OTPKEY_12, 256, (const uint8_t *)iv, 0)) != SUCCESS) ||
      ((check = (outlen != inlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
      ((check = pufs_test_memcmp(out, ct, inlen)) != SUCCESS))
  {
      printf("Pufcc %s Failed!\n", __func__);
  } else {
      printf("Pufcc %s Pass!\n", __func__);
  }

  return 0;
}

bool aes_otpkey_dec_test(void)
{
  const uint32_t pt[16] = {
    0xe2bec16b, 0x969f402e, 0x117e3de9, 0x2a179373,
    0x578a2dae, 0x9cac031e, 0xac6fb79e, 0x518eaf45,
    0x461cc830, 0x11e45ca3, 0x19c1fbe5, 0xef520a1a,
    0x45249ff6, 0x179b4fdf, 0x7b412bad, 0x10376ce6,
  };
  const uint32_t iv[4] = {
    0x00010203, 0x4050607, 0x08090a0b, 0x0c0d0e0f
  };
  const uint32_t ct[16] = {
    0x7465851f, 0xba5bf8aa, 0x109e888c, 0x71fcd5ef,
    0xf301f5f0, 0xad805004, 0x18cdd122, 0x061e66a6,
    0x368a5bb7, 0x30a82744, 0x9e4ddb8f, 0x695798d7,
    0x139a1509, 0xfa3e88bd, 0xd4ca85ca, 0x22bfa1c0,
  };

  pufs_status_t check = SUCCESS;
  uint32_t out[64];
  uint32_t outlen, inlen;

#ifdef CONFIG_COMPILE_ASIC
  aes_prog_otpkey();
#endif

  inlen = sizeof(ct);

  if (((check = pufs_dec_cbc((uint8_t *)out, &outlen, (const uint8_t *)ct, inlen, AES, OTPKEY, OTPKEY_12, 256, (const uint8_t *)iv, 0)) != SUCCESS) ||
      ((check = (outlen != inlen ? E_VERFAIL : SUCCESS)) != SUCCESS) ||
      ((check = pufs_test_memcmp(out, pt, inlen)) != SUCCESS))
  {
      printf("Pufcc %s Failed!\n", __func__);
  } else {
      printf("Pufcc %s Pass!\n", __func__);
  }
  free(out);

  return 0;
}

#include "pufs_dma_internal.h"
extern struct pufs_dma pufs_dma;

static int pufcc_irq_handler(int irq, void *args)
{
  pufs_dma.regs->interrupt |= (0x01 << 0);

  printf("Pufcc irq_test Pass!\n");

  return 0;
}

bool irq_test(void)
{
  pufs_status_t check;
  pufs_dma_dsc_attr_st attr = {
      .fix_read_addr = false,
      .fix_write_addr = false,
      .read_protect = 0x0,
      .write_protect = 0x0,
  };
  const uint32_t length = 15;
  char in[15] __attribute__((aligned(64)));
  uint8_t out[15] __attribute__((aligned(64)));

  memcpy(in, "\x11\x22\x33\x44\x55\x66\x77\x88\x99\xaa\xbb\xcc\xdd\xee\xff", 15);

  request_irq(S_PUFCC_IRQn, pufcc_irq_handler, "pufcc_irq", NULL);
  pufs_dma.regs->interrupt |= (0x01 << 16);

  if ((check = pufs_dma_read_write(out, 4, (uint8_t *)in, length, &attr)) != SUCCESS)
  {
      return check;
  }

#ifdef CONFIG_COMPILE_RTL
  while (1) {
    printf("Please stop simulation manually if test case Pass\n");
    udelay(1000);
  }
#endif

  return true;
}

static const struct test_st pufcc_test_table[] = {
  { "sha2"                   ,fpga_sha2_test },
  { "sm3"                    ,fpga_sm3_test },
  { "hmac"                   ,fpga_hmac_test },
  { "cmac"                   ,fpga_cmac_test },
  { "chacha20"               ,fpga_chacha20_test },
  { "aes"                    ,fpga_aes_test },
  { "aes_xts"                ,fpga_aes_xts_test },
  { "sm4"                    ,fpga_sm4_test },
  { "chacha20_poly1305"      ,fpga_chacha20_poly1305_test },
  { "aes_ccm"                ,fpga_aes_ccm_test },
  { "aes_gcm"                ,fpga_aes_gcm_test },
  { "drbg"                   ,fpga_drbg_test },
  { "kdf"                    ,fpga_kdf_test },
  { "sm2"                    ,fpga_sm2_test },
  { "rsa"                    ,fpga_rsa_test },
  { "ecp"                    ,fpga_ecp_test },
  { "ka"                     ,fpga_ka_test },
  { NULL, NULL}
};

static const struct test_st pufcc_test_group_table[] = {
  { "all"                    ,fpga_all_test },
#ifndef CONFIG_COMPILE_ASIC
  { "sm2"                    ,fpga_sm2_test },
  { "aes_otp_prog"           ,aes_prog_otpkey },
  { "aes_otp_read"           ,aes_read_otpkey },
  { "aes_otp_enc"            ,aes_otpkey_enc_test },
  { "aes_otp_dec"            ,aes_otpkey_dec_test },
  { "irq"                    ,irq_test },
  { "rt_user"                ,fpga_rt_user_test },
#else
  { "ini_off_chk",      fpga_ini_off_chk_test },
  { "puf_qty_chk",      fpga_puf_qty_chk_test },
  { "puf_health_chk",   fpga_puf_health_chk_test },
  { "puf_enroll",       fpga_puf_enroll_test },
  { "auto_repair",      fpga_auto_repair_test },
  { "pif_uid_read",     fpga_pif_uid_read_test },
  { "aes_otp_enc",      aes_otpkey_enc_test },
  { "aes_otp_dec",      aes_otpkey_dec_test },
  { "irq",              irq_test },
  { "rt_user",          fpga_rt_user_test },
#endif
  { NULL, NULL}
};

static void pufcc_show_usage(void)
{
  const struct test_st *ptr = pufcc_test_table;

  printf("Usage: pufcc [OPTION]...\n\n");
  printf("--help\t\tcommand help\n");
  for (int i = 0; ptr[i].case_name && ptr[i].case_func; i++) {
    printf("\t%s\t\t Run %s test case\n",
        ptr[i].case_name, ptr[i].case_name);
  }

  ptr = pufcc_test_group_table;
  for (int i = 0; ptr[i].case_name && ptr[i].case_func; i++) {
    printf("\t%s\t\t Run %s test case\n",
        ptr[i].case_name, ptr[i].case_name);
  }

  printf("\nUnrecoverable test functions below:\n");

  ptr = pufcc_rt_factory_test_table;
  for (int i = 0; ptr[i].case_name && ptr[i].case_func; i++) {
    printf("\t%s\t\t Run %s test case\n",
        ptr[i].case_name, ptr[i].case_name);
  }

  ptr = pufcc_rt_user_test_table;
  for (int i = 0; ptr[i].case_name && ptr[i].case_func; i++) {
    printf("\t%s\t\t Run %s test case\n",
        ptr[i].case_name, ptr[i].case_name);
  }
}

bool fpga_all_test(void)
{
  const struct test_st *ptr = pufcc_test_table;
  int pass = 0, fail = 0;

  for (int i = 0; ptr[i].case_name && ptr[i].case_func; i++) {
    if (ptr[i].case_func() != true)
      fail++;
    else
      pass++;
  }
  printf("\n\nPufcc %d cases Pass, %d cases Failed\n\n", pass, fail);
  return fail == 0;
}

bool run_test_case(const struct test_st * test_table, const char * case_name)
{
    int ret;
    const struct test_st * ptr = test_table;

    if( (test_table == NULL) || (case_name == NULL) ){
        printf("cmd error!, test table or name is null.\n");
        return false;
    }

    while(1){
        if(ptr->case_name == NULL){
            // printf("cmd error!, arg2:%s\n",case_name);
            return false;
        }
        ret = strcmp(case_name, ptr->case_name);
        if(!ret){
            return ptr->case_func();
        }else{
            ptr++;
        }
    }
}

static int pufcc_main(int argc, char *argv[]) {
  
  if(argc != 2 || !strcmp(argv[1], "help") || !strcmp(argv[1], "-h")) {
    pufcc_show_usage();
    return -1;
  }

  if (run_test_case(pufcc_test_table, argv[1]) != false) {
    /* Do something... */
  } else if (run_test_case(pufcc_rt_factory_test_table, argv[1]) != false) {
    /* Do something... */
  } else if (run_test_case(pufcc_rt_user_test_table, argv[1]) != false) {
    /* Do something... */
  } else if (run_test_case(pufcc_test_group_table, argv[1]) != false) {
     return -1;
  }

  return 0;
}

void pufcc_init(void) { register_testbench("pufcc", pufcc_main, NULL); }

testbench_init(pufcc_init);
