#include<npu.h>

#ifdef CONFIG_COMPILE_RTL
void AluFunction_0_test_dump(){
    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x820004f8, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x820009f0, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x82000ee8, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x820013e0, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x820018d8, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x82001dd0, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x820022c8, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x820027c0, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x82002cb8, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x820031b0, 0x000000e8);
    soc_dump0(RTL_DUMP_ADDR + 0x820036a8, 0x000000e8);
}


void kernel3x3_pooling0(){
    unsigned int offset =0x82000000;
    for(int j =0;j<3;j++){

        for(int i =0 ;i < 102; i++){
            
            if(i%2==0){
                soc_dump0(RTL_DUMP_ADDR + offset, 0x00000010);
                offset = offset +0xc;
            }else{
                soc_dump0(RTL_DUMP_ADDR + offset, 0x00000010);
                offset = offset +0x10;
            }
            
            
        }
        offset = offset + 0x940 - 0x10;
        
    }
}

void sp_AluFunction_0_dump(){
    unsigned int offset =0x82000000;
    for(int j =0;j<14;j++){
        
        for(int i =0 ;i < 25; i++){
            soc_dump0(RTL_DUMP_ADDR + offset, 0x00000010);
            if((i+1)%4==0){
                offset = offset + 0x10;
            }else{
                offset = offset + 0xc;
            }
               
        }
        offset = offset + 0xaf8 - 0xc;
        printf("\n");
        printf("\n");
    }
}

void sp_AluFunction_2_dump(){
    soc_dump0(RTL_DUMP_ADDR + 0x82004bcc, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004bd4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004be0, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004be8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004bf4, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004bfc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c08, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c10, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c1c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c24, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c30, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c38, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c44, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c4c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c58, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c60, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c6c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c74, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c80, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c88, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c94, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004c9c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004ca8, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004cb0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004cbc, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004cc4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004cd0, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004cd8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004ce4, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004cec, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004cf8, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d00, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d0c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d14, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d20, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d28, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d34, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d3c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d48, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d50, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d5c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d64, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d70, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d78, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d84, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d8c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d98, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004da0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004dac, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004db4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004dc0, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004dc8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004dd4, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004ddc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004de8, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004df0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004dfc, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004e04, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004e10, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004e18, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004e24, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004e2c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004e38, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004e40, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82004e4c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ad4c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ad54, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ad60, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ad68, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ad74, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ad7c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ad88, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ad90, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ad9c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ada4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200adb0, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200adb8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200adc4, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200adcc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200add8, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ade0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200adec, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200adf4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae00, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae08, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae14, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae1c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae28, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae30, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae3c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae44, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae50, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae58, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae64, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae6c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae78, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae80, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae8c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200ae94, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aea0, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aea8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aeb4, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aebc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aec8, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aed0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aedc, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aee4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aef0, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200aef8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af04, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af0c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af18, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af20, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af2c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af34, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af40, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af48, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af54, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af5c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af68, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af70, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af7c, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af84, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af90, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200af98, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200afa4, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200afac, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200afb8, 0x0000000c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200afc0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200afcc, 0x0000000c);
}
void sp_AluFunction_test1_dump(){
    
    soc_dump0(RTL_DUMP_ADDR + 0x82004030, 0x0000004c);
    soc_dump0(RTL_DUMP_ADDR + 0x820040d0, 0x00000048);
    soc_dump0(RTL_DUMP_ADDR + 0x82004170, 0x00000048);
    soc_dump0(RTL_DUMP_ADDR + 0x8200420c, 0x0000004c);
    soc_dump0(RTL_DUMP_ADDR + 0x820042ac, 0x0000004c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200434c, 0x00000048);
    soc_dump0(RTL_DUMP_ADDR + 0x820043ec, 0x00000048);
    soc_dump0(RTL_DUMP_ADDR + 0x82004488, 0x0000004c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004704, 0x0000004c);
    soc_dump0(RTL_DUMP_ADDR + 0x820047a4, 0x0000004c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004844, 0x00000048);
    soc_dump0(RTL_DUMP_ADDR + 0x820048e4, 0x00000048);
    soc_dump0(RTL_DUMP_ADDR + 0x82004980, 0x0000004c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004a20, 0x0000004c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004ac0, 0x00000048);
    soc_dump0(RTL_DUMP_ADDR + 0x82004b60, 0x00000048);
}

