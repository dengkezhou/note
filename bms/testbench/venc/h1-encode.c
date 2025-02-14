//********************************************************************
//(Copyright 2008) Verisilicon Inc. All Rights Reserved
//Company confidential and Properietary information.
//This information may not be disclosed to unauthorized individual.
//********************************************************************
//
// VeriSilicon Microelectronics Co.,Ltd.
//
// File Name: h1.c
// Author:    wgwei
// Version:   1.0
// Created:   Aug 14, 2013
// Modified:
// Description:
//********************************************************************
#include "h1-encode.h"
#include <common.h>
#include <venc-common.h>
#include <asm/io.h>
#include <common.h>
#include <para.h>
#include <irq.h>
#include <iws100/interrupt.h>

static VencLinearMem outCtxBuf ;
static VencLinearMem outMvsBuf ;
static VencLinearMem outNalsBuf ;
static VencLinearMem outPrt1Buf ;
static VencLinearMem outPrt2Buf ;
static VencLinearMem outPrt3Buf ;
static VencLinearMem outPrt4Buf ;
static VencLinearMem outReChBuf ;
static VencLinearMem outReLuBuf ;
static VencLinearMem outScaleBuf ;
static VencLinearMem outStrmBuf ;
static VencLinearMem outStrmAmBuf ;
//input file 
static FILE *inDataFd ;
static FILE *inCtabFd ;
static FILE *inSegFd ;
static FILE *inStabFd ;

VencRegOffsetPara  *vencH1IndataRegRefAddress = NULL;
#define VENC_H1_MAX_enc_PIC_NUM   15
static uint32_t  venc_h1_enc_cost_time[VENC_H1_MAX_enc_PIC_NUM];
static uint32_t venc_h1_enc_single_cost_time = 0;
static uint32_t  indataSizeRef = 0;
static uint32_t  vencH1encPicNum = 0;

static uint32_t  venc_h1_irq_mode_enable = 0;
static uint32_t  venc_h1_dmmu_mode_enable = 0;
static uint32_t  venc_h1_irq_value = 0;

static uint32_t venc_h1_origin_mem_base = VENC_H1_MEM_BASE ;
static uint32_t venc_h1_dmmu_mem_base   = VENC_H1_MEM_BASE  ;

