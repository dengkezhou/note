//********************************************************************
//(Copyright 2008) Verisilicon Inc. All Rights Reserved
//Company confidential and Properietary information.
//This information may not be disclosed to unauthorized individual.
//********************************************************************
//
// VeriSilicon Microelectronics Co.,Ltd.
//
// File Name: g2.h
// Author:    wgwei
// Version:   1.0
// Created:   Aug 14, 2013
// Modified:
// Description:
//********************************************************************
#include <common.h>
#include <para.h>
#ifndef _H2_DECODE_H_
#define _H2_DECODE_H_

//#define AXI64BIT
#define SWAP_64BIT
#if 1
#define H2_DBG(str...)  printf(str)
#define H2_ERR(str...)  printf(str)
#define H2_INFO(str...)  
#else 
#define H2_DBG(str...)  printf(str)
#define H2_ERR(str...)  LOG_ERR(str)
#define H2_INFO(str...)  printf(str) 
#endif

//****************************************************************
//q3 h2 reg mem

#define VENC_H2_REG_BASE	0x25300000//
#define VENC_H2_MEM_BASE	0x68000000//
#define H2_DEFAULT_OUTPUT_SIZE  10240000
#define H2_DEFAULT_DMMU_MAP_SIZE  102400000

#if 0
#define H2_DEC_HW_ID 				0x0
#define H2_DEC_CONFIG 				0x8 
#define H2_DEC_TILES 				0x29C
#define H2_DEC_INDATA				0x2A4
#define H2_DEC_PROBTABS				0x2B4

#define H2_DEC_PIC_FRM_Y			0x114 
#define H2_DEC_PIC_FRM_C			0x19C
#define H2_DEC_PIC_FRM_RSY 			0x2BC
#define H2_DEC_PIC_FRM_RSC			0x2C4
#define H2_DEC_DIRMV 				0x224
#define H2_DEC_CTX_COUNTER 			0x2AC

#define H2_DEC_MEM_OFFSET			0x60000000
#endif

#define H2_DEC_HW_ID 				0x0
#define H2_DEC_CONFIG 				80 
#define VENC_H2_SLICE_READY   0x100
#define VENC_H2_FRAME_READY   0x004
#define VENC_H2_IRQ_READY	  0x001
typedef struct {
	char caseName[32];
	char inScript[128];
	char inData[128];

	char outDir[128];

	uint32_t encPicNum;

	uint32_t outStrmSizeCrc[2];
	uint32_t outPlumSizeCrc[2];
	uint32_t outTblSizeCrc[2];
	uint32_t outLuSizeCrc[2];
	uint32_t outChSizeCrc[2];
	uint32_t outNalsSizeCrc[2];
	uint32_t irqEnable;
	uint32_t dmmuEnable;

}VENC_H2_TB_CFG;
typedef struct {
	uint16_t regIndex ;
	uint8_t  used ; 
	uint8_t  servered_8_1 ;
	uint32_t offset ;
	uint32_t reserved_32_1;
	uint32_t reserved_32_2;
}RegOffsetPara;
typedef struct {
    uint16_t cmdIndex;
    uint8_t keyFlag ;
    uint8_t reserved;
    uint32_t para1;
    uint32_t para2;
    uint32_t para3;
}ScriptCmd;
//#define VENC_H2_FULL_DUMP  0
#define VENC_H2_MAX_ENCODE_PIC_NUM   15
#endif