void nn_read_and_ot_dump( ){

    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82000280, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82000500, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82000780, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82000a00, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82000c80, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82000f00, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82001180, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82001400, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82001680, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82001900, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82001b80, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82001e00, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82002080, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82002300, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82002580, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82002800, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82002a80, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82002d00, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82002f80, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82003200, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82003480, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82003700, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82003980, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82003c00, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82003e80, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82004100, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82004380, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82004600, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82004880, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82004b00, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82004d80, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82005000, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82005280, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82005500, 0x00000208);
    soc_dump0(RTL_DUMP_ADDR + 0x82005780, 0x00000208);

}

void storageSame_dump(){
    soc_dump0(RTL_DUMP_ADDR + 0x82069128, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x820696d8, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x82069c88, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206a238, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206a7e8, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206ad98, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206b348, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206b8f8, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206bea8, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206c468, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206ca18, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206cfc8, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206d578, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206db28, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206e0d8, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206e688, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206ec38, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206f1e8, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206f7a8, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x8206fd58, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x82070308, 0x000002e8);
    soc_dump0(RTL_DUMP_ADDR + 0x82010b4c, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82010d40, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82010f34, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82011128, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x8201131c, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82011510, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82011704, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x820118f8, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82011aec, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82011ce0, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82011ed4, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x820120cc, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x820122c0, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x820124b4, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x820126a8, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x8201289c, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82012a90, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82012c84, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82012e78, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x8201306c, 0x000000c4);
    soc_dump0(RTL_DUMP_ADDR + 0x82013260, 0x000000c4);
}


void nn_write_dump(){

    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x0011ee88);
    soc_dump0(RTL_DUMP_ADDR + 0x8211f080, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x8211f300, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x8211f580, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x8211f800, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x8211fa80, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x8211fd00, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x8211ff80, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82120200, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82120480, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82120700, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82120980, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82120c00, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82120e80, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82121100, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82121380, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82121600, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82121880, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82121b00, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82121d80, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82122000, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82122280, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82122500, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82122780, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82122a00, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82122c80, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82122f00, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82123180, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82123400, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82123680, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82123900, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82123b80, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82123e00, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82124080, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82124300, 0x00000088);
    soc_dump0(RTL_DUMP_ADDR + 0x82124580, 0x00000088);
}

void convStride_1_dump(){
    unsigned int offset =0x82000000;
    for(int j =0;j<7;j++){
        soc_dump0(RTL_DUMP_ADDR + offset, 0x00210);
        offset = offset + 0x690;
        for(int i =0 ;i < 26; i++){
            soc_dump0(RTL_DUMP_ADDR + offset, 0x00c);
          
            offset = offset + 0x14;
            
        }
        offset = offset + 0x256c - 0x14;
        
    }
}

void in2ndChnum_16_dump(){
    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000014, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000028, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200003c, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000054, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000068, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200007c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000090, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820000a8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820000bc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820000d0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820000e4, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820000fc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000110, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000124, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000138, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000150, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000164, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000178, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200018c, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820001a4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820001b8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820001cc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820001e0, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820001f8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200020c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000220, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000234, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x8200024c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000260, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000274, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000288, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820002a0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820002b4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820002c8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820002dc, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820002f4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000308, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200031c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000330, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000348, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200035c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000380, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000394, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820003a8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820003bc, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820003d4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820003e8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820003fc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000410, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000428, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200043c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000450, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000464, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x8200047c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000490, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820004a4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820004b8, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820004d0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820004e4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820004f8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200050c, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000524, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000538, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200054c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000560, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000578, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200058c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820005a0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820005b4, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820005cc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820005e0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820005f4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000608, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000620, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000634, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000648, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200065c, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000674, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000688, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200069c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820006b0, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820006c8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820006dc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000700, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000714, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000728, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200073c, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000754, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000768, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200077c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000790, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820007a8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820007bc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820007d0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820007e4, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820007fc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000810, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000824, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000838, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000850, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000864, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000878, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200088c, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820008a4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820008b8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820008cc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820008e0, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820008f8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x8200090c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000920, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000934, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x8200094c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000960, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000974, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000988, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820009a0, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820009b4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820009c8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x820009dc, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x820009f4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000a08, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000a1c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000a30, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000a48, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000a5c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000a80, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000abc, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000afc, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000b3c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000b7c, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000bb8, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000bf8, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000c38, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000c78, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000cb4, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82000cf4, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000d34, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000d74, 0x00000010);
    soc_dump0(RTL_DUMP_ADDR + 0x82000db0, 0x00000014);

}

