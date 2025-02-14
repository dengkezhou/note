/* da_pec_support.c
 *
 * Support functions for demo application.
 */

/*****************************************************************************
* Copyright (c) 2011-2020 by Rambus, Inc. and/or its subsidiaries.
* All rights reserved. Unauthorized use (including, without limitation,
* distribution and copying) is strictly prohibited. All use requires,
* and is subject to, explicit written authorization and nondisclosure
* Rambus, Inc. and/or its subsidiaries
*
* For more information or support, please go to our online support system at
* https://sipsupport.rambus.com.
* In case you do not have an account for this system, please send an e-mail
* to sipsupport@rambus.com.
*****************************************************************************/

#include <cae.h>

#include "c_da_pec.h"             // configuration switches
#include "da_pec_internal.h"

#include "api_pec.h"
#include "api_pec_sg.h"
#include "api_dmabuf.h"

#include "log.h"

#include "clib.h"

#include "sa_builder.h"
#include "sa_builder_basic.h"
#include "token_builder.h"

extern DMABuf_Status_t
DMABuf_Alloc(cae_device *dev,
        const DMABuf_Properties_t RequestedProperties,
        DMABuf_HostAddress_t * const Buffer_p,
        DMABuf_Handle_t * const Handle_p);
extern DMABuf_Status_t
DMABuf_Release(cae_device *dev,
        DMABuf_Handle_t Handle);
extern PEC_Status_t
PEC_Packet_Put(cae_device *dev,
        const unsigned int InterfaceId,
        const PEC_CommandDescriptor_t * Commands_p,
        const unsigned int CommandsCount,
        unsigned int * const PutCount_p);
extern PEC_Status_t
PEC_SA_Register(cae_device *dev,
        const unsigned int InterfaceId,
        DMABuf_Handle_t SA_Handle1,
        DMABuf_Handle_t SA_Handle2,
        DMABuf_Handle_t SA_Handle3);
extern PEC_Status_t
PEC_SA_UnRegister(cae_device *dev,
        const unsigned int InterfaceId,
        DMABuf_Handle_t SA_Handle1,
        DMABuf_Handle_t SA_Handle2,
        DMABuf_Handle_t SA_Handle3);
extern PEC_Status_t
PEC_Packet_Get(cae_device *dev,
        const unsigned int InterfaceId,
        PEC_ResultDescriptor_t * Results_p,
        const unsigned int ResultsLimit,
        unsigned int * const GetCount_p);
extern unsigned int
da_pec_pe_get_one(cae_device *dev,
        IOToken_Output_Dscr_t * const OutTokenDscr_p,
        uint32_t * OutTokenData_p,
        PEC_ResultDescriptor_t * RD_p);

/****************************************************************
* Definitions and macros.
*****************************************************************/


/*----------------------------------------------------------------------------
 * da_pec_iotoken_create
 */
bool
da_pec_iotoken_create(
        IOToken_Input_Dscr_t * const Dscr_p,
        void * const Ext_p,
        uint32_t * Data_p,
        PEC_CommandDescriptor_t * const PEC_CmdDscr)
{
    int IOTokenRc;

    Dscr_p->InPacket_ByteCount = PEC_CmdDscr->SrcPkt_ByteCount;
    Dscr_p->Ext_p              = Ext_p;

    IOTokenRc = IOToken_Create(Dscr_p, Data_p);
    if (IOTokenRc < 0)
    {
        LOG_CRIT("DA_PEC: %s: IOToken_Create() error %d\n",
                 __func__,
                 IOTokenRc);
        return false;
    }

    PEC_CmdDscr->InputToken_p = Data_p;

    return true; // Success
}


