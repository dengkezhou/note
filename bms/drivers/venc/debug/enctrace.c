/*------------------------------------------------------------------------------
--                                                                            --
--       This software is confidential and proprietary and may be used        --
--        only as expressly authorized by a licensing agreement from          --
--                                                                            --
--                            Hantro Products Oy.                             --
--                                                                            --
--                   (C) COPYRIGHT 2006 HANTRO PRODUCTS OY                    --
--                            ALL RIGHTS RESERVED                             --
--                                                                            --
--                 The entire notice above must be reproduced                 --
--                  on all copies and should not be removed.                  --
--                                                                            --
--------------------------------------------------------------------------------
--
--  Description : Internal traces
--
--------------------------------------------------------------------------------
--  Version control information, please leave untouched.
--
--  $RCSfile: enctrace.c,v $
--  $Revision: 1.3 $
--
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    1. Include headers
------------------------------------------------------------------------------*/
#include <stdio.h>

#include "enctrace.h"

/*------------------------------------------------------------------------------
    2. External compiler flags
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
    3. Module defines
------------------------------------------------------------------------------*/
static FILE *fileAsic = NULL;
static FILE *filePreProcess = NULL;
static FILE *fRegs = NULL;
static FILE *fRecon = NULL;
static FILE *fTrace = NULL;

/*------------------------------------------------------------------------------
    4. Local function prototypes
------------------------------------------------------------------------------*/

void EncTraceCloseAll(void)
{
    if(fileAsic != NULL)
        fclose(fileAsic);
    if(filePreProcess != NULL)
        fclose(filePreProcess);
    if(fRegs != NULL)
        fclose(fRegs);
    if(fRecon != NULL)
        fclose(fRecon);
    if(fTrace != NULL)
        fclose(fTrace);
}

/*------------------------------------------------------------------------------

    EncTraceAsic

------------------------------------------------------------------------------*/
void EncTraceAsicParameters(asicData_s * asic)
{
    if(fileAsic == NULL)
        fileAsic = fopen("sw_asic.trc", "w");

    if(fileAsic == NULL)
    {
        fprintf(stderr, "Unable to open trace file: asic.trc\n");
        return;
    }

    fprintf(fileAsic, "ASIC parameters:\n");
    fprintf(fileAsic, "Input lum bus:       0x%08x\n",
            (u32) asic->regs.inputLumBase);
    fprintf(fileAsic, "Input cb bus:        0x%08x\n",
            (u32) asic->regs.inputCbBase);
    fprintf(fileAsic, "Input cr bus:        0x%08x\n\n",
            (u32) asic->regs.inputCrBase);

    /*fprintf(fileAsic, "Internal image base W: 0x%08x\n", (u32)asic->internalImageBase.virtualAddress); */

    fprintf(fileAsic, "Encoding type:           %6d\n", asic->regs.codingType);
    /*
     * fprintf(fileAsic, "Input endian mode:       %6d\n",
     * asic->regs.inputEndianMode);
     * fprintf(fileAsic, "Input endian width:      %6d\n",
     * asic->regs.inputEndianWidth);
     * fprintf(fileAsic, "Output endian width:      %6d\n",
     * asic->regs.outputEndianWidth);
     */
    fprintf(fileAsic, "Mbs in row:              %6d\n", asic->regs.mbsInRow);
    fprintf(fileAsic, "Mbs in col:              %6d\n", asic->regs.mbsInCol);
    fprintf(fileAsic, "Input lum width:         %6d\n", asic->regs.pixelsOnRow);
    fprintf(fileAsic, "Frame type:              %6d\n",
            asic->regs.frameCodingType);
    fprintf(fileAsic, "QP:                      %6d\n", asic->regs.qp);
    fprintf(fileAsic, "Round control:           %6d\n",
            asic->regs.roundingCtrl);
/*    fprintf(fileAsic, "MV SAD penalty:          %6d\n", asic->regs.mvSadPenalty);
    fprintf(fileAsic, "Intra SAD penalty:       %6d\n", asic->regs.intraSadPenalty);
    fprintf(fileAsic, "4MV SAD penalty:         %6d\n", asic->regs.fourMvSadPenalty);
*/

    fprintf(fileAsic, "Burst size:              %6d\n", ENC8270_BURST_LENGTH);

}

/*------------------------------------------------------------------------------

    EncTracePreProcess

------------------------------------------------------------------------------*/
void EncTracePreProcess(preProcess_s * preProcess)
{
    if(filePreProcess == NULL)
        filePreProcess = fopen("sw_preprocess.trc", "w");

    if(filePreProcess == NULL)
    {
        fprintf(stderr, "Unable to open trace file: preprocess.trc\n");
        return;
    }

    fprintf(filePreProcess, "Input width: %d\n", preProcess->lumWidthSrc);
    fprintf(filePreProcess, "Input height: %d\n", preProcess->lumHeightSrc);
    fprintf(filePreProcess, "Hor offset src: %d\n", preProcess->horOffsetSrc);
    fprintf(filePreProcess, "Ver offset src: %d\n", preProcess->verOffsetSrc);
}

/*------------------------------------------------------------------------------

    EncTraceRegs

------------------------------------------------------------------------------*/
void EncTraceRegs(const void *ewl, u32 mbNum)
{
    u32 i;

    if(fRegs == NULL)
        fRegs = fopen("sw_reg.trc", "w");

    if(fRegs == NULL)
        fRegs = stderr;

    if(mbNum == 0)
        fprintf(fRegs, "\n=== NEW VOP ====================================\n");

    fprintf(fRegs, "\nASIC register dump, mb=%4d\n\n", mbNum);

    /* Dump registers */
    for(i = 0; i <= 0x17C; i += 4)
        fprintf(fRegs, "Reg 0x%02x    0x%08x\n", i, EWLReadReg(ewl, i));

    fprintf(fRegs, "\n");

    /*fclose(fRegs);
     * fRegs = NULL; */

}

u32 SwapEndian(u32 tmp)
{

    u32 swapped;

    swapped = tmp >> 24;
    swapped |= (tmp >> 8) & (0xFF00);
    swapped |= (tmp << 8) & (0xFF0000);
    swapped |= tmp << 24;

    return swapped;
}

/*------------------------------------------------------------------------------

    EncDumpRecon

------------------------------------------------------------------------------*/
void EncDumpRecon(asicData_s * asic)
{
    if(fRecon == NULL)
        fRecon = fopen("sw_recon_internal.yuv", "wb");

    if(fRecon)
    {
        u32 index;
        u32 size = asic->regs.mbsInCol * asic->regs.mbsInRow * 16 * 16;

        if(asic->regs.internalImageLumBaseW ==
           asic->internalImageLuma[0].busAddress)
            index = 0;
        else
            index = 1;

        {
            u32 *pTmp = asic->internalImageLuma[index].virtualAddress;

            fwrite(pTmp, 1, size, fRecon);
        }

        {
            u32 *pTmp = asic->internalImageChroma[index].virtualAddress;

            fwrite(pTmp, 1, size / 2, fRecon);
        }
    }
}