void inChnum_16_dump(){
    unsigned int offset =0x82000000;
     int i=0;
    for(int j =0;j<17;j++){
        soc_dump0(RTL_DUMP_ADDR + offset, 0x00000238);
        if(j%2==0){
            offset = offset +0x4fc;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0000000c);
            offset = offset +0x14;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0000000c);
            for( i =1 ;i < 30; i++){
           
            	 if(i%2==0){
            	 	offset = offset +0x14;
		            soc_dump0(RTL_DUMP_ADDR + offset, 0x0000000c);
                }else{
                    offset = offset +0x10;
                    soc_dump0(RTL_DUMP_ADDR + offset, 0x0000000c);
                
                    
                }   
        	}
        	offset = offset + 0x1bd8;
		
        }else{
            offset = offset +0x500;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0000000c);
            offset = offset +0x10;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0000000c);
            for( i =0 ;i < 29; i++){
           
            	 if(i%2==0){
            	 	offset = offset +0x14;
		            soc_dump0(RTL_DUMP_ADDR + offset, 0x0000000c);
                }else{
                    offset = offset +0x10;
                    soc_dump0(RTL_DUMP_ADDR + offset, 0x0000000c);
                    
                }   
        	}
        	offset = offset + 0x1bd8;
        } 
            
        
        
        
    }

}

void image_Type_0_2_dump(){
    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000078);
    soc_dump0(RTL_DUMP_ADDR + 0x8200015c, 0x0000007c);
    soc_dump0(RTL_DUMP_ADDR + 0x820002bc, 0x00000078);
    soc_dump0(RTL_DUMP_ADDR + 0x82000418, 0x0000007c);
    soc_dump0(RTL_DUMP_ADDR + 0x82000840, 0x00000078);
    soc_dump0(RTL_DUMP_ADDR + 0x8200099c, 0x0000007c);
    soc_dump0(RTL_DUMP_ADDR + 0x82000afc, 0x00000078);
    soc_dump0(RTL_DUMP_ADDR + 0x82000c58, 0x0000007c);
    soc_dump0(RTL_DUMP_ADDR + 0x82001080, 0x00000078);
    soc_dump0(RTL_DUMP_ADDR + 0x820011dc, 0x0000007c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200133c, 0x00000078);
    soc_dump0(RTL_DUMP_ADDR + 0x82001498, 0x0000007c);
    soc_dump0(RTL_DUMP_ADDR + 0x820018c0, 0x00000078);
    soc_dump0(RTL_DUMP_ADDR + 0x82001a1c, 0x0000007c);
    soc_dump0(RTL_DUMP_ADDR + 0x82001b7c, 0x00000078);
    soc_dump0(RTL_DUMP_ADDR + 0x82001cd8, 0x0000007c);
}

void kernel_image_Date1_dump(){
    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x820000d0, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x820001a4, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82000274, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x820009d8, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82000aa8, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x82000b7c, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82000c4c, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x820013b0, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82001480, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x82001554, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82001624, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x82001d88, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82001e58, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x82001f2c, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82001ffc, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x82002760, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82002830, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x82002904, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x820029d4, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x82003138, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82003208, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x820032dc, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x820033ac, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x82003b10, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82003be0, 0x0000005c);
    soc_dump0(RTL_DUMP_ADDR + 0x82003cb4, 0x00000058);
    soc_dump0(RTL_DUMP_ADDR + 0x82003d84, 0x0000005c);
}

void inimage_Data_7_8_dump(){
    
    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000003d8);
    soc_dump0(RTL_DUMP_ADDR + 0x82004020, 0x000003d8);
    soc_dump0(RTL_DUMP_ADDR + 0x82008040, 0x000003d8);
    soc_dump0(RTL_DUMP_ADDR + 0x8200c060, 0x000003d8);
    soc_dump0(RTL_DUMP_ADDR + 0x82010080, 0x000003d8);
    soc_dump0(RTL_DUMP_ADDR + 0x820140a0, 0x000003d8);
}

void kernel1_pooling_0_dump(){
    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82000170, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x820002e4, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82000454, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x820005c8, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82000738, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x820008ac, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82000a1c, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82000b90, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82000d00, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82000e74, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82000fe4, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82001158, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x820012c8, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x8200143c, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x820015ac, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82001720, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82001890, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82001a04, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82001b74, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82001ce8, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82001e58, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82001fcc, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200213c, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x820022b0, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82002420, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82002594, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82002704, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82002878, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x820029e8, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82002b5c, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82002ccc, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82002e40, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82002fb0, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82003124, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82003294, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82003408, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82003578, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x820036ec, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x8200385c, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x820039d0, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82003b40, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82003cb4, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82003e24, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x82003f98, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x82004108, 0x00000090);
    soc_dump0(RTL_DUMP_ADDR + 0x8200427c, 0x0000008c);
    soc_dump0(RTL_DUMP_ADDR + 0x820043ec, 0x00000090);
}