/*----------------------------------------------------------------------------
 * da_pec_pe_get_one
 *
 * Attempt to receive a single packet from the result descriptor ring.
 * Try this a configurable number of times. When a packet is received,
 * check its status and perform header post-processing.
 *
 * OutTokenDscr_p (output)
 *      Pointer to the Output Token descriptor that will be updated.
 *
 * OutTokenData_p (output)
 *      Pointer to the Output Token buffer where the token will be stored.
 *
 * RD_p (output)
 *      Pointer to the result descriptor that will be updated.
 *
 * Return: 0 if no packet received (timeout),
 *           if packet IO error or if packet processing error.
 *        >0 number of packets received.
 */
unsigned int
da_pec_pe_get_one(cae_device *dev,
        IOToken_Output_Dscr_t * const OutTokenDscr_p,
        uint32_t * OutTokenData_p,
        PEC_ResultDescriptor_t * RD_p)
{
    PEC_Status_t pecres;
    int LoopCounter = 1;//DA_PEC_PKT_GET_RETRY_COUNT;

    int IOToken_Rc;

    ZEROINIT(*OutTokenDscr_p);
    ZEROINIT(*RD_p);

    // Link data structures
    RD_p->OutputToken_p = OutTokenData_p;

    while (LoopCounter > 0)
    {
        // Try to get the processed packet from the driver
        unsigned int Counter = 0;

        pecres = PEC_Packet_Get(dev, INTERFACE_ID, RD_p, 1, &Counter);
        if (pecres != PEC_STATUS_OK)
        {
            LOG_CRIT("DA_PEC: PEC_Packet_Get error %d\n", pecres);
            return 0; // IO error
        }

        if (Counter)
        {
            IOToken_Rc = IOToken_Parse(OutTokenData_p, OutTokenDscr_p);
            if (IOToken_Rc < 0)
            {
                LOG_CRIT("DA_PEC: IOToken_Parse error %d\n", IOToken_Rc);
                return 0; // IO error
            }

            if(OutTokenDscr_p->ErrorCode != 0)
            {
                LOG_CRIT("DA_PEC: Result descriptor error 0x%x\n",
                         OutTokenDscr_p->ErrorCode);
                return 0; // Packet processing error
            }

            return Counter; // Packets received
        }

        // Wait for DA_PEC_PKT_GET_TIMEOUT_MS milliseconds
        //da_pec_usleep(DA_PEC_PKT_GET_TIMEOUT_MS * 1000);
        LoopCounter--;
    } // while

    LOG_CRIT("DA_PEC: Timeout when reading packet\n");

    return 0; // IO error (timeout, no result packet received)
}


#ifdef DA_PEC_USE_INVALIDATE_COMMANDS
/*----------------------------------------------------------------------------
 * da_pec_invalidate_rec
 */
bool
da_pec_invalidate_rec(
        const DMABuf_Handle_t Rec_p)
{
    PEC_Status_t PEC_Rc;
    PEC_CommandDescriptor_t Cmd;
    PEC_ResultDescriptor_t Res;

    unsigned int count;

    IOToken_Input_Dscr_t InTokenDscr;
    IOToken_Output_Dscr_t OutTokenDscr;
    uint32_t InputToken [IOTOKEN_IN_WORD_COUNT];
    uint32_t OutputToken [IOTOKEN_OUT_WORD_COUNT];
    void * InTokenDscrExt_p = NULL;

#ifdef DA_PEC_IOTOKEN_EXT
    IOToken_Input_Dscr_Ext_t InTokenDscrExt;

    ZEROINIT(InTokenDscrExt);
    InTokenDscrExt_p = &InTokenDscrExt;
#endif

    ZEROINIT(InTokenDscr);

    // Fill in the command descriptor for the Invalidate command
    ZEROINIT(Cmd);

    Cmd.SrcPkt_Handle       = DMABuf_NULLHandle;
    Cmd.DstPkt_Handle       = DMABuf_NULLHandle;
    Cmd.SA_Handle1          = Rec_p;
    Cmd.SA_Handle2          = DMABuf_NULLHandle;
    Cmd.Token_Handle        = DMABuf_NULLHandle;
    Cmd.SrcPkt_ByteCount    = 0;

#if defined(DA_PEC_IOTOKEN_EXT_SRV_ICEOCE) || \
    defined(DA_PEC_IOTOKEN_EXT_SRV_ICE)
    InTokenDscrExt.HW_Services = FIRMWARE_EIP207_CMD_INV_TR;
#endif

    if (!da_pec_iotoken_create(&InTokenDscr, InTokenDscrExt_p, InputToken, &Cmd))
        return false;

    // Issue command
    PEC_Rc = PEC_Packet_Put(dev, INTERFACE_ID, &Cmd, 1, &count);
    if (PEC_Rc != PEC_STATUS_OK || count != 1)
    {
        LOG_CRIT("DA_PEC: %s: PEC_Packet_Put() error %d, count %d\n",
                __func__,
                PEC_Rc,
                count);
        return false;
    }

    // Receive the result packet ... do we care about contents ?
    if (da_pec_pe_get_one(dev, &OutTokenDscr,
                          OutputToken,
                          &Res) < 1)
    {
        LOG_CRIT("DA_PEC: %s: da_pec_pe_get_one(dev, ) failed\n", __func__);
        return false;
    }

    return true;
}
#endif