int venc_h1_h1_irq_handler(int irq,void * s){
	H1_INFO("%s\n",__func__);
	uint32_t address = VENC_H1_REG_BASE + 4; 
	venc_h1_irq_value =  readl(address);
	uint32_t temp = 0 ;
	int32_t ret = 1;
	if(venc_h1_irq_value &VENC_H1_IRQ_READY_BIT){
		if(venc_h1_irq_value & VENC_H1_IRQ_PICTURE_READY_BIT  ){
			H1_DBG("irq picture ready\n");
			ret =1 ;
		}
		else if(venc_h1_irq_value & VENC_H1_IRQ_STREM_ERR_BIT){
			H1_ERR("irq stream error\n");
			ret = -1;

		}else if(venc_h1_irq_value &VENC_H1_IRQ_BUS_ERR_BIT){
			H1_ERR("irq bus error  error\n");
			ret = -1;

		}else if(venc_h1_irq_value &VENC_H1_IRQ_TIMEOUT_BIT){
			H1_ERR("irq timeout error\n");
			ret = -1;
		}
		temp = venc_h1_irq_value &( ~(VENC_H1_IRQ_READY_BIT ));
		writel( temp,address);
	}
	else {
		H1_ERR("irq not happend");
		return -1;
	}
	return ret;
}
static void venc_dump_debug_info(void){
	static int picId = 0;
	uint32_t memList[] = {	 
							0x60000000,0x8000000,
							0x68000000,0x8000000,
							0x70000000,0x8000000,
						};
	int32_t i ;
	char fileName[64];
	FILE *fd =NULL;
	int32_t writeResult = 0;
	int32_t writeSize = 0;
	uint32_t offset ;
	int32_t number = sizeof(memList)/8;
	H1_DBG("dump file number -> %d\n",number);
	for(i=0;i<number;i+=2){
		offset =  memList[i];
		writeSize =  memList[i+1];
		memset(fileName,0,64);
		sprintf(fileName,"venc/h1/h1_mem_%d_0x%X_0x%X.bin",picId,offset,writeSize);
		H1_INFO("dump mem to file ->%s\n",fileName);
		fd = fopen(fileName,"wb");
		if(fd == NULL){
			H1_ERR("dump error -> 0x%X\n",memList[i]);
			return ;
		}
		writeResult =  fwrite((char *)(size_t)offset,writeSize,1,fd );
		if(writeResult !=  writeSize){
			H1_ERR("dump error -> 0x%X 0x%X\n",writeSize,writeResult);
			fclose(fd);
			return ;
		}
		fclose(fd);
	}
	picId++ ;
	return ;
}
static int venc_h1_i_blocking_handler(VencScriptCmd *cmd)
{
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint i = 0 ;
	uint32_t value ;
	int timeout =  cmd->para3 * 20; //40,about 20ms
	uint32_t offset = cmd->para1 *4 + VENC_H1_REG_BASE;
	venc_h1_irq_mode_enable = 0; //temp test
	if(venc_h1_irq_mode_enable ){
		H1_DBG("wait irq +++++\n");
		for(i = 0;i < timeout;i++){
			if (venc_h1_irq_value ){
				break;
			}
			udelay(1000);//wait 0.5ms
			if(i%10 == 0)
				H1_DBG("blocking->0x%X\n",readl(offset) );
		}
		if(venc_h1_irq_value == cmd->para2){
			venc_h1_irq_value = 0;
			H1_DBG("ok->%d\n",vencH1encPicNum);
			return 1;
		}
		else {
			H1_ERR("irq wait error -> 0x%X\n",readl(offset));
			venc_h1_irq_value = 0;
			return -1;
		}
	}
	else {
		H1_INFO("query reg 0x%X  %d times\n",offset,timeout);
		//for(i = 0 ;i < timeout;i++){
		for(i = 0 ;i< timeout;i++){
			udelay(500);//wait 0.5ms
			value =  readl(offset);
			if(cmd->para2 == value) {
				H1_DBG("ok->%d\n",vencH1encPicNum);
				value &= (~0x1100);
				writel(value,offset);
				
				//venc_dump_debug_info();
				return 1;
			}
			if(value &0x100 ) { //irq ready
				if(value & 0x1000){
					H1_DBG("ok\n");
					writel(0,offset);
					return 1;
				}
				else {
					H1_ERR("i block err -> %x %x  %x %d \n",cmd->para1,cmd->para2,readl(offset),cmd->para3);
					writel(0,offset);
					H1_ERR("clear irq -> %x",readl(offset));
					break;
				}
			}
			//if(i%30 == 0)
			//	H1_DBG("blocking->%d 0x%X\n",i,readl(offset) );
		}
	}
	return -1;
}
static int venc_h1_picture_handler(VencScriptCmd *cmd)
{
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	vencH1encPicNum = cmd->para1;
	return 1;
}  

static int venc_h1_slice_handler(VencScriptCmd *cmd)
{
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	udelay(3000);
	return 1;
}  
static int venc_h1_timer_pause_handler(VencScriptCmd *cmd)
{
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	return 1;
}  
static int venc_h1_c_handler(VencScriptCmd *cmd)
{
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	return 1;
} 
static int venc_h1_read_hw_id_handler(VencScriptCmd *cmd)
{
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	//uint32_t value = readl(VENC_H1_REG_BASE + cmd->para1*4);
	return 1;
}
static int venc_h1_read_enc_config_handler(VencScriptCmd *cmd)
{
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	//uint32_t value = readl(VENC_H1_REG_BASE + cmd->para1*4);
	return 1;
}
static void show_memcpy_info(char *mem,uint32_t offset,uint32_t range,char *msg){
	char *p = mem+offset ;
	int i = 0;
	H1_INFO("show %s data-> \n",msg);
	for (i = 0;i<range;i++){
		H1_INFO(" %02X ",p[i]);
	}
	H1_INFO("\nshow over \n");
}
static int venc_h1_r_handler(VencScriptCmd *cmd)
{
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	uint32_t regValue = 0;
	if (cmd->keyFlag == 1){
		regValue += venc_h1_origin_mem_base;
	}
	offset = VENC_H1_REG_BASE  +  offset*4;
	regValue = readl(offset) - venc_h1_origin_mem_base;
	if(regValue != cmd->para2){
		H1_INFO("read reg mistch -> 0x%X  0x%X\n",regValue,cmd->para2);
	}
	else {
		H1_INFO("read reg ok ->%x %x\n",regValue,cmd->para2);
	}
	return 1;
}
static int venc_h1_wait_handler(VencScriptCmd *cmd){
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	udelay(cmd->para1/10);
	return 1;
}
static int venc_h1_e_handler(VencScriptCmd *cmd){
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	udelay(cmd->para1/10);
	return 1;
}
/**
 * @brief venc_h1_m_handler 
 *i I_BLOCKING_ESC
 * @param cmd
 *
 * @return 
 */