void kernelData_0_2_dump(){
    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x00000128);
    soc_dump0(RTL_DUMP_ADDR + 0x82002960, 0x00000128);
    soc_dump0(RTL_DUMP_ADDR + 0x820052c0, 0x00000128);
    soc_dump0(RTL_DUMP_ADDR + 0x82007c20, 0x00000128);
    soc_dump0(RTL_DUMP_ADDR + 0x8200a580, 0x00000128);
    soc_dump0(RTL_DUMP_ADDR + 0x8200cee0, 0x00000128);
    soc_dump0(RTL_DUMP_ADDR + 0x8200f840, 0x00000128);
}

void kernelData_7_dump(){
    soc_dump0(RTL_DUMP_ADDR + 0x82000000, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8200022c, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x820022c0, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x820024ec, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82004580, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x820047ac, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82006840, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82006a6c, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82008b00, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82008d2c, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8200adc0, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8200afec, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8200d080, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8200d2ac, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8200f340, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8200f56c, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82011600, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8201182c, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x820138c0, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82013aec, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82015b80, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82015dac, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x82017e40, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8201806c, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8201a100, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8201a32c, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8201c3c0, 0x000000c8);
    soc_dump0(RTL_DUMP_ADDR + 0x8201c5ec, 0x000000c8);
}


void control1_ch2_fromV11V12(){
    soc_dump0(RTL_DUMP_ADDR + 0x82001a38, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82001a50, 0x00000018);
    soc_dump0(RTL_DUMP_ADDR + 0x82001a6c, 0x00000018);
    soc_dump0(RTL_DUMP_ADDR + 0x82001a88, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82001aa4, 0x00000014);
    soc_dump0(RTL_DUMP_ADDR + 0x82001abc, 0x00000018);
    soc_dump0(RTL_DUMP_ADDR + 0x82001ad8, 0x00000018);
    soc_dump0(RTL_DUMP_ADDR + 0x82001af4, 0x00000014);
}

//0x19668
void outChNum_16_dump(){
    unsigned int offset =0x82000000;
    for(int j =0;j<7;j++){
        for(int i =0 ;i < 51; i++){

            soc_dump0(RTL_DUMP_ADDR + offset, 0x10);
            offset = offset +0x40;
        }
        offset = offset + 0x15580 - 0x40;
        
    }
}


void OutimageData_0_2_dump(){
    

    unsigned int offset = 0x82000000;
    
    int temp = 0 ;
    
    
    for(int j =0;j<13;j++){
        temp = j%4;
        // printf("temp = %d  %d\n",temp,j);
        switch (temp)
        {
        case 0:
            for(int i =0 ;i<77;i++){

            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            // soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x0c;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x10);
            offset += 0x10;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;

            }
             soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x0c;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x10);
            offset = offset + 0x19668;
            
            break;
        case 1:
             
            for(int i =0 ;i<77;i++){

                soc_dump0(RTL_DUMP_ADDR + offset, 0x10);
                offset += 0x10;
                soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0x10;
                soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0x10;
                soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0xc;

            }
            soc_dump0(RTL_DUMP_ADDR + offset, 0x10);
            offset += 0x10;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset = offset + 0x19668;
            
            break;
        case 2:

            
            for(int i =0 ;i<77;i++){

                soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0x10;
                soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0x10;
                soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0xc;
                soc_dump0(RTL_DUMP_ADDR + offset, 0x10);
                offset += 0x10;

            }
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset = offset + 0x19668;
            
            break;
        case 3:
            for(int i =0 ;i<77;i++){

            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0xc;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x10);
            offset += 0x10;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;

            }
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;
            soc_dump0(RTL_DUMP_ADDR + offset, 0x0c);
            offset = offset + 0x19668;
            
            break;
        default:
            break;
        }
        
    }
}