/*----------------------------------------------------------------------------
 * da_pec_aes_block_encrypt
 *
 * Encrypt a single AES block.
 */
bool
da_pec_aes_block_encrypt(cipher_ctx *ctx, uint8_t *Key_p,
                             unsigned int KeyByteCount,
                             uint8_t *InData_p,
                             uint8_t *OutData_p)
{
    cae_device *dev = ctx->dev;
    int rc;
    SABuilder_Params_t params;
    SABuilder_Params_Basic_t ProtocolParams;
    unsigned int SAWords=0;

    DMABuf_Status_t DMAStatus;
    DMABuf_Properties_t DMAProperties = {0, 0, 0, 0};
    DMABuf_HostAddress_t SAHostAddress;
    DMABuf_HostAddress_t TokenHostAddress;
    DMABuf_HostAddress_t PktHostAddress;

    DMABuf_Handle_t SAHandle = {0};
    DMABuf_Handle_t TokenHandle = {0};
    DMABuf_Handle_t PktHandle = {0};

    unsigned int TCRWords=0;
    void * TCRData=0;
    unsigned int TokenWords=0;
    unsigned int TokenHeaderWord;
    unsigned int TokenMaxWords=0;

    TokenBuilder_Params_t TokenParams;
    PEC_CommandDescriptor_t Cmd;
    PEC_ResultDescriptor_t Res;
    unsigned int count;

    IOToken_Input_Dscr_t InTokenDscr;
    IOToken_Output_Dscr_t OutTokenDscr;
    uint32_t InputToken [IOTOKEN_IN_WORD_COUNT];
    uint32_t OutputToken [IOTOKEN_OUT_WORD_COUNT];
    void * InTokenDscrExt_p = NULL;

#ifdef DA_PEC_IOTOKEN_EXT
    IOToken_Input_Dscr_Ext_t InTokenDscrExt;

    ZEROINIT(InTokenDscrExt);
    InTokenDscrExt_p = &InTokenDscrExt;
#endif

    ZEROINIT(InTokenDscr);
    ZEROINIT(OutTokenDscr);

    rc = SABuilder_Init_Basic(&params, &ProtocolParams, SAB_DIRECTION_OUTBOUND);
    if (rc!=0)
    {
        LOG_CRIT("SABuilder_Init_Basic failed\n");
        goto error_exit;
    }
    // Add crypto key and parameters.
    params.CryptoAlgo = SAB_CRYPTO_AES;
    params.CryptoMode = SAB_CRYPTO_MODE_ECB;
    params.KeyByteCount = KeyByteCount;
    params.Key_p = Key_p;

    rc=SABuilder_GetSizes(ctx, &params, &SAWords, NULL, NULL);

    if (rc!=0)
    {
        LOG_CRIT("SA not created because of errors\n");
        goto error_exit;
    }

    DMAProperties.fCached   = true;
    DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
    DMAProperties.Bank      = DA_PEC_BANK_SA;
    DMAProperties.Size      = MAX(4*SAWords,DA_PEC_MIN_SA_BYTE_COUNT);

    DMAStatus = DMABuf_Alloc(dev, DMAProperties, &SAHostAddress, &SAHandle);
    if (DMAStatus != DMABUF_STATUS_OK)
    {
        rc = 1;
        LOG_CRIT("Allocation of SA failed\n");
        goto error_exit;
    }

    rc=SABuilder_BuildSA(ctx, &params, (uint32_t *)SAHostAddress.p, NULL, NULL);

    if (rc != 0)
    {
        LOG_CRIT("SA not created because of errors\n");
        goto error_exit;
    }

    rc=TokenBuilder_GetContextSize(&params, &TCRWords);

    if (rc != 0)
    {
        LOG_CRIT("TokenBuilder_GetContextSize returned errors\n");
        goto error_exit;
    }

    // The Token Context Record does not need to be allocated
    // in a DMA-safe buffer.
    TCRData = da_pec_malloc(4*TCRWords);
    if (!TCRData)
    {
        rc = 1;
        LOG_CRIT("Allocation of TCR failed\n");
        goto error_exit;
    }

    rc = TokenBuilder_BuildContext(&params, TCRData);

    if (rc != 0)
    {
        LOG_CRIT("TokenBuilder_BuildContext failed\n");
        goto error_exit;
    }

    rc = TokenBuilder_GetSize(TCRData, &TokenMaxWords);
    if (rc != 0)
    {
        LOG_CRIT("TokenBuilder_GetSize failed\n");
        goto error_exit;
    }

    // Allocate one buffer for the token and two packet buffers.

    DMAProperties.fCached   = true;
    DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
    DMAProperties.Bank      = DA_PEC_BANK_TOKEN;
    DMAProperties.Size      = 4*TokenMaxWords;

    DMAStatus = DMABuf_Alloc(dev, DMAProperties, &TokenHostAddress, &TokenHandle);
    if (DMAStatus != DMABUF_STATUS_OK)
    {
        rc = 1;
        LOG_CRIT("Allocation of token buffer failed.\n");
        goto error_exit;
    }

    DMAProperties.fCached   = true;
    DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
    DMAProperties.Bank      = DA_PEC_BANK_PACKET;
    DMAProperties.Size      = 16;

    DMAStatus = DMABuf_Alloc(dev, DMAProperties, &PktHostAddress,
                             &PktHandle);
    if (DMAStatus != DMABUF_STATUS_OK)
    {
        rc = 1;
        LOG_CRIT("Allocation of source packet buffer failed.\n");
        goto error_exit;
    }

    // Register the SA
    rc = PEC_SA_Register(dev, INTERFACE_ID, SAHandle, DMABuf_NULLHandle,
                      DMABuf_NULLHandle);
    if (rc != PEC_STATUS_OK)
    {
        LOG_CRIT("PEC_SA_Register failed\n");
        goto error_exit;
    }

    // Copy input packet into source packet buffer.
    memcpy(PktHostAddress.p, InData_p, 16);

    // Set Token Parameters if specified in test vector.
    ZEROINIT(TokenParams);


    // Prepare a token to process the packet.
    rc = TokenBuilder_BuildToken(ctx, TCRData,
                                 (uint8_t*)PktHostAddress.p,
                                 16,
                                 &TokenParams,
                                 (uint32_t*)TokenHostAddress.p,
                                 &TokenWords,
                                 &TokenHeaderWord);
    if(rc != TKB_STATUS_OK)
    {
        if(rc == TKB_BAD_PACKET)
        {
            LOG_CRIT("Token not created because packet size is invalid\n");
        }
        else
        {
            LOG_CRIT("Token builder failed\n");
        }
        goto error_exit_unregister;
    }
    Cmd.User_p = 0;
    Cmd.Token_Handle = TokenHandle;
    Cmd.Token_WordCount = TokenWords;
    Cmd.SrcPkt_Handle = PktHandle;
    Cmd.SrcPkt_ByteCount = 16;
    Cmd.DstPkt_Handle = PktHandle;
    Cmd.Bypass_WordCount = 0;
    Cmd.SA_Handle1 = SAHandle;
    Cmd.SA_Handle2 = DMABuf_NULLHandle;
    Cmd.SA_WordCount = 128;

#if defined(DA_PEC_IOTOKEN_EXT_SRV_ICEOCE) || \
    defined(DA_PEC_IOTOKEN_EXT_SRV_ICE)
    InTokenDscrExt.HW_Services  = FIRMWARE_EIP207_CMD_PKT_LAC;
#endif
    InTokenDscr.TknHdrWordInit = TokenHeaderWord;

    if (!da_pec_iotoken_create(&InTokenDscr,
                               InTokenDscrExt_p,
                               InputToken,
                               &Cmd))
    {
        rc = 1;
        goto error_exit_unregister;
    }

    rc = PEC_Packet_Put(dev, INTERFACE_ID,
                        &Cmd,
                        1,
                        &count);
    if (rc != PEC_STATUS_OK && count != 1)
    {
        rc = 1;
        LOG_CRIT("PEC_Packet_Put error\n");
        goto error_exit_unregister;
    }

    if (da_pec_pe_get_one(dev, &OutTokenDscr,
                          OutputToken,
                          &Res) == 0)
    {
        rc = 1;
        LOG_CRIT("error from da_pec_pe_get_one\n");
        goto error_exit_unregister;
    }
    memcpy(OutData_p, PktHostAddress.p, 16);


error_exit_unregister:
#ifdef DA_PEC_USE_INVALIDATE_COMMANDS
    if (!da_pec_invalidate_rec(SAHandle))
        rc=1;
#endif
    PEC_SA_UnRegister(dev, INTERFACE_ID, SAHandle, DMABuf_NULLHandle,
                      DMABuf_NULLHandle);

error_exit:
    DMABuf_Release(dev, SAHandle);
    DMABuf_Release(dev, TokenHandle);
    DMABuf_Release(dev, PktHandle);

    if (TCRData != NULL)
        da_pec_free (TCRData);

    return rc == 0;

}


