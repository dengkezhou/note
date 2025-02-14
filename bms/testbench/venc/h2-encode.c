//********************************************************************
//(Copyright 2008) Verisilicon Inc. All Rights Reserved
//Company confidential and Properietary information.
//This information may not be disclosed to unauthorized individual.
//********************************************************************
//
// VeriSilicon Microelectronics Co.,Ltd.
//
// File Name: h2.c
// Author:    wgwei
// Version:   1.0
// Created:   Aug 14, 2013
// Modified:
// Description:
//********************************************************************
#include "h2-encode.h"
#include <common.h>
#include <venc-common.h>
#include <asm/io.h>
#if 0
	uint32_t outStrmSizeCrc[2];
	uint32_t outPlumSizeCrc[2];
	uint32_t outTblSizeCrc[2];
	uint32_t outLuSizeCrc[2];
	uint32_t outChSizeCrc[2];
	uint32_t outNalsSizeCrc[2];
#endif
static VencLinearMem inScriptBuf ;
//static VencLinearMem inDataBuf ;

static FILE *inDataFd = NULL;

static VencLinearMem outStrmBuf ;
static VencLinearMem outPlumBuf ;
static VencLinearMem outTblBuf ;
static VencLinearMem outLuBuf ;
static VencLinearMem outChBuf ;
static VencLinearMem outNalsBuf ;

uint32_t  vencIndataRegRefAddress = 0;
uint32_t  vencIndataSizeRef = 0;
uint32_t  encPicNum = 0;

uint32_t venc1_origin_mem_base = VENC_H2_MEM_BASE ;
uint32_t venc1_dmmu_mem_base   = VENC_H2_MEM_BASE  ;