void OutimageData_1_7_dump(){
    
    unsigned int offset = 0x82000000;
    int size = 0x10;
    for(int j =0 ;j < 13; j++){

        if(j%2 == 0){
            size = 0x0c;
            for(int i = 0;i<310;i++){
                soc_dump0(RTL_DUMP_ADDR + offset, size);
                // printf("addr = %x %x\t",offset,size);
                if(i%2==0){
                        size = 0x10;
                        offset =offset + 0x1c;
                        // printf("addr = %x\t",offset);
                }else{
                        size = 0x0c;
                        offset = offset+0x20;
                        // printf("addr = %x\t",offset);
                }
            }
            offset = offset - 0x20 + 0x8598;
        }else{
            size = 0x10;
            for(int i = 0;i<310;i++){
                soc_dump0(RTL_DUMP_ADDR + offset, size);
                // printf("addr = %x %x\t",offset,size);
                if(i%2==0){
                        size = 0x0c;
                        offset =offset + 0x20;
                        // printf("addr = %x\t",offset);
                }else{
                        size = 0x10;
                        offset = offset+0x1c;
                        // printf("addr = %x\t",offset);
                }
            }
            offset = offset - 0x1c + 0x8598;
        }
    }
   
}

void OutimageData_4_dump(){
    unsigned int offset = 0x82000000;
    int size = 0x10;
    for(int j =0 ;j < 13; j++){

        if(j%2 == 0){
            size = 0x0c;
            for(int i = 0;i<310;i++){

                // printf("addr = %x %x\t",offset,size);
                soc_dump0(RTL_DUMP_ADDR + offset, size);
                if(i%2==0){
                        size = 0x10;
                        offset =offset + 0x1c;
                        // printf("addr = %x\t",offset);
                }else{
                        size = 0x0c;
                        offset = offset+0x20;
                        // printf("addr = %x\t",offset);
                }

            }

            offset = offset - 0x20 + 0x32cd0;
        }else{
            size = 0x10;
            for(int i = 0;i<310;i++){

                // printf("addr = %x %x\t",offset,size);
                soc_dump0(RTL_DUMP_ADDR + offset, size);
                if(i%2==0){
                        size = 0x0c;
                        offset =offset + 0x20;
                        // printf("addr = %x\t",offset);
                }else{
                        size = 0x10;
                        offset = offset+0x1c;
                        // printf("addr = %x\t",offset);
                }

            }
            
            offset = offset - 0x1c + 0x32cd0;
        }
    }
    
}

void OutimageData_8_dump(){
    //0x46668
   
    unsigned int offset = 0x82000000;
    for(int j =0 ;j<13;j++){
        for(int i =0;i<310;i++){
            soc_dump0(RTL_DUMP_ADDR + offset,0x00000010);
            // printf("addr = %x %d\t",offset,i);
            offset = offset + 0x3c;
        }
        offset = offset +0x46668 -0x3c;
            
    }
}
#else
int AluFunction_0_test_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820004f8, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820009f0, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000ee8, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820013e0, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820018d8, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001dd0, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820022c8, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820027c0, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002cb8, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820031b0, 0x000000e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820036a8, 0x000000e8);
    return ret;
}


int kernel3x3_pooling0(){
    unsigned int offset =0x82000000;
    int ret = 0;
    for(int j =0;j<3;j++){

        for(int i =0 ;i < 102; i++){
            
            if(i%2==0){
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x00000010);
                offset = offset +0xc;
            }else{
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x00000010);
                offset = offset +0x10;
            }
            
            
        }
        offset = offset + 0x940 - 0x10;
        
    }
    return ret;
}

int sp_AluFunction_0_dump(){
    unsigned int offset =0x82000000;
    int ret = 0;
    for(int j =0;j<14;j++){
        
        for(int i =0 ;i < 25; i++){
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x00000010);
            if((i+1)%4==0){
                offset = offset + 0x10;
            }else{
                offset = offset + 0xc;
            }
               
        }
        offset = offset + 0xaf8 - 0xc;
        printf("\n");
        printf("\n");
    }
    return ret;
}