static int venc_h1_m_handler(VencScriptCmd *cmd){
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset = cmd->para1 *4 + VENC_H1_REG_BASE;
	uint i = 0 ;
	uint32_t value ;
	int timeout =  cmd->para3 /10 ; //40,about 20ms
	H1_INFO("query reg 0x%X  %d times\n",offset,timeout);
	//for(i = 0 ;i < timeout;i++){
	for(i = 0 ;i< timeout;i++){
		udelay(500);//wait 0.5ms
		value =  readl(offset);
		if(cmd->para2 == value) {
			H1_DBG("+++++ok->%X %d\n",value,vencH1encPicNum);
			value &= (~0x1100);
//			writel(value,offset);

			//venc_dump_debug_info();
			return 1;
		}
		if(i%10 == 0)
			H1_DBG("m blocking->%d 0x%X\n",i,readl(offset) );
	}
	return -1;
	H1_ERR("%s not do now \n",__func__);
	return -1;
}
static int venc_h1_n_handler(VencScriptCmd *cmd){
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset = cmd->para1 *4 + VENC_H1_REG_BASE;
	uint i = 0 ;
	uint32_t value ;
	int timeout =  cmd->para3 /10 ; //40,about 20ms
	H1_INFO("query reg 0x%X  %d times\n",offset,timeout);
	//for(i = 0 ;i < timeout;i++){
	for(i = 0 ;i< timeout;i++){
		udelay(500);//wait 0.5ms
		value =  readl(offset);
		if(cmd->para2 == value) {
			H1_DBG("+++++ok->%X %d\n",value,vencH1encPicNum);
			value &= (~0x1100);
			writel(value,offset);

			//venc_dump_debug_info();
			return 1;
		}
		if(i%10 == 0)
			H1_DBG("n blocking->%d 0x%X\n",i,readl(offset) );
	}
	H1_ERR("%s not do now \n",__func__);
	return -1;
	H1_ERR("%s not do now \n",__func__);
	return -1;
}
/**
 * @brief venc_h1_o_handler 
 *  I_NONBLOCKING_ESC
 * @param cmd
 *
 * @return 
 */
static int venc_h1_o_handler(VencScriptCmd *cmd){
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset = cmd->para1 *4 + VENC_H1_REG_BASE;
	uint i = 0 ;
	uint32_t value ;
	int timeout =  cmd->para3 /10 ; //40,about 20ms
	H1_INFO("query reg 0x%X  %d times\n",offset,timeout);
	//for(i = 0 ;i < timeout;i++){
	for(i = 0 ;i< timeout;i++){
		udelay(500);//wait 0.5ms
		value =  readl(offset);
		if(cmd->para2 == value) {
			H1_DBG("+++++ok->%X %d\n",value,vencH1encPicNum);
			value &= (~0x1100);
	//		writel(value,offset);

			//venc_dump_debug_info();
			return 1;
		}
		if(i%10 == 0)
			H1_DBG("o blocking->%d 0x%X\n",i,readl(offset) );
	}
	H1_ERR("%s not do now \n",__func__);
	return -1;
}
static int venc_h1_w_handler(VencScriptCmd *cmd)
{
	uint32_t offset =  cmd->para1;
	uint32_t regValue = cmd->para2;
	if (cmd->keyFlag == 1){
		regValue += venc_h1_dmmu_mem_base ;
	}
	offset = offset *4;
	offset += VENC_H1_REG_BASE ;  
	H1_INFO("write reg-->%d %d 0x%X %X\n",cmd->keyFlag,cmd->para1,offset,regValue);
	writel(regValue,offset);
	return 1;
}
static int venc_h1_timer_start_handler(VencScriptCmd *cmd)
{
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	venc_h1_enc_single_cost_time = get_timer(0);
	return 1;
}
static int venc_h1_timer_end_handler(VencScriptCmd *cmd)
{
	venc_h1_enc_single_cost_time = get_timer(venc_h1_enc_single_cost_time);
	venc_h1_enc_cost_time[vencH1encPicNum] = venc_h1_enc_single_cost_time ;
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	return 1;
}           