uint32_t  venc1_irq_mode_enable = 0;
uint32_t  venc1_irq_value = 0;
uint32_t  venc_h2_encode_time[VENC_H2_MAX_ENCODE_PIC_NUM];
int venc1_h2_irq_handler(int irq,void * s){
	H2_INFO("%s\n",__func__);
	uint32_t address = VENC_H2_REG_BASE + 4; 
	venc1_irq_value =  readl(address);
	int ret = 1;
	uint32_t temp = 0;
	if(venc1_irq_value){
		if((venc1_irq_value & VENC_H2_FRAME_READY) || (venc1_irq_value & VENC_H2_SLICE_READY)) {
			H2_DBG("frame or slice ready irq -> 0x%X\n",venc1_irq_value);
			ret =1 ;
		}
		else {
			H2_ERR("WRONG IRQ\n");
			ret = -1;
			
		}
		temp = venc1_irq_value &(~VENC_H2_IRQ_READY);
		writel(temp,address);
	}
	if(ret ==1 )
		H2_INFO("h2 irq test ok\n");
	return ret;
}
static void venc_h2_dump_debug_info(void){
	static int picId = 0;
	uint32_t memList[] = {0x600d0000, 
						0x600e0000,
						0x60130000,
						0x602b0000
						};
	int32_t i ;
	char fileName[64];
	FILE *fd =NULL;
	int32_t writeResult = 0;
	int32_t number = sizeof(memList)/4;
	H2_DBG("dump file number -> %d\n",number);
	for(i=0;i<number;i++){
		memset(fileName,0,64);
		sprintf(fileName,"venc/hevc/h2_mem_%d_0x%X.bin",picId,memList[i]);
		H2_INFO("dump mem to file ->%s\n",fileName);
		fd = fopen(fileName,"wb");
		if(fd == NULL){
			H2_ERR("dump error -> 0x%X\n",memList[i]);
			return ;
		}
		writeResult =  fwrite((char *)(size_t)memList[i],0x100000,1,fd );
		if(writeResult !=  0x100000){
			H2_ERR("dump error -> 0x%X\n",memList[i]);
			fclose(fd);
			return ;
		}
		fclose(fd);
	}
	picId++;
	return ;
}
static int venc_h2_i_blocking_handler(ScriptCmd *cmd)
{
	static blockingCounter = 0;
	H2_INFO("blocking -> %d %d %d %X %X %X %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3,blockingCounter++);
	uint i = 0 ;
	uint32_t value ;
	int ret = 0;
	int timeout =  1000 ;
	if(venc1_irq_mode_enable){
		for (i = 0;i<timeout;i++){
			if(venc1_irq_value){
				break;
			}
			else {
				H2_DBG(" not expect interupt\n");
				udelay(500);
			}
			H2_DBG("h2 irq happened is ok \n");
		}
		value = venc1_irq_value ;
		//add irq deal handler
		if((uint32_t)cmd->para2 ==(uint32_t) value) {
			if(value & VENC_H2_SLICE_READY){
				H2_INFO("slice ok\n");
						;
				value = value  &(~( VENC_H2_SLICE_READY | VENC_H2_IRQ_READY  ));
				H2_INFO("clean value -> %X\n",value);
				writel(value,VENC_H2_REG_BASE + cmd->para1);
				ret = 1;

			}
			else if (value & VENC_H2_FRAME_READY){
				H2_DBG("pic ok->%d\n",encPicNum);
				value = value  &(~( VENC_H2_IRQ_READY | VENC_H2_FRAME_READY ));
				H2_INFO("clean value -> %X\n",value);
				writel(value,VENC_H2_REG_BASE + cmd->para1);
				ret = 1;
			}
			else {
				H2_DBG("?????????????\n");
				ret = -1;
			}

		}
		else if(( ( 0x905 == value ) ||(0x901 == value )  ) && (0x901 == cmd->para2) ) { //second slice 
			H2_INFO("slice 2 ok\n");
			value = value  &(~( VENC_H2_SLICE_READY | VENC_H2_IRQ_READY | VENC_H2_FRAME_READY ));
			H2_DBG("clean value -> %X\n",value);
			writel(value,VENC_H2_REG_BASE + cmd->para1);
			ret = 1;
		}
	}
	else {
		for(i = 0 ;i < timeout ;i++){
			udelay(500);
			value =  readl(VENC_H2_REG_BASE + cmd->para1);
			if((uint32_t)cmd->para2 ==(uint32_t) value) {
				if(value & VENC_H2_SLICE_READY){
					H2_INFO("slice ok\n");
					value = value  &(~( VENC_H2_SLICE_READY | VENC_H2_IRQ_READY  ));
					H2_INFO("clean value -> %X\n",value);
					writel(value,VENC_H2_REG_BASE + cmd->para1);
					ret = 1;

				}
				else if (value & VENC_H2_FRAME_READY){
					H2_DBG("pic ok->%d\n",encPicNum);
					value = value  &(~( VENC_H2_IRQ_READY | VENC_H2_FRAME_READY ));
					H2_INFO("clean value -> %X\n",value);
					writel(value,VENC_H2_REG_BASE + cmd->para1);
					ret = 1;
				}
				else {
					H2_DBG("?????????????\n");
					ret = -1;
				}

				break;
			}
			else if(( 0x905 == value ) && (0x901 == cmd->para2) ) { //second slice 
					H2_INFO("slice2 ok 2\n");
					value = value  &(~( VENC_H2_SLICE_READY | VENC_H2_IRQ_READY | VENC_H2_FRAME_READY ));
					H2_INFO("clean value -> %X\n",value);
					writel(value,VENC_H2_REG_BASE + cmd->para1);
					ret = 1;
					break;
				
			}
//			if(i%10 == 0)
//				H2_DBG("blocking->%d 0x%X\n",i,readl(VENC_H2_REG_BASE+cmd->para1) );
		}
	}
	//venc_h2_dump_debug_info();
	if(ret != 1){
		H2_ERR("i block err -> %x %x  %x %d \n",cmd->para1,cmd->para2,readl(VENC_H2_REG_BASE + cmd->para1),cmd->para3);
		return -1;
	}
	return 1;
}
static int venc_h2_picture_handler(ScriptCmd *cmd)
{
	H2_INFO("picture -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	encPicNum = cmd->para1;
	return 1;
}  
static int venc_h2_c_handler(ScriptCmd *cmd)
{
	H2_INFO("coment -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	return 1;
} 
static int venc_h2_read_hw_id_handler(ScriptCmd *cmd)
{
	H2_INFO("read hw id -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	uint32_t value = readl(VENC_H2_REG_BASE + H2_DEC_HW_ID);
	return 1;
}
static int venc_h2_read_enc_config_handler(ScriptCmd *cmd)
{
	H2_INFO("read env cfg -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	uint32_t value = readl(VENC_H2_REG_BASE + H2_DEC_CONFIG);
	return 1;
}
static void show_memcpy_info(char *mem,uint32_t offset,uint32_t range,char *msg){
	char *p = mem+offset ;
	int i = 0;
	H2_INFO("show %s data-> \n",msg);
	for (i = 0;i<range;i++){
		H2_INFO(" %02X ",p[i]);
	}
	H2_INFO("\nshow over \n");
}
static int venc_h2_write_enc_indata_handler(ScriptCmd *cmd)
{
	H2_INFO("write indata -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	vencIndataRegRefAddress =  cmd->para1; // set input stream ref reg
	vencIndataSizeRef =  cmd->para2; // set input stream ref size
	uint32_t offset = cmd->para1;
	if(cmd->keyFlag ) {
		offset += venc1_dmmu_mem_base ;	
	}
	char *buf =  (char *)(size_t)(offset) ;
	int32_t readRet =  fread(buf,cmd->para2,1,inDataFd);
	if(readRet != cmd->para2){
		H2_ERR("load h2 data error -> %d %d\n",cmd->para2,readRet);
		return -1;
	}
//	H2_DBG("old ref->0x%X  %d\n",vencIndataRegRefAddress,vencIndataSizeRef);
	return 1;
}
static int venc_h2_r_handler(ScriptCmd *cmd)
{
	H2_INFO("read  -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	uint32_t offset  = cmd->para1;
	uint32_t regValue = readl(offset+VENC_H2_REG_BASE);
	if (regValue != cmd->para2){
		H2_INFO("read -> %x  %x\n",regValue,cmd->para2);
	}
	
	return 1;
}
static int venc_h2_w_handler(ScriptCmd *cmd)
{
	
	uint32_t value = cmd->para2;
	
	if(cmd->keyFlag ) {
		value += venc1_dmmu_mem_base ;	
	}
	writel(value ,VENC_H2_REG_BASE + cmd->para1);
	H2_INFO("w reg -> %d %d %d %d %d %d %x\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3,value);
	return 1;
}
static  uint32_t venc_h2_start_time = 0;
static int venc_h2_timer_start_handler(ScriptCmd *cmd)
{
	H2_INFO("start -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	venc_h2_start_time =  get_timer(0);
	return 1;
}
static int venc_h2_timer_end_handler(ScriptCmd *cmd)
{
	venc_h2_start_time =  get_timer(venc_h2_start_time);
	H2_INFO("time end -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
//	H2_DBG("pic encode cost -> %d\n",venc_h2_start_time);
	if(encPicNum >  VENC_H2_MAX_ENCODE_PIC_NUM)
		H2_DBG("wrong pic index \n");
	else 
		venc_h2_encode_time[encPicNum] =  venc_h2_start_time ;
	return 1;
}           


static int	venc_h2_flush_enc_complum_handler (ScriptCmd *cmd){
	H2_INFO("flush -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	uint32_t offset  = cmd->para1;
	if(cmd->keyFlag ) {
		offset += venc1_origin_mem_base ;	
	}
	memset((char *)(size_t)(offset),0,cmd->para2);

	return 1;
}
/**
 * @brief venc_h2_check_enc_strm_handler 
 *
 * @param cmd
 * para1  -> mem start 
 * para2  -> mem size 
 * para3  -> valid lenght 
 * if size > lenght , extra will be set to 0
 *
 * @return 
 */
static int	venc_h2_check_enc_strm_handler (ScriptCmd *cmd){
	H2_INFO("check strm -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	uint32_t offset  = cmd->para1;
	if(cmd->keyFlag ) {
		offset += venc1_origin_mem_base ;	
	}
	//H2_INFO("offset->%d\n",offset);
	memcpy((char *)outStrmBuf.vBuffer + outStrmBuf.offset ,
			(char *)(size_t)(offset) ,
			cmd->para2);
	if(cmd->para2 < cmd->para3){
		H2_ERR("strm size and length error \n");
		return -1;
	}
	else if(cmd->para2 == cmd->para3) {
		outStrmBuf.offset += cmd->para2;
	}
	else {
		uint32_t i = 0;
		uint32_t fillBytes = cmd->para2 - cmd->para3;
//		H2_DBG("fill 0 from %d : %d\n",cmd->para3,cmd->para2);
		char *buf = (char *)outStrmBuf.vBuffer ;
		buf+= outStrmBuf.offset + cmd->para2 -16 ;
		for (;i< fillBytes;i++){
			buf[i] = 0;
		}
		outStrmBuf.offset += cmd->para2;
	}
	return 1;
}
static int	venc_h2_check_enc_reccomplum_handler (ScriptCmd *cmd){
	H2_INFO("check plum -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
#ifdef VENC_H2_FULL_DUMP
	uint32_t offset  = cmd->para1;
	if(cmd->keyFlag ) {
		offset += venc1_origin_mem_base ;	
	}
	memcpy((char *)outPlumBuf.vBuffer + outPlumBuf.offset ,
			(char *)(size_t)(offset) ,
			cmd->para2);
	outPlumBuf.offset += cmd->para2;
#endif
	return 1;
}
static int	venc_h2_check_enc_recon4n_lu_handler (ScriptCmd *cmd){

	H2_INFO("check lu -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
#ifdef VENC_H2_FULL_DUMP
	uint32_t offset  = cmd->para1;
	if(cmd->keyFlag ) {
		offset += venc1_origin_mem_base ;	
	}
	H2_INFO("offset->%d\n",offset);
	memcpy((char *)outLuBuf.vBuffer + outLuBuf.offset ,
			(char *)(size_t)(offset) ,
			cmd->para2);
	outLuBuf.offset += cmd->para2;
#endif
	return 1;
}
static int	venc_h2_check_enc_recon_ch_handler (ScriptCmd *cmd){ 
	H2_INFO("check ch -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
#ifdef VENC_H2_FULL_DUMP
	uint32_t offset  = cmd->para1;
	if(cmd->keyFlag ) {
		offset += venc1_origin_mem_base ;	
	}
	memcpy((char *)outChBuf.vBuffer + outChBuf.offset ,
			(char *)(size_t)(offset) ,
			cmd->para2);
	outChBuf.offset += cmd->para2;
#endif
	return 1;
}
static int	venc_h2_check_enc_nals_handler (ScriptCmd *cmd){
	H2_INFO("check nals -> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
	uint32_t offset  = cmd->para1;
	if(cmd->keyFlag ) {
		offset += venc1_origin_mem_base ;	
	}
	H2_INFO("nals start ->%p %d\n",offset,cmd->para2);
	char *buf = (char *)outNalsBuf.vBuffer + outNalsBuf.offset ;
	memcpy(buf,
			(char *)(size_t)(offset) ,
			cmd->para2);
	outNalsBuf.offset += cmd->para2;
	if(cmd->para2 >= cmd->para3){
		uint32_t i  = cmd->para3;
		uint32_t size = cmd->para2;
		for(;i<size;i++){
			buf[i] = 0;
		}
	}
	else {
		H2_ERR("nals data error \n");
	}
	return 1;
}
static int	venc_h2_check_enc_reccomptbl_handler (ScriptCmd *cmd){
	H2_INFO("check tbl-> %d %d %d %d %d %d\n",cmd->cmdIndex,cmd->keyFlag,cmd->reserved,cmd->para1,cmd->para2,cmd->para3);
#ifdef VENC_H2_FULL_DUMP
	uint32_t offset  = cmd->para1;
	if(cmd->keyFlag ) {
		offset += venc1_origin_mem_base ;	
	}
	memcpy((char *)outTblBuf.vBuffer + outTblBuf.offset ,
			(char *)(size_t)(offset) ,
			cmd->para2);
	outTblBuf.offset += cmd->para2;
#endif
	return 1;
}
int (*venc_h2_cmd_handler_table[])(ScriptCmd *cmd) =
{
	NULL,
	venc_h2_picture_handler  ,
	venc_h2_c_handler ,
	venc_h2_read_hw_id_handler,
	venc_h2_read_enc_config_handler,
	venc_h2_write_enc_indata_handler,
	venc_h2_flush_enc_complum_handler,
	venc_h2_check_enc_strm_handler,
	venc_h2_check_enc_reccomplum_handler,
	venc_h2_check_enc_recon4n_lu_handler,
	venc_h2_check_enc_recon_ch_handler ,
	venc_h2_check_enc_nals_handler,
	venc_h2_check_enc_reccomptbl_handler,
	venc_h2_r_handler,
	venc_h2_w_handler,
	venc_h2_i_blocking_handler,
	venc_h2_timer_start_handler,
	venc_h2_timer_end_handler   ,         
};


int venc_h2_try_dump_mem_to_file(VencLinearMem *mem,char *dir,char *caseName,char *fileName,uint32_t crc){
	if(( mem->offset == 0 )  ||(!dir) || (!caseName) ||(!fileName) ){
		H2_DBG("no dump\n");
		venc_free_linear_buffer(mem);
		return 0;
	}
	char buf[128];
	memset(buf,0, 128);
	sprintf(buf,"%s_%s_%s.bin",dir,caseName,fileName);
 	venc_dump_mem_to_file(buf,mem,crc,fileName);
	venc_free_linear_buffer(mem);
}
int venc_h2_process(VENC_H2_TB_CFG *extb,char *path){
	//int inputFile1Fd ,inputFile2Fd,inputFile3Fd;
	VencLinearMem inputScriptBuf = {0};		
	vencIndataRegRefAddress = 0;
	vencIndataSizeRef = 0;
	encPicNum = 0;
	if(extb->irqEnable){
		venc1_irq_mode_enable =  extb->irqEnable;
		int32_t ret = request_irq(VENC1_INT_ID,venc1_h2_irq_handler,"venc1_irq");
		H2_DBG("request irq ->%d %d\n",ret,VENC1_INT_ID);
	}
//	extb->dmmuEnable = 1;
	if(extb->dmmuEnable){
		int32_t ret =  dmmu_enable("venc1");
		venc1_origin_mem_base = VENC_H2_MEM_BASE ; 
		venc1_dmmu_mem_base = dmmu_map("venc1",venc1_origin_mem_base,H2_DEFAULT_DMMU_MAP_SIZE);
		H2_DBG("dmmu->%d 0x%X 0x%X\n",ret,venc1_origin_mem_base,venc1_dmmu_mem_base);
	}
	else {
		venc1_origin_mem_base = VENC_H2_MEM_BASE ; 
		venc1_dmmu_mem_base   = VENC_H2_MEM_BASE ;
	}
	memset(venc_h2_encode_time,0,4*VENC_H2_MAX_ENCODE_PIC_NUM);
	// open file for read
	CHECK_JUMP_ERROR(venc_load_file_to_mem(extb->inScript, &inScriptBuf,0)  );
	inDataFd= fopen(extb->inData,"rb");
	if(inDataFd == NULL){
		H2_ERR("open data file error \n");
		goto ERROR_PROCESS;
	}
	//malloc output message
	CHECK_JUMP_ERROR( venc_malloc_linear_buffer(&outStrmBuf,extb->outStrmSizeCrc[0] ==0 ?\
			H2_DEFAULT_OUTPUT_SIZE:extb->outStrmSizeCrc[0] *1024000 ) );
	CHECK_JUMP_ERROR( venc_malloc_linear_buffer(&outPlumBuf,extb->outPlumSizeCrc[0] ==0 ?\
			H2_DEFAULT_OUTPUT_SIZE:extb->outPlumSizeCrc[0] *1024000 ) );
	CHECK_JUMP_ERROR( venc_malloc_linear_buffer(&outTblBuf,extb->outTblSizeCrc[0] ==0 ?\
			H2_DEFAULT_OUTPUT_SIZE:extb->outTblSizeCrc[0] *1024000 ) );
	CHECK_JUMP_ERROR( venc_malloc_linear_buffer(&outLuBuf,extb->outLuSizeCrc[0] ==0 ?\
			H2_DEFAULT_OUTPUT_SIZE:extb->outLuSizeCrc[0] *1024000 ) );
	CHECK_JUMP_ERROR( venc_malloc_linear_buffer(&outChBuf,extb->outChSizeCrc[0] ==0 ?\
			H2_DEFAULT_OUTPUT_SIZE:extb->outChSizeCrc[0] *1024000 ) );
	CHECK_JUMP_ERROR( venc_malloc_linear_buffer(&outNalsBuf,extb->outNalsSizeCrc[0] ==0 ?\
			H2_DEFAULT_OUTPUT_SIZE:extb->outNalsSizeCrc[0] *1024000 ) );

	H2_INFO("out strm -> %p\n",outStrmBuf.vBuffer);
	H2_INFO("out plum -> %p\n",outPlumBuf.vBuffer);
	H2_INFO("out tbl  -> %p\n",outTblBuf.vBuffer);
	H2_INFO("out  lu  -> %p\n",outLuBuf.vBuffer);
	H2_INFO("out ch   -> %p\n",outChBuf.vBuffer);
	H2_INFO("out nals -> %p\n",outNalsBuf.vBuffer);

	int funcNumber = sizeof(venc_h2_cmd_handler_table)/sizeof(size_t);
//	H2_DBG("funcNumber -> %d\n",funcNumber - 1);
	int i =0;
	uint32_t *cmd;
	ScriptCmd *script  ;
	for(i = 0;i<inScriptBuf.size;i+=16){
		if((inScriptBuf.size - i )  < sizeof(ScriptCmd)){
			//reach to end 
			break;
		}
		cmd = (uint32_t *)( (char *)inScriptBuf.vBuffer + i );
		script = (ScriptCmd *)cmd;
		if(script->cmdIndex > funcNumber ){
			H2_ERR("cmd key exceed the funcNumber -> %d\n",script->cmdIndex);
		}
		else {
			int (*cmd_handler)(ScriptCmd *cmd) = *(venc_h2_cmd_handler_table + script->cmdIndex );
		//	printf("cmd->%X\n",script->cmdIndex);
			CHECK_JUMP_ERROR((*cmd_handler)(script) );
		}
		if(encPicNum >= extb->encPicNum ){
			H2_DBG("encode pic number is reached -> %d %d\n",encPicNum,extb->encPicNum);
			break;
		}
	}
	venc_h2_try_dump_mem_to_file(&outStrmBuf,path,extb->caseName,"strm",extb->outStrmSizeCrc[1]);
	venc_h2_try_dump_mem_to_file(&outNalsBuf,path,extb->caseName,"nals",extb->outNalsSizeCrc[1]);
#ifdef  VENC_H2_FULL_DUMP
	venc_h2_try_dump_mem_to_file(&outTblBuf,path,extb->caseName,"tbl",extb->outTblSizeCrc[1]);
	venc_h2_try_dump_mem_to_file(&outLuBuf,path,extb->caseName,"lu",extb->outLuSizeCrc[1]);
	venc_h2_try_dump_mem_to_file(&outChBuf,path,extb->caseName,"ch",extb->outChSizeCrc[1]);
	venc_h2_try_dump_mem_to_file(&outPlumBuf,path,extb->caseName,"plum",extb->outPlumSizeCrc[1]);
#endif
	H2_DBG("timecost-> ");
	for(i = 0;i< extb->encPicNum;i++){
		H2_DBG("%3d ",venc_h2_encode_time[i]);
	}
	H2_DBG("\n");
	venc_free_linear_buffer(&inScriptBuf);
	venc1_irq_mode_enable = 0;
	if(extb->dmmuEnable){
		dmmu_disable("venc1");
	}
	if(inDataFd)
		fclose(inDataFd);
	return 1;
ERROR_PROCESS :
	venc_h2_try_dump_mem_to_file(&outStrmBuf,extb->outDir,extb->caseName,"strm",extb->outStrmSizeCrc[1]);
	venc_h2_try_dump_mem_to_file(&outPlumBuf,extb->outDir,extb->caseName,"plum",extb->outPlumSizeCrc[1]);
	venc_h2_try_dump_mem_to_file(&outTblBuf,extb->outDir,extb->caseName,"tbl",extb->outTblSizeCrc[1]);
	venc_h2_try_dump_mem_to_file(&outLuBuf,extb->outDir,extb->caseName,"lu",extb->outLuSizeCrc[1]);
	venc_h2_try_dump_mem_to_file(&outChBuf,extb->outDir,extb->caseName,"ch",extb->outChSizeCrc[1]);
	venc_h2_try_dump_mem_to_file(&outNalsBuf,extb->outDir,extb->caseName,"nals",extb->outNalsSizeCrc[1]);
	venc_free_linear_buffer(&inScriptBuf);
	H2_ERR("ERROR_PROCESS\n");
	venc1_irq_mode_enable = 0;
	if(extb->dmmuEnable){
		dmmu_disable("venc1");
	}
	if(inDataFd)
		fclose(inDataFd);
	return -1;
}
void show_h2_tb_cfg(VENC_H2_TB_CFG *cfg){
	H2_INFO("caseName -> %s\n",cfg->caseName);
	H2_INFO("inScript -> %s\n",cfg->inScript);
	H2_INFO("inData -> %s\n",cfg->inData);
	H2_INFO("out dir -> %s\ndd",cfg->outDir);

	H2_INFO("encPicNum -> %d\n",cfg->encPicNum);

	H2_INFO("outStrmSize->%d 0x%X\n",cfg->outStrmSizeCrc[0],cfg->outStrmSizeCrc[1]);
	H2_INFO("outPlumSize->%d 0x%X\n",cfg->outPlumSizeCrc[0],cfg->outPlumSizeCrc[1]);
	H2_INFO("outTblSize->%d 0x%X\n",cfg->outTblSizeCrc[0],cfg->outTblSizeCrc[1]);
	H2_INFO("outLuSize->%d 0x%X\n",cfg->outLuSizeCrc[0],cfg->outLuSizeCrc[1]);
	H2_INFO("outChSize->%d 0x%X\n",cfg->outChSizeCrc[0],cfg->outChSizeCrc[1]);
	H2_INFO("outNalsSize->%d 0x%X\n",cfg->outNalsSizeCrc[0],cfg->outNalsSizeCrc[1]);
	H2_INFO("irq enable -> %d\n",cfg->irqEnable);
	H2_INFO("dmmuEnable -> %d\n",cfg->dmmuEnable);

}
int venc_h2_load_para(char *paraFile,VENC_H2_TB_CFG *cfg){
	memset(cfg,0,sizeof(VENC_H2_TB_CFG));
	para_struct_t	para[] = {
		{"caseName", 		char_p,1, cfg->caseName },
		{"inScript", 		char_p,1, cfg->inScript },
		{"inData", 			char_p,1, cfg->inData },
		{"outDir", 			char_p,1, cfg->outDir},

		{"encPicNum", 				u32_p,1, &(cfg->encPicNum)  },

		{"outStrmSizeCrc", 			u32_p,	2, cfg->outStrmSizeCrc },
		{"outPlumSizeCrc", 			u32_p,	2, cfg->outPlumSizeCrc },
		{"outTblStrmSizeCrc", 		u32_p,	2, cfg->outTblSizeCrc },
		{"outLuSizeCrc", 		u32_p,	2, cfg->outLuSizeCrc },
		{"outChSizeCrc", 		u32_p,	2, cfg->outChSizeCrc },
		{"outNalsSizeCrc", 		u32_p,	2, cfg->outNalsSizeCrc },
		{"dmmuEnable", 	u32_p,1, &(cfg->dmmuEnable)  },
		{"irqEnable", 	u32_p,1, &(cfg->irqEnable)  },
	};
	int32_t para_num = sizeof(para) /sizeof(para_struct_t);
	H2_INFO("try load cfg file -> %s \n",paraFile);
	int32_t ret =  load_para_from_cfg_file(paraFile,para,para_num);
	if(ret < 0){
		LOG_ERR("load h2 basic para error \n");
		return -1;
	}
	return 1;
}
int venc_h2_get_default_config(VENC_H2_TB_CFG *tb){
	VENC_H2_TB_CFG def = {
		"Def_hevc_8013_1",
		"venc/h2/res/case_8013/inScript.bin",
		"venc/h2/res/case_8013/inData.bin",
		"venc/h2/",
		10,//enc pic number
		{0,0x7db79c83},//strm
		{0,0},//lum
		{0,0},//bl
		{0,0},//lu
		{0,0},//ch
		{0,0x31cfe091},//nal
		0,//irqEnable
		0 //dmmuEnable
	};
	memcpy(tb,&def,sizeof(VENC_H2_TB_CFG));
	return 1;
}



int32_t venc_h2_entry(int argc,char *argv[])
{
	if(argc < 2){
		H2_DBG("err,need more para");
		return TB_RET_FAIL;
	}
	VENC_H2_TB_CFG cfg  ;
	int ret = 0;
	if(strncmp(argv[2],"def",3) ==  0){
		H2_INFO("load def cfg \n");
		venc_h2_get_default_config(&cfg);
		show_h2_tb_cfg(&cfg);
		H2_INFO("h2 process\n");
		ret = venc_h2_process(&cfg,"venc/h2/Def");
	}
	else {
		ret = venc_h2_load_para(argv[2],&cfg);
		show_h2_tb_cfg(&cfg);
		if(ret >= 0){
			ret =  venc_h2_process(&cfg,argv[2]);
		}
	}
	if(ret < 0){
		return TB_RET_FAIL;
	}
	else {
		TB_RET_MANUAL;
	}
}