int sp_AluFunction_2_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004bcc, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004bd4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004be0, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004be8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004bf4, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004bfc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c08, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c10, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c1c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c24, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c30, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c38, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c44, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c4c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c58, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c60, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c6c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c74, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c80, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c88, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c94, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004c9c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004ca8, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004cb0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004cbc, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004cc4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004cd0, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004cd8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004ce4, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004cec, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004cf8, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d00, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d0c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d14, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d20, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d28, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d34, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d3c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d48, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d50, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d5c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d64, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d70, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d78, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d84, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d8c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d98, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004da0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004dac, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004db4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004dc0, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004dc8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004dd4, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004ddc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004de8, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004df0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004dfc, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004e04, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004e10, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004e18, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004e24, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004e2c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004e38, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004e40, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004e4c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ad4c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ad54, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ad60, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ad68, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ad74, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ad7c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ad88, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ad90, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ad9c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ada4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200adb0, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200adb8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200adc4, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200adcc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200add8, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ade0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200adec, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200adf4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae00, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae08, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae14, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae1c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae28, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae30, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae3c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae44, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae50, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae58, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae64, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae6c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae78, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae80, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae8c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200ae94, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aea0, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aea8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aeb4, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aebc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aec8, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aed0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aedc, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aee4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aef0, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200aef8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af04, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af0c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af18, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af20, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af2c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af34, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af40, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af48, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af54, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af5c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af68, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af70, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af7c, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af84, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af90, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200af98, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200afa4, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200afac, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200afb8, 0x0000000c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200afc0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200afcc, 0x0000000c);
    return ret;
}
int sp_AluFunction_test1_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004030, 0x0000004c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820040d0, 0x00000048);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004170, 0x00000048);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200420c, 0x0000004c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820042ac, 0x0000004c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200434c, 0x00000048);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820043ec, 0x00000048);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004488, 0x0000004c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004704, 0x0000004c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820047a4, 0x0000004c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004844, 0x00000048);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820048e4, 0x00000048);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004980, 0x0000004c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004a20, 0x0000004c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004ac0, 0x00000048);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004b60, 0x00000048);
    return ret;
}

int nn_read_and_ot_dump( ){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000280, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000500, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000780, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000a00, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000c80, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000f00, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001180, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001400, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001680, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001900, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001b80, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001e00, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002080, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002300, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002580, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002800, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002a80, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002d00, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002f80, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003200, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003480, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003700, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003980, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003c00, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003e80, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004100, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004380, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004600, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004880, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004b00, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004d80, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82005000, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82005280, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82005500, 0x00000208);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82005780, 0x00000208);
    return ret;
}

int storageSame_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82069128, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820696d8, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82069c88, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206a238, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206a7e8, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206ad98, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206b348, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206b8f8, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206bea8, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206c468, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206ca18, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206cfc8, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206d578, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206db28, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206e0d8, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206e688, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206ec38, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206f1e8, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206f7a8, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8206fd58, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82070308, 0x000002e8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82010b4c, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82010d40, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82010f34, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82011128, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8201131c, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82011510, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82011704, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820118f8, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82011aec, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82011ce0, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82011ed4, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820120cc, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820122c0, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820124b4, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820126a8, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8201289c, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82012a90, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82012c84, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82012e78, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8201306c, 0x000000c4);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82013260, 0x000000c4);
    return ret;
}


int nn_write_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x0011ee88);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8211f080, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8211f300, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8211f580, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8211f800, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8211fa80, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8211fd00, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8211ff80, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82120200, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82120480, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82120700, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82120980, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82120c00, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82120e80, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82121100, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82121380, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82121600, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82121880, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82121b00, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82121d80, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82122000, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82122280, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82122500, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82122780, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82122a00, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82122c80, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82122f00, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82123180, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82123400, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82123680, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82123900, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82123b80, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82123e00, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82124080, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82124300, 0x00000088);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82124580, 0x00000088);
    return ret;
}

int convStride_1_dump(){
    unsigned int offset =0x82000000;
    int ret = 0;
    for(int j =0;j<7;j++){
        ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x00210);
        offset = offset + 0x690;
        for(int i =0 ;i < 26; i++){
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x00c);
          
            offset = offset + 0x14;
            
        }
        offset = offset + 0x256c - 0x14;
        
    }
    return ret;
}

int in2ndChnum_16_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000014, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000028, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200003c, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000054, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000068, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200007c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000090, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820000a8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820000bc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820000d0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820000e4, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820000fc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000110, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000124, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000138, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000150, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000164, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000178, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200018c, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820001a4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820001b8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820001cc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820001e0, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820001f8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200020c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000220, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000234, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200024c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000260, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000274, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000288, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820002a0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820002b4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820002c8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820002dc, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820002f4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000308, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200031c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000330, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000348, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200035c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000380, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000394, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820003a8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820003bc, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820003d4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820003e8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820003fc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000410, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000428, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200043c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000450, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000464, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200047c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000490, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820004a4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820004b8, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820004d0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820004e4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820004f8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200050c, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000524, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000538, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200054c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000560, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000578, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200058c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820005a0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820005b4, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820005cc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820005e0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820005f4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000608, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000620, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000634, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000648, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200065c, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000674, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000688, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200069c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820006b0, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820006c8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820006dc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000700, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000714, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000728, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200073c, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000754, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000768, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200077c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000790, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820007a8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820007bc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820007d0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820007e4, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820007fc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000810, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000824, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000838, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000850, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000864, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000878, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200088c, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820008a4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820008b8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820008cc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820008e0, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820008f8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200090c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000920, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000934, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200094c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000960, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000974, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000988, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820009a0, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820009b4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820009c8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820009dc, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820009f4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000a08, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000a1c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000a30, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000a48, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000a5c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000a80, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000abc, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000afc, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000b3c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000b7c, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000bb8, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000bf8, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000c38, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000c78, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000cb4, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000cf4, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000d34, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000d74, 0x00000010);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000db0, 0x00000014);
    return ret;

}