static int	venc_h1_write_enc_ctables_handler(VencScriptCmd *cmd){			//17
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	FILE *fd = inCtabFd ;
	if(fd == NULL){
		H1_ERR("%s fd is null\n",__func__);
		return -1;
	}
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	int32_t readSize = fread(buf,cmd->para2,1,fd);
	if(readSize != cmd->para2){
		H1_ERR("load h1 ctab error ->%d %d\n",cmd->para2,readSize);
		return -1;
	}
	return 1;
}           
static int	venc_h1_write_enc_indata_handler(VencScriptCmd *cmd){   	//19
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	FILE *fd = inDataFd ;
	if(fd == NULL){
		H1_ERR("%s fd is null\n",__func__);
		return -1;
	}
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	int32_t readSize = fread(buf,cmd->para2,1,fd);
	if(readSize != cmd->para2){
		H1_ERR("load enc indata error ->%d %d\n",cmd->para2,readSize);
		return -1;
	}
	return 1;
}           
static int	venc_h1_write_enc_segment_handler(VencScriptCmd *cmd){			//16
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	FILE *fd = inSegFd ;
	if(fd == NULL){
		H1_ERR("%s fd is null\n",__func__);
		return -1;
	}
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	int32_t readSize = fread(buf,cmd->para2,1,fd);
	if(readSize != cmd->para2){
		H1_ERR("load h1 segment error ->%d %d\n",cmd->para2,readSize);
		return -1;
	}
	return 1;
}           
static int	venc_h1_write_enc_stab_data_handler(VencScriptCmd *cmd){			//18
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	FILE *fd = inStabFd ;
	if(fd == NULL){
		H1_ERR("%s fd is null\n",__func__);
		return -1;
	}
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	int32_t readSize = fread(buf,cmd->para2,1,fd);
	if(readSize != cmd->para2){
		H1_ERR("load h1 stab error ->%d %d\n",cmd->para2,readSize);
		return -1;
	}
	return 1;
}           
static int	venc_h1_check_enc_ctx_handler(VencScriptCmd *cmd){         //34
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outCtxBuf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_mvs_handler(VencScriptCmd *cmd){         //35
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outMvsBuf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_nals_handler(VencScriptCmd *cmd){        //36
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outNalsBuf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_prt1_handler(VencScriptCmd *cmd){      //37
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outPrt1Buf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}

	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_prt2_handler(VencScriptCmd *cmd){      //38
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outPrt2Buf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_prt3_handler(VencScriptCmd *cmd){      //37
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outPrt3Buf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}

	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_prt4_handler(VencScriptCmd *cmd){      //38
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outPrt4Buf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_rech_handler(VencScriptCmd *cmd){      //39
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outReChBuf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_relu_handler(VencScriptCmd *cmd){       //40
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outReLuBuf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_scale_handler(VencScriptCmd *cmd){       //40
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outScaleBuf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_strm_handler(VencScriptCmd *cmd){       //40
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outStrmBuf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
static int	venc_h1_check_enc_strm_am_handler(VencScriptCmd *cmd){       //40
	H1_INFO("%d %d %X %X %X %s\n",cmd->cmdIndex,cmd->keyFlag,cmd->para1,cmd->para2,cmd->para3,__func__);
	uint32_t offset =  cmd->para1;
	VencLinearMem *mem = &outStrmAmBuf;
	uint32_t memSize =  cmd->para2;
	if (cmd->keyFlag == 1){
		offset += venc_h1_origin_mem_base ; 
	}
	char *buf = (char *)(size_t)offset;
	memcpy(((char *)mem->vBuffer) +mem->offset , buf,memSize);
	mem->offset += memSize;
	return 1;
}           
int (*venc_h1_cmd_handler_table[])(VencScriptCmd *cmd) =
{
	NULL,
	venc_h1_c_handler  ,  			//1
	venc_h1_check_enc_ctx_handler ,						//2
	venc_h1_check_enc_mvs_handler,				//3
	venc_h1_check_enc_nals_handler,		//4
	venc_h1_check_enc_prt1_handler, 		//5
	venc_h1_check_enc_prt2_handler,						//6
	venc_h1_check_enc_prt3_handler,						//7
	venc_h1_check_enc_prt4_handler,				//8
	venc_h1_check_enc_rech_handler,			//9
	venc_h1_check_enc_relu_handler  ,         	//10
	venc_h1_check_enc_scale_handler,			//11
	venc_h1_check_enc_strm_handler,		 			//12
	venc_h1_check_enc_strm_am_handler,			//13
	venc_h1_e_handler,					//14
	venc_h1_i_blocking_handler,						//15
	venc_h1_picture_handler,			//16
	venc_h1_r_handler,			//17
	venc_h1_read_enc_config_handler,			//18
	venc_h1_read_hw_id_handler,   	//19
	venc_h1_timer_end_handler,  	 	//20
	venc_h1_timer_start_handler,   	//21
	venc_h1_w_handler,   	//22
	venc_h1_write_enc_ctables_handler,   	//23
	venc_h1_write_enc_indata_handler,   	//24
	venc_h1_write_enc_segment_handler,   		//25
	venc_h1_write_enc_stab_data_handler,   		//26
};
int venc_h1_load_file_to_mem(char *fileName,VencLinearMem *mem){
	H1_INFO("try load file to 0x%p-> %s --> ",mem,fileName);
	int fd = open(fileName,O_RDONLY);
	if(fd < 0){
		goto ERROR_PROCESS ;
	}
	mem->size = flen(fd);
	mem->vBuffer = malloc(mem->size);
	if(mem->vBuffer == NULL)
		goto ERROR_PROCESS ;
	int readSize = read(fd,mem->vBuffer,mem->size);
	if(readSize != mem->size )
		goto ERROR_PROCESS ;
	mem->offset = 0;
	H1_INFO("OK-->%d\n",readSize);
	return readSize;
ERROR_PROCESS :
	if(mem->vBuffer != NULL){
		free(mem->vBuffer);
		mem->vBuffer = NULL;
		mem->size = 0;
		mem->offset = 0;
	}
	if(fd != -1)
		close(fd);
	H1_INFO("ERR\n");
	return -1;
}

#define closefd(fd)  if(fd)fclose(fd) 

#define venc_h1_free_resource()  if(1){ \
	venc_free_linear_buffer(&inScriptBuf  ) ;\
	closefd(inDataFd);\
	closefd(inCtabFd);\
	closefd(inSegFd);\
	closefd(inStabFd);\
}


int32_t  venc_h1_try_open_read_file(char *fileName,FILE **fd) {
	if(strlen(fileName) ==0 ){
		H1_INFO("no input\n");
		*fd = NULL;
		return -1;
	}
	*fd =  fopen(fileName,"rb");
	if(*fd  == NULL){
		H1_ERR("h1 open file error -> %s\n",fileName);
		*fd = NULL;
		return -1;
	}
	H1_INFO("open ok ->%s %p\n",fileName,*fd);
	return 1;
}

int venc_h1_try_dump_mem_to_file(VencLinearMem *mem,char *dir,char *caseName,char *fileName,uint32_t crc){
	if(( mem->offset == 0 )  ||(!dir) || (!caseName) ||(!fileName) ){
		H1_INFO("%s :: no data to dump\n",fileName);
		venc_free_linear_buffer(mem);
		return 0;
	}
	char buf[128];
	memset(buf,0, 128);
	sprintf(buf,"%s_%s_%s.bin",dir,caseName,fileName);
 	venc_dump_mem_to_file(buf,mem,crc,fileName);
	venc_free_linear_buffer(mem);
	return 1;
}

int venc_h1_process(VENC_H1_TB_CFG *extb,char *path){
	//int inputFile1Fd ,inputFile2Fd,inputFile3Fd;
	H1_INFO("%s\n",__func__);
	VencLinearMem inScriptBuf = {0};		
	vencH1IndataRegRefAddress = 0;
	indataSizeRef = 0;
	vencH1encPicNum = 0 ;
	memset(venc_h1_enc_cost_time,0,VENC_H1_MAX_enc_PIC_NUM *4);
	H1_DBG("%s\n",extb->inData);
//irq 
	if(extb->irqEnable ){
		venc_h1_irq_mode_enable =  extb->irqEnable;
		int32_t ret = request_irq(VENC0_INT_ID,venc_h1_h1_irq_handler,"venc_h1_irq", NULL);
		H1_INFO("request_irq %d %d\n",ret,VENC0_INT_ID);
		venc_h1_irq_value = 0;
	}
//dmmu
	H1_INFO("dmmu status ->%d\n",extb->dmmuEnable);
	if(extb->dmmuEnable){
		venc_h1_dmmu_mode_enable = 1;
		int ret;
		ret = dmmu_enable("venc0");
		H1_DBG("dmmu enable -> %d\n",ret);
		venc_h1_origin_mem_base = VENC_H1_MEM_BASE ;
		venc_h1_dmmu_mem_base = dmmu_map("venc0",VENC_H1_MEM_BASE,VENC_H1_DEFAULT_DMMU_MAP_SIZE);
		H1_DBG("dmmu map ->  0x%X 0x%X\n",venc_h1_origin_mem_base,venc_h1_dmmu_mem_base);
	}
	else {
		venc_h1_origin_mem_base = VENC_H1_MEM_BASE ;
		venc_h1_dmmu_mem_base = VENC_H1_MEM_BASE ;
	}
	//load file 
	//venc_load_file_to_mem(extb->inScript,&inScriptBuf);
	venc_load_file_to_mem(extb->inScript,&inScriptBuf,0 );
	//prepare in put data file 
	venc_h1_try_open_read_file(extb->inData , 		&inDataFd) ;	
	venc_h1_try_open_read_file(extb->inCtab , 		&inCtabFd)  ;
	venc_h1_try_open_read_file(extb->inSeg , 		&inSegFd) ;	
	venc_h1_try_open_read_file(extb->inStab , 		&inStabFd) ;	


#define  VENC_MALLOC_MEMORY(b,c,a)	if(1){	CHECK_JUMP_ERROR( \
		venc_malloc_linear_buffer(&out##a##b,\
			extb->out##a##c[0] ==0 ?\
			H1_DEFAULT_OUTPUT_SIZE:extb->out##a##c[0] *0x100000 ) )  }


	//malloc output message{
	VENC_MALLOC_MEMORY(Buf,SizeCrc, Ctx  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, Mvs  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, Nals  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, Prt1  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, Prt2  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, Prt3  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, Prt4  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, ReCh  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, ReLu  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, Scale  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, Strm  );
	VENC_MALLOC_MEMORY(Buf,SizeCrc, StrmAm  );


	int funcNumber = sizeof(venc_h1_cmd_handler_table)/sizeof(size_t);

	int i =0;
	VencScriptCmd *cmd;
	uint32_t cmdNumber = inScriptBuf.size / sizeof(VencScriptCmd);
	H1_INFO("funcNumber -> %d %d\n",funcNumber-1,cmdNumber);
	for(i = 0;i<cmdNumber;i++){
		cmd = (VencScriptCmd *)inScriptBuf.vBuffer  +  i;
		if(cmd->cmdIndex > funcNumber ){
			H1_ERR("cmd key exceed the funcNumber -> %d\n",cmd->cmdIndex);
		}
		else {
			int (*cmd_handler)(VencScriptCmd *cmd) = *(venc_h1_cmd_handler_table + cmd->cmdIndex );
			CHECK_JUMP_ERROR((*cmd_handler)(cmd) );
		}
		if(vencH1encPicNum >= extb->picNum ){
			H1_DBG("encode pic number is reached -> %d %d\n",vencH1encPicNum,extb->picNum);
			break;
		}
	}
	
	venc_h1_try_dump_mem_to_file(&outCtxBuf,path,extb->caseName,"Ctx",extb->outCtxSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outMvsBuf,path,extb->caseName,"Mvs",extb->outMvsSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outNalsBuf,path,extb->caseName,"Nals",extb->outNalsSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outPrt1Buf,path,extb->caseName,"Prt1",extb->outPrt1SizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outPrt2Buf,path,extb->caseName,"Prt2",extb->outPrt2SizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outPrt3Buf,path,extb->caseName,"Prt3",extb->outPrt3SizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outPrt4Buf,path,extb->caseName,"Prt4",extb->outPrt4SizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outReChBuf,path,extb->caseName,"ReCh",extb->outReChSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outReLuBuf,path,extb->caseName,"ReLu",extb->outReLuSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outScaleBuf,path,extb->caseName,"Scale",extb->outScaleSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outStrmBuf,path,extb->caseName,"Strm",extb->outStrmSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outStrmAmBuf,path,extb->caseName,"StrmAm",extb->outStrmAmSizeCrc[1]);

	venc_h1_free_resource();	

	venc_h1_irq_mode_enable = 0;
	if(extb->dmmuEnable){
		dmmu_disable("venc0");
	}
	venc_h1_dmmu_mode_enable = 0;
	H1_DBG("timecost -> ");
	for(i = 0;i<vencH1encPicNum;i++){
		H1_DBG(" %3d ",venc_h1_enc_cost_time[i]);
	}
	H1_DBG("\n");
	return 1;
ERROR_PROCESS :

	venc_h1_try_dump_mem_to_file(&outCtxBuf,path,extb->caseName,"Ctx",extb->outCtxSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outMvsBuf,path,extb->caseName,"Mvs",extb->outMvsSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outNalsBuf,path,extb->caseName,"Nals",extb->outNalsSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outPrt1Buf,path,extb->caseName,"Prt1",extb->outPrt1SizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outPrt2Buf,path,extb->caseName,"Prt2",extb->outPrt2SizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outPrt3Buf,path,extb->caseName,"Prt3",extb->outPrt3SizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outPrt4Buf,path,extb->caseName,"Prt4",extb->outPrt4SizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outReChBuf,path,extb->caseName,"ReCh",extb->outReChSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outReChBuf,path,extb->caseName,"ReLu",extb->outReLuSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outScaleBuf,path,extb->caseName,"Scale",extb->outScaleSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outStrmBuf,path,extb->caseName,"Strm",extb->outStrmSizeCrc[1]);
	venc_h1_try_dump_mem_to_file(&outStrmAmBuf,path,extb->caseName,"StrmAm",extb->outStrmAmSizeCrc[1]);
	venc_h1_free_resource();	
	venc_h1_irq_mode_enable = 0;
	if(extb->dmmuEnable){
		dmmu_disable("venc0");
	}

	venc_h1_irq_mode_enable = 0;
	H1_ERR("ERROR_PROCESS\n");
	if(extb->dmmuEnable){
		dmmu_disable("venc0");
	}
	venc_h1_dmmu_mode_enable = 0;
	return -1;
}
void show_h1_tb_cfg(VENC_H1_TB_CFG *cfg){
	H1_INFO("caseName -> %s\n",cfg->caseName);
	H1_INFO("inScript -> %s\n",cfg->inScript);
	H1_INFO("inData -> %s\n",cfg->inData );
	H1_INFO("inCtab -> %s\n",cfg->inCtab );
	H1_INFO("inSeg -> %s\n",cfg->inSeg );
	H1_INFO("inStab -> %s\n",cfg->inStab );

	H1_INFO("outCtxSizeCrc ->%d  %d \n",cfg->outCtxSizeCrc[0],cfg->outCtxSizeCrc[1]);
	H1_INFO("outMvsSizeCrc ->%d  %d \n",cfg->outMvsSizeCrc[0],cfg->outMvsSizeCrc[1]);
	H1_INFO("outNalsSizeCrc ->%d  %d \n",cfg->outNalsSizeCrc[0],cfg->outNalsSizeCrc[1]);
	H1_INFO("outPrt1SizeCrc ->%d  %d \n",cfg->outPrt1SizeCrc[0],cfg->outPrt1SizeCrc[1]);
	H1_INFO("outPrt2SizeCrc ->%d  %d \n",cfg->outPrt2SizeCrc[0],cfg->outPrt2SizeCrc[1]);
	H1_INFO("outPrt3SizeCrc ->%d  %d \n",cfg->outPrt3SizeCrc[0],cfg->outPrt3SizeCrc[1]);
	H1_INFO("outPrt4SizeCrc ->%d  %d \n",cfg->outPrt4SizeCrc[0],cfg->outPrt4SizeCrc[1]);
	H1_INFO("outReChSizeCrc ->%d  %d \n",cfg->outReChSizeCrc[0],cfg->outReChSizeCrc[1]);
	H1_INFO("outReLuSizeCrc ->%d  %d \n",cfg->outReLuSizeCrc[0],cfg->outReLuSizeCrc[1]);
	H1_INFO("outScaleSizeCrc ->%d  %d \n",cfg->outScaleSizeCrc[0],cfg->outScaleSizeCrc[1]);
	H1_INFO("outStrmSizeCrc ->%d  %d \n",cfg->outStrmSizeCrc[0],cfg->outStrmSizeCrc[1]);
	H1_INFO("outStrmAmSizeCrc ->%d  %d \n",cfg->outStrmAmSizeCrc[0],cfg->outStrmAmSizeCrc[1]);

	H1_INFO("picNum -> %d\n",cfg->picNum);
	H1_INFO("irqEnable -> %d\n",cfg->irqEnable);
	H1_INFO("dmmuEnable -> %d\n",cfg->dmmuEnable);
}
int venc_h1_load_para(char *paraFile,VENC_H1_TB_CFG *cfg){
	memset(cfg,0,sizeof(VENC_H1_TB_CFG));
	para_struct_t	para[] = {
		{"caseName", 			char_p,1, cfg->caseName },
		{"inScript", 			char_p,1, cfg->inScript },
		{"inData", 				char_p,1, cfg->inData },
		{"inCtab",	 			char_p,1, cfg->inCtab },
		{"inSeg",	 			char_p,1, cfg->inSeg },
		{"inStab",	 			char_p,1, cfg->inStab },

		{"outCtxSizeCrc", 		u32_p,	2, cfg->outCtxSizeCrc },
		{"outMvsSizeCrc", 		u32_p,	2, cfg->outMvsSizeCrc },
		{"outNalsSizeCrc", 		u32_p,	2, cfg->outNalsSizeCrc },
		{"outPrt1SizeCrc", 		u32_p,	2, cfg->outPrt1SizeCrc },
		{"outPrt2SizeCrc", 		u32_p,	2, cfg->outPrt2SizeCrc },
		{"outPrt3SizeCrc", 		u32_p,	2, cfg->outPrt3SizeCrc },
		{"outPrt4SizeCrc", 		u32_p,	2, cfg->outPrt4SizeCrc },
		{"outReChSizeCrc", 		u32_p,	2, cfg->outReChSizeCrc },
		{"outReLuSizeCrc", 		u32_p,	2, cfg->outReLuSizeCrc },
		{"outScaleSizeCrc", 		u32_p,	2, cfg->outScaleSizeCrc },
		{"outStrmSizeCrc", 		u32_p,	2, cfg->outStrmSizeCrc },
		{"outStrmAmSizeCrc", 		u32_p,	2, cfg->outStrmAmSizeCrc },

		{"picNum", 				u32_p,1, &(cfg->picNum)  },
		{"dmmuEnable", 			u32_p,1, &(cfg->dmmuEnable)  },
		{"irqEnable", 			u32_p,1, &(cfg->irqEnable)  },
	};
	int32_t para_num = sizeof(para) /sizeof(para_struct_t);
	H1_INFO("try load cfg file -> %s \n",paraFile);
	int32_t ret =  load_para_from_cfg_file(paraFile,para,para_num);
	if(ret < 0){
		LOG_ERR("load h1 basic para error \n");
		return -1;
	}
	show_h1_tb_cfg(cfg);
	return 1;
}
int venc_h1_get_default_config(VENC_H1_TB_CFG *tb){
	VENC_H1_TB_CFG def = {
		"Def_h1_1152_3",
		"venc/h1/res/case_1152/inScript.bin",

		"venc/h1/res/case_1152/inData.bin",
		"", //in CTables 
		"", //in Segmetn
		"", //in Stab

		{0,1},//ctx counter
		{0,1},//mvs
		{0,1},//nals
		{0,1},//prt1
		{0,1},//prt2
		{0,1},//prt3
		{0,1},//prt4
		{0,1},//recon lu
		{0,1},//recon ch
		{0,1},//scale
		{0,1},//strm
		{0,1},//strm am
		1,
		0,//irq
		0,//dmmu
	};
	memcpy(tb,&def,sizeof(VENC_H1_TB_CFG));
	return 1;
}

int32_t venc_h1_entry(int argc,char *argv[])
{
	if(argc < 2){
		H1_DBG("err,need more para");
		return TB_RET_FAIL;
	}
	VENC_H1_TB_CFG cfg  ;
	int ret = 0;
	if(strncmp(argv[2],"def",3) ==  0){
		H1_INFO("load def cfg \n");
		venc_h1_get_default_config(&cfg);
		H1_INFO("h1 process\n");
		ret = venc_h1_process(&cfg,"venc/h1/def");
	}
	else {
		ret = venc_h1_load_para(argv[2],&cfg);
		if(ret >= 0){
			ret =  venc_h1_process(&cfg,argv[2]);
		}
	}
	if(ret < 0){
		return TB_RET_FAIL;
	}
	else {
		TB_RET_MANUAL;
	}
}
