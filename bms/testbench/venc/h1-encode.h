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
#ifndef _H1_DECODE_H_
#define _H1_DECODE_H_

//#define AXI64BIT
#define SWAP_64BIT
#if 0
	#define H1_DBG(str...)  printf(str)
	#define H1_ERR(str...)  printf(str)
	#define H1_INFO(str...)  
#else 
	#define H1_DBG(str...)  printf(str)
	#define H1_ERR(str...)  printf(str)
	#define H1_INFO(str...)  printf(str) 
#endif


//****************************************************************
//q3 reg mem
#define VENC_H1_REG_BASE	0x25100000//for webm platform

#define H1_DEFAULT_OUTPUT_SIZE  0xA00000  //10Mb

#define VENC_H1_MEM_BASE            0x60000000

#define VENC_H1_DEFAULT_DMMU_MAP_SIZE  0x12000000
typedef struct {
	char caseName[32];
	char inScript[128];

	char inData[128];
	char inCtab[128];
	char inSeg[128];
	char inStab[128];

	uint32_t outCtxSizeCrc[2];
	uint32_t outMvsSizeCrc[2];
	uint32_t outNalsSizeCrc[2];
	uint32_t outPrt1SizeCrc[2];
	uint32_t outPrt2SizeCrc[2];
	uint32_t outPrt3SizeCrc[2];
	uint32_t outPrt4SizeCrc[2];
	uint32_t outReLuSizeCrc[2];
	uint32_t outReChSizeCrc[2];
	uint32_t outScaleSizeCrc[2];
	uint32_t outStrmSizeCrc[2];
	uint32_t outStrmAmSizeCrc[2];

	uint32_t picNum;
	uint32_t irqEnable;
	uint32_t dmmuEnable;
}VENC_H1_TB_CFG;
typedef struct {
	uint16_t regIndex ;
	uint8_t  used ; 
	uint8_t  servered_8_1 ;
	uint32_t offset ;
	uint32_t reserved_32_1;
	uint32_t reserved_32_2;
}VencRegOffsetPara;
typedef struct {
    uint16_t cmdIndex;
    uint8_t keyFlag ;
    uint8_t reserved;
    uint32_t para1;
    uint32_t para2;
    uint32_t para3;
}VencScriptCmd;

#define VENC_H1_IRQ_PICTURE_READY_BIT   0x4
#define VENC_H1_IRQ_SLICE_READY_BIT   0x100
#define VENC_H1_IRQ_STREM_ERR_BIT     0x200
#define VENC_H1_IRQ_BUS_ERR_BIT       0x8
#define VENC_H1_IRQ_TIMEOUT_BIT       (0x1<<6)
#define VENC_H1_IRQ_READY_BIT         0x1

#endif