int inChnum_16_dump(){
    unsigned int offset =0x82000000;
    int ret = 0;
     int i=0;
    for(int j =0;j<17;j++){
        ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x00000238);
        if(j%2==0){
            offset = offset +0x4fc;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0000000c);
            offset = offset +0x14;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0000000c);
            for( i =1 ;i < 30; i++){
           
            	 if(i%2==0){
            	 	offset = offset +0x14;
		            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0000000c);
                }else{
                    offset = offset +0x10;
                    ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0000000c);
                
                    
                }   
        	}
        	offset = offset + 0x1bd8;
		
        }else{
            offset = offset +0x500;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0000000c);
            offset = offset +0x10;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0000000c);
            for( i =0 ;i < 29; i++){
           
            	 if(i%2==0){
            	 	offset = offset +0x14;
		            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0000000c);
                }else{
                    offset = offset +0x10;
                    ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0000000c);
                    
                }   
        	}
        	offset = offset + 0x1bd8;
        } 
            
        
        
        
    }
    return ret;

}

int image_Type_0_2_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x00000078);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200015c, 0x0000007c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820002bc, 0x00000078);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000418, 0x0000007c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000840, 0x00000078);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200099c, 0x0000007c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000afc, 0x00000078);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000c58, 0x0000007c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001080, 0x00000078);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820011dc, 0x0000007c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200133c, 0x00000078);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001498, 0x0000007c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820018c0, 0x00000078);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001a1c, 0x0000007c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001b7c, 0x00000078);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001cd8, 0x0000007c);
    return ret;
}

int kernel_image_Date1_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820000d0, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820001a4, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000274, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820009d8, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000aa8, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000b7c, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000c4c, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820013b0, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001480, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001554, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001624, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001d88, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001e58, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001f2c, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001ffc, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002760, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002830, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002904, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820029d4, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003138, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003208, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820032dc, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820033ac, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003b10, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003be0, 0x0000005c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003cb4, 0x00000058);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003d84, 0x0000005c);
    return ret;
}

int inimage_Data_7_8_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x000003d8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004020, 0x000003d8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82008040, 0x000003d8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200c060, 0x000003d8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82010080, 0x000003d8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820140a0, 0x000003d8);
    return ret;
}

int kernel1_pooling_0_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000170, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820002e4, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000454, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820005c8, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000738, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820008ac, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000a1c, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000b90, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000d00, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000e74, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000fe4, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001158, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820012c8, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200143c, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820015ac, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001720, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001890, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001a04, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001b74, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001ce8, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001e58, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001fcc, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200213c, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820022b0, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002420, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002594, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002704, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002878, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820029e8, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002b5c, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002ccc, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002e40, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002fb0, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003124, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003294, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003408, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003578, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820036ec, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200385c, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820039d0, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003b40, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003cb4, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003e24, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82003f98, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004108, 0x00000090);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200427c, 0x0000008c);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820043ec, 0x00000090);

    return ret;
}


int kernelData_0_2_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x00000128);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82002960, 0x00000128);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820052c0, 0x00000128);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82007c20, 0x00000128);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200a580, 0x00000128);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200cee0, 0x00000128);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200f840, 0x00000128);
    return ret;
}

int kernelData_7_dump(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82000000, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200022c, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820022c0, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820024ec, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82004580, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820047ac, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82006840, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82006a6c, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82008b00, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82008d2c, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200adc0, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200afec, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200d080, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200d2ac, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200f340, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8200f56c, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82011600, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8201182c, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x820138c0, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82013aec, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82015b80, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82015dac, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82017e40, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8201806c, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8201a100, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8201a32c, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8201c3c0, 0x000000c8);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x8201c5ec, 0x000000c8);

    return ret;
}


int control1_ch2_fromV11V12(){
    int ret = 0;
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001a38, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001a50, 0x00000018);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001a6c, 0x00000018);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001a88, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001aa4, 0x00000014);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001abc, 0x00000018);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001ad8, 0x00000018);
    ret |= soc_dump0_compare(RTL_DUMP_ADDR + 0x82001af4, 0x00000014);
    return ret;
}