/*----------------------------------------------------------------------------
 * da_pec_basic_hash
 */
bool
da_pec_basic_hash(md_ctx *ctx,
        SABuilder_Auth_t HashAlgo,
        uint8_t *Input_p,
        unsigned int InputByteCount,
        uint8_t *Output_p,
        unsigned int OutputByteCount,
        bool fFinalize)
{
    cae_device *dev = ctx->dev;
    int rc;
    SABuilder_Params_t params;
    SABuilder_Params_Basic_t ProtocolParams;
    unsigned int SAWords=0;

    static uint8_t DummyAuthKey[64];

    DMABuf_Status_t DMAStatus;
    DMABuf_Properties_t DMAProperties = {0, 0, 0, 0};
    DMABuf_HostAddress_t SAHostAddress;
    DMABuf_HostAddress_t TokenHostAddress;
    DMABuf_HostAddress_t PktHostAddress;

    DMABuf_Handle_t SAHandle = {0};
    DMABuf_Handle_t TokenHandle = {0};
    DMABuf_Handle_t PktHandle = {0};

    unsigned int TCRWords=0;
    void * TCRData=0;
    unsigned int TokenWords=0;
    unsigned int TokenHeaderWord;
    unsigned int TokenMaxWords=0;

    TokenBuilder_Params_t TokenParams;
    PEC_CommandDescriptor_t Cmd;
    PEC_ResultDescriptor_t Res;
    unsigned int count;

    IOToken_Input_Dscr_t InTokenDscr;
    IOToken_Output_Dscr_t OutTokenDscr;
    uint32_t InputToken [IOTOKEN_IN_WORD_COUNT];
    uint32_t OutputToken [IOTOKEN_OUT_WORD_COUNT];
    void * InTokenDscrExt_p = NULL;

#ifdef DA_PEC_IOTOKEN_EXT
    IOToken_Input_Dscr_Ext_t InTokenDscrExt;

    ZEROINIT(InTokenDscrExt);
    InTokenDscrExt_p = &InTokenDscrExt;
#endif

    ZEROINIT(InTokenDscr);
    ZEROINIT(OutTokenDscr);


    rc = SABuilder_Init_Basic(&params, &ProtocolParams, SAB_DIRECTION_OUTBOUND);
    if (rc!=0)
    {
        LOG_CRIT("DA_PEC: SABuilder_Init_Basic failed\n");
        goto error_exit;
    }
    // Add crypto key and parameters.
    params.AuthAlgo = HashAlgo;
    params.AuthKey1_p = DummyAuthKey;
    /* Dummy authentication key must be supplied when SAB_FLAG_HASH_INTERMEDIATE
       is set. */
    if (!fFinalize)
        params.flags |= SAB_FLAG_HASH_SAVE | SAB_FLAG_HASH_INTERMEDIATE;
    params.flags |= SAB_FLAG_SUPPRESS_PAYLOAD;
    ProtocolParams.ICVByteCount = OutputByteCount;

    rc=SABuilder_GetSizes(ctx, &params, &SAWords, NULL, NULL);

    if (rc!=0)
    {
        LOG_CRIT("DA_PEC: SA not created because of errors\n");
        goto error_exit;
    }

    DMAProperties.fCached   = true;
    DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
    DMAProperties.Bank      = DA_PEC_BANK_SA;
    DMAProperties.Size      = MAX(4*SAWords, DA_PEC_MIN_SA_BYTE_COUNT);

    DMAStatus = DMABuf_Alloc(dev, DMAProperties, &SAHostAddress, &SAHandle);
    if (DMAStatus != DMABUF_STATUS_OK)
    {
        rc = 1;
        LOG_CRIT("DA_PEC: Allocation of SA failed\n");
        goto error_exit;
    }

    rc=SABuilder_BuildSA(ctx, &params, (uint32_t *)SAHostAddress.p, NULL, NULL);

    if (rc != 0)
    {
        LOG_CRIT("DA_PEC: SA not created because of errors\n");
        goto error_exit;
    }

    rc=TokenBuilder_GetContextSize(&params, &TCRWords);

    if (rc != 0)
    {
        LOG_CRIT("DA_PEC: TokenBuilder_GetContextSize returned errors\n");
        goto error_exit;
    }

    // The Token Context Record does not need to be allocated
    // in a DMA-safe buffer.
    TCRData = da_pec_malloc(4*TCRWords);
    if (!TCRData)
    {
        rc = 1;
        LOG_CRIT("DA_PEC: Allocation of TCR failed\n");
        goto error_exit;
    }

    rc = TokenBuilder_BuildContext(&params, TCRData);

    if (rc != 0)
    {
        LOG_CRIT("DA_PEC: TokenBuilder_BuildContext failed\n");
        goto error_exit;
    }

    rc = TokenBuilder_GetSize(TCRData, &TokenMaxWords);
    if (rc != 0)
    {
        LOG_CRIT("DA_PEC: TokenBuilder_GetSize failed\n");
        goto error_exit;
    }

    // Allocate one buffer for the token and two packet buffers.

    DMAProperties.fCached   = true;
    DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
    DMAProperties.Bank      = DA_PEC_BANK_TOKEN;
    DMAProperties.Size      = 4*TokenMaxWords;

    DMAStatus = DMABuf_Alloc(dev, DMAProperties, &TokenHostAddress, &TokenHandle);
    if (DMAStatus != DMABUF_STATUS_OK)
    {
        rc = 1;
        LOG_CRIT("DA_PEC: Allocation of token buffer failed.\n");
        goto error_exit;
    }

    DMAProperties.fCached   = true;
    DMAProperties.Alignment = DA_PEC_DMA_ALIGNMENT_BYTE_COUNT;
    DMAProperties.Bank      = DA_PEC_BANK_PACKET;
    DMAProperties.Size      = MAX(InputByteCount, OutputByteCount);

    DMAStatus = DMABuf_Alloc(dev, DMAProperties, &PktHostAddress,
                             &PktHandle);
    if (DMAStatus != DMABUF_STATUS_OK)
    {
        rc = 1;
        LOG_CRIT("DA_PEC: Allocation of source packet buffer failed.\n");
        goto error_exit;
    }

    // Register the SA
    rc = PEC_SA_Register(dev, INTERFACE_ID, SAHandle, DMABuf_NULLHandle,
                      DMABuf_NULLHandle);
    if (rc != PEC_STATUS_OK)
    {
        LOG_CRIT("DA_PEC: PEC_SA_Register failed\n");
        goto error_exit;
    }

    // Copy input packet into source packet buffer.
    memcpy(PktHostAddress.p, Input_p, InputByteCount);

    // Set Token Parameters if specified in test vector.
    ZEROINIT(TokenParams);
    TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHFIRST |TKB_PACKET_FLAG_HASHAPPEND;
    if (fFinalize)
        TokenParams.PacketFlags |= TKB_PACKET_FLAG_HASHFINAL;

    // Prepare a token to process the packet.
    rc = TokenBuilder_BuildToken(ctx, TCRData,
                                 (uint8_t*)PktHostAddress.p,
                                 InputByteCount,
                                 &TokenParams,
                                 (uint32_t*)TokenHostAddress.p,
                                 &TokenWords,
                                 &TokenHeaderWord);
    if(rc != TKB_STATUS_OK)
    {
        if(rc == TKB_BAD_PACKET)
        {
            LOG_CRIT(
                "DA_PEC: Token not created because packet size is invalid\n");
        }
        else
        {
            LOG_CRIT("DA_PEC: Token builder failed\n");
        }
        goto error_exit_unregister;
    }
    Cmd.User_p = 0;
    Cmd.Token_Handle = TokenHandle;
    Cmd.Token_WordCount = TokenWords;
    Cmd.SrcPkt_Handle = PktHandle;
    Cmd.SrcPkt_ByteCount = InputByteCount;
    Cmd.DstPkt_Handle = PktHandle;
    Cmd.Bypass_WordCount = 0;
    Cmd.SA_Handle1 = SAHandle;
    Cmd.SA_Handle2 = DMABuf_NULLHandle;
    Cmd.SA_WordCount = 128;


#if defined(DA_PEC_IOTOKEN_EXT_SRV_ICEOCE) || \
    defined(DA_PEC_IOTOKEN_EXT_SRV_ICE)
    InTokenDscrExt.HW_Services  = FIRMWARE_EIP207_CMD_PKT_LAC;
#endif
    InTokenDscr.TknHdrWordInit = TokenHeaderWord;

    if (!da_pec_iotoken_create(&InTokenDscr,
                               InTokenDscrExt_p,
                               InputToken,
                               &Cmd))
    {
        rc = 1;
        goto error_exit_unregister;
    }

    rc = PEC_Packet_Put(dev, INTERFACE_ID,
                        &Cmd,
                        1,
                        &count);
    if (rc != PEC_STATUS_OK && count != 1)
    {
        rc = 1;
        LOG_CRIT("DA_PEC: PEC_Packet_Put error\n");
        goto error_exit_unregister;
    }

    if (da_pec_pe_get_one(dev, &OutTokenDscr,
                          OutputToken,
                          &Res) < 1)
    {
        rc = 1;
        LOG_CRIT("DA_PEC: error from da_pec_pe_get_one\n");
        goto error_exit_unregister;
    }
    memcpy(Output_p, PktHostAddress.p, OutputByteCount);


error_exit_unregister:
#ifdef DA_PEC_USE_INVALIDATE_COMMANDS
    if (!da_pec_invalidate_rec(SAHandle))
        rc=1;
#endif
    PEC_SA_UnRegister(dev, INTERFACE_ID, SAHandle, DMABuf_NULLHandle,
                      DMABuf_NULLHandle);

error_exit:
    DMABuf_Release(dev, SAHandle);
    DMABuf_Release(dev, TokenHandle);
    DMABuf_Release(dev, PktHandle);

    if (TCRData != NULL)
        da_pec_free (TCRData);

    return rc == 0;
}


/*----------------------------------------------------------------------------
 * da_pec_hmac_precompute
 */
bool
da_pec_hmac_precompute(md_ctx *ctx,
        SABuilder_Auth_t AuthAlgo,
        uint8_t *AuthKey_p,
        unsigned int AuthKeyByteCount,
        uint8_t * Inner_p,
        uint8_t * Outer_p)
{
    SABuilder_Auth_t HashAlgo;
    unsigned int blocksize, hashsize,digestsize;
    static uint8_t pad_block[128],hashed_key[128];
    unsigned int i;
    switch(AuthAlgo)
    {
    case SAB_AUTH_HMAC_MD5:
        HashAlgo = SAB_AUTH_HASH_MD5;
        blocksize = 64;
        hashsize = 16;
        digestsize = 16;
        break;
    case SAB_AUTH_HMAC_SHA1:
        HashAlgo = SAB_AUTH_HASH_SHA1;
        blocksize = 64;
        hashsize = 20;
        digestsize = 20;
        break;
    case SAB_AUTH_HMAC_SHA2_224:
        HashAlgo = SAB_AUTH_HASH_SHA2_224;
        blocksize = 64;
        hashsize = 28;
        digestsize = 32;
        break;
    case SAB_AUTH_HMAC_SHA2_256:
        HashAlgo = SAB_AUTH_HASH_SHA2_256;
        blocksize = 64;
        hashsize = 32;
        digestsize = 32;
        break;
    case SAB_AUTH_HMAC_SHA2_384:
        HashAlgo = SAB_AUTH_HASH_SHA2_384;
        blocksize = 128;
        hashsize = 48;
        digestsize = 64;
        break;
    case SAB_AUTH_HMAC_SHA2_512:
        HashAlgo = SAB_AUTH_HASH_SHA2_512;
        blocksize = 128;
        hashsize = 64;
        digestsize = 64;
        break;
    default:
        LOG_CRIT("DA_PEC: Unknown HMAC algorithm\n");
        return false;
    }

    memset(hashed_key, 0, blocksize);
    if (AuthKeyByteCount <= blocksize)
    {
        memcpy(hashed_key, AuthKey_p, AuthKeyByteCount);
    }
    else
    {
        if (!da_pec_basic_hash(ctx, HashAlgo,
                          AuthKey_p,
                          AuthKeyByteCount,
                          hashed_key,
                          hashsize,
                           true))
        {
            return false;
        }
    }

    for (i=0; i<blocksize; i++)
    {
        pad_block[i] = hashed_key[i] ^ 0x36;
    }
    if (!da_pec_basic_hash(ctx, HashAlgo,
                       pad_block,
                       blocksize,
                       Inner_p,
                       digestsize,
                       false))
    {
        return false;
    }

    for (i=0; i<blocksize; i++)
    {
        pad_block[i] = hashed_key[i] ^ 0x5c;
    }
    if (!da_pec_basic_hash(ctx, HashAlgo,
                       pad_block,
                       blocksize,
                       Outer_p,
                       digestsize,
                       false))
    {
        return false;
    }
    return true;
}


/* end of file da_pec_support.c */