//0x19668
int outChNum_16_dump(){
    unsigned int offset =0x82000000;
    int ret = 0;
    for(int j =0;j<7;j++){
        for(int i =0 ;i < 51; i++){

            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x10);
            offset = offset +0x40;
        }
        offset = offset + 0x15580 - 0x40;
        
    }
    return ret;
}


int OutimageData_0_2_dump(){
    

    unsigned int offset = 0x82000000;
    int ret = 0;
    int temp = 0 ;
    
    
    for(int j =0;j<13;j++){
        temp = j%4;
        // printf("temp = %d  %d\n",temp,j);
        switch (temp)
        {
        case 0:
            for(int i =0 ;i<77;i++){

            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            // ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x0c;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x10);
            offset += 0x10;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;

            }
             ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x0c;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x10);
            offset = offset + 0x19668;
            
            break;
        case 1:
             
            for(int i =0 ;i<77;i++){

                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x10);
                offset += 0x10;
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0x10;
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0x10;
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0xc;

            }
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x10);
            offset += 0x10;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset = offset + 0x19668;
            
            break;
        case 2:

            
            for(int i =0 ;i<77;i++){

                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0x10;
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0x10;
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
                offset += 0xc;
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x10);
                offset += 0x10;

            }
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset = offset + 0x19668;
            
            break;
        case 3:
            for(int i =0 ;i<77;i++){

            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0xc;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x10);
            offset += 0x10;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;

            }
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset += 0x10;
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, 0x0c);
            offset = offset + 0x19668;
            
            break;
        default:
            break;
        }
        
    }
    return ret;
}


int OutimageData_1_7_dump(){
    
    unsigned int offset = 0x82000000;
    int ret = 0;
    int size = 0x10;
    for(int j =0 ;j < 13; j++){

        if(j%2 == 0){
            size = 0x0c;
            for(int i = 0;i<310;i++){
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, size);
                // printf("addr = %x %x\t",offset,size);
                if(i%2==0){
                        size = 0x10;
                        offset =offset + 0x1c;
                        // printf("addr = %x\t",offset);
                }else{
                        size = 0x0c;
                        offset = offset+0x20;
                        // printf("addr = %x\t",offset);
                }
            }
            offset = offset - 0x20 + 0x8598;
        }else{
            size = 0x10;
            for(int i = 0;i<310;i++){
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, size);
                // printf("addr = %x %x\t",offset,size);
                if(i%2==0){
                        size = 0x0c;
                        offset =offset + 0x20;
                        // printf("addr = %x\t",offset);
                }else{
                        size = 0x10;
                        offset = offset+0x1c;
                        // printf("addr = %x\t",offset);
                }
            }
            offset = offset - 0x1c + 0x8598;
        }
    }
   return ret;
}

int OutimageData_4_dump(){
    unsigned int offset = 0x82000000;
    int ret = 0;
    int size = 0x10;
    for(int j =0 ;j < 13; j++){

        if(j%2 == 0){
            size = 0x0c;
            for(int i = 0;i<310;i++){

                // printf("addr = %x %x\t",offset,size);
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, size);
                if(i%2==0){
                        size = 0x10;
                        offset =offset + 0x1c;
                        // printf("addr = %x\t",offset);
                }else{
                        size = 0x0c;
                        offset = offset+0x20;
                        // printf("addr = %x\t",offset);
                }

            }

            offset = offset - 0x20 + 0x32cd0;
        }else{
            size = 0x10;
            for(int i = 0;i<310;i++){

                // printf("addr = %x %x\t",offset,size);
                ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset, size);
                if(i%2==0){
                        size = 0x0c;
                        offset =offset + 0x20;
                        // printf("addr = %x\t",offset);
                }else{
                        size = 0x10;
                        offset = offset+0x1c;
                        // printf("addr = %x\t",offset);
                }

            }
            
            offset = offset - 0x1c + 0x32cd0;
        }
    }
    return ret;
}

int OutimageData_8_dump(){
    //0x46668
   
    unsigned int offset = 0x82000000;
    int ret = 0;
    for(int j =0 ;j<13;j++){
        for(int i =0;i<310;i++){
            ret |= soc_dump0_compare(RTL_DUMP_ADDR + offset,0x00000010);
            // printf("addr = %x %d\t",offset,i);
            offset = offset + 0x3c;
        }
        offset = offset +0x46668 -0x3c;
            
    }
    return ret;
}
#endif

