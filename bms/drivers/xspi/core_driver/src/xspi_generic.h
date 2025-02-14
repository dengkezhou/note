/******************************************************************************
 *
 * Copyright (C) 2014-2021 Cadence Design Systems, Inc.
 * All rights reserved worldwide
 * The material contained herein is the proprietary and confidential
 * information of Cadence or its licensors, and is supplied subject to, and may
 * be used only by Cadence's customer in accordance with a previously executed
 * license and maintenance agreement between Cadence and that customer.
 *
 ******************************************************************************
 * xspi_generic.h
 *****************************************************************************/
#ifndef XSPI_GENERIC_H
#define XSPI_GENERIC_H

#include <stdint.h>

/* parasoft-begin-suppress MISRA2012-DIR-4_9-4 "Do not define function-like macro, DRV-4021" */

#define MODULO_32_BIT_POS(pos)                      ((pos) & 0x1FU)

/* DIRECT remap address macros */
#define DIR_REMAP_ADDR_GET_LOW_DWORD(rmpaddr)       ((uint32_t)((rmpaddr) & ((uint32_t)(0xFFFFFFFFU))))
#define DIR_REMAP_ADDR_GET_HIGH_DWORD(rmpaddr)      ((uint32_t)(((rmpaddr) >> 32) & ((uint32_t)0xFFFFFFFFU)))
#define DIR_REMAP_ADDR_SET_LOW_DWORD(rmpaddr)       ((uint64_t)(rmpaddr) & ((uint32_t)0xFFFFFFFFU))
#define DIR_REMAP_ADDR_SET_HIGH_DWORD(rmpaddr)      ((uint64_t)(((uint64_t)(rmpaddr)) << 32))

/* Legacy SPI and xSPI profile 1.0 instruction layout fields */
#define STIG_FLD_HBUS_EN(hyperBusEn)                ((uint32_t)((uint32_t)(hyperBusEn) & 1U) << MODULO_32_BIT_POS(127U))
#define STIG_FLD_INSTR_LINK(instrLink)              ((uint32_t)((uint32_t)(instrLink) & 1U) << MODULO_32_BIT_POS(124U))
#define STIG_FLD_CRC_VARIANT(crcVariant)            ((uint32_t)((uint32_t)(crcVariant) & 1U) << MODULO_32_BIT_POS(118U))
#define STIG_FLD_CRC_EN(crcEnable)                  ((uint32_t)((uint32_t)(crcEnable) & 1U) << MODULO_32_BIT_POS(117U))
#define STIG_FLD_XIP_EN(xipEnable)                  ((uint32_t)((uint32_t)(xipEnable) & 1U) << MODULO_32_BIT_POS(116U))
#define STIG_FLD_ADDR_SHIFT(addrShift)              ((uint32_t)((uint32_t)(addrShift) & 1U) << MODULO_32_BIT_POS(115U))
#define STIG_FLD_BANK(bank)                         ((uint32_t)((uint32_t)(bank) & 0x07U) << MODULO_32_BIT_POS(108U))
#define STIG_FLD_OPCODE_EDGE_MODE(mode)             ((uint32_t)((uint32_t)(mode) & 1U) << MODULO_32_BIT_POS(107U))
#define STIG_FLD_OPCODE_NO_OF_IOS(ios)              ((uint32_t)((uint32_t)(ios) & 0x03U) << MODULO_32_BIT_POS(104U))
#define STIG_FLD_OPCODE_EXT_EN(opExtEn)             ((uint32_t)((uint32_t)(opExtEn) & 1U) << MODULO_32_BIT_POS(100U))
#define STIG_FLD_ADDR_EDGE_MODE(mode)               ((uint32_t)((uint32_t)(mode) & 1U) << MODULO_32_BIT_POS(99U))
#define STIG_FLD_ADDR_NO_OF_IOS(ios)                ((uint32_t)((uint32_t)(ios) & 0x03U) << MODULO_32_BIT_POS(96U))
#define STIG_FLD_ADDR_NO_OF_BYTES(addrBytes)        ((uint32_t)((uint32_t)(addrBytes) & 0x07U) << MODULO_32_BIT_POS(92U))
#define STIG_FLD_DATA_NO_OF_BYTES(dataBytes)        ((uint32_t)((uint32_t)(dataBytes) & 0x03U) << MODULO_32_BIT_POS(88U))
#define STIG_FLD_CMD(cmd)                           ((uint32_t)((uint32_t)(cmd) & 0xFFU) << MODULO_32_BIT_POS(80U))
#define STIG_FLD_CMD_EXT(cmdExt)                    ((uint32_t)((uint32_t)(cmdExt) & 0xFFU) << MODULO_32_BIT_POS(72U))
#define STIG_FLD_ADDR_5(addr)                       ((uint32_t)((uint32_t)((addr)[5]) & 0xFFU) << MODULO_32_BIT_POS(64U))
#define STIG_FLD_ADDR_4(addr)                       ((uint32_t)((uint32_t)((addr)[4]) & 0xFFU) << MODULO_32_BIT_POS(56U))
#define STIG_FLD_ADDR_3(addr)                       ((uint32_t)((uint32_t)((addr)[3]) & 0xFFU) << MODULO_32_BIT_POS(48U))
#define STIG_FLD_ADDR_2(addr)                       ((uint32_t)((uint32_t)((addr)[2]) & 0xFFU) << MODULO_32_BIT_POS(40U))
#define STIG_FLD_ADDR_1(addr)                       ((uint32_t)((uint32_t)((addr)[1]) & 0xFFU) << MODULO_32_BIT_POS(32U))
#define STIG_FLD_ADDR_0(addr)                       ((uint32_t)((uint32_t)((addr)[0]) & 0xFFU) << MODULO_32_BIT_POS(24U))
#define STIG_FLD_DATA(data)                         ((uint32_t)((uint32_t)((data)[1]) & 0xFFU) << MODULO_32_BIT_POS(16U)) | \
                                                    ((uint32_t)((uint32_t)((data)[0]) & 0xFFU) << MODULO_32_BIT_POS(8U))
#define STIG_FLD_INSTR_TYPE(instrType)              ((uint32_t)((uint32_t)(instrType) & 0x7FU) << MODULO_32_BIT_POS(0U))

/* Legacy Hyperflash and xSPI profile 2.0 instruction layout specific fields */
#define STIG_FLD_TCMS_EN(tcmsEn)                    ((uint32_t)((uint32_t)(tcmsEn) & 1U) << MODULO_32_BIT_POS(125U))
#define STIG_FLD_EXT_CMD_MOD_EN(extCmdModEn)        ((uint32_t)((uint32_t)(extCmdModEn) & 1U) << MODULO_32_BIT_POS(120U))
#define STIG_FLD_RW(rw)                             ((uint32_t)((uint32_t)(rw) & 1U) << MODULO_32_BIT_POS(87U))
#define STIG_FLD_TARGET(target)                     ((uint32_t)((uint32_t)(target) & 1U) << MODULO_32_BIT_POS(86U))
#define STIG_FLD_BURST_TYPE(burstType)              ((uint32_t)((uint32_t)(burstType) & 1U) << MODULO_32_BIT_POS(85U))
#define STIG_FLD_ADDR_BIT_44(addrBit44_40)          ((uint32_t)((uint32_t)(addrBit44_40) & 0x10U) << MODULO_32_BIT_POS(84U))
#define STIG_FLD_ADDR_BIT_43(addrBit44_40)          ((uint32_t)((uint32_t)(addrBit44_40) & 0x8U) << MODULO_32_BIT_POS(83U))
#define STIG_FLD_ADDR_BIT_42(addrBit44_40)          ((uint32_t)((uint32_t)(addrBit44_40) & 0x4U) << MODULO_32_BIT_POS(82U))
#define STIG_FLD_ADDR_BIT_41(addrBit44_40)          ((uint32_t)((uint32_t)(addrBit44_40) & 0x2U) << MODULO_32_BIT_POS(81U))
#define STIG_FLD_ADDR_BIT_40(addrBit44_40)          ((uint32_t)((uint32_t)(addrBit44_40) & 0x1U) << MODULO_32_BIT_POS(80U))

/* Generic instruction layout specific fields */
#define STIG_FLD_GEN_INSTR_NO_OF_BYTES(noOfBytes)   ((uint32_t)((uint32_t)(noOfBytes) & 0x0FU) << MODULO_32_BIT_POS(88U))
#define STIG_FLD_GEN_INSTR_BYTE_9(bytes)            ((uint32_t)((uint32_t)((bytes)[9]) & 0xFFU) << MODULO_32_BIT_POS(80U))
#define STIG_FLD_GEN_INSTR_BYTE_8(bytes)            ((uint32_t)((uint32_t)((bytes)[8]) & 0xFFU) << MODULO_32_BIT_POS(72U))
#define STIG_FLD_GEN_INSTR_BYTE_7(bytes)            ((uint32_t)((uint32_t)((bytes)[7]) & 0xFFU) << MODULO_32_BIT_POS(64U))
#define STIG_FLD_GEN_INSTR_BYTE_6(bytes)            ((uint32_t)((uint32_t)((bytes)[6]) & 0xFFU) << MODULO_32_BIT_POS(56U))
#define STIG_FLD_GEN_INSTR_BYTE_5(bytes)            ((uint32_t)((uint32_t)((bytes)[5]) & 0xFFU) << MODULO_32_BIT_POS(48U))
#define STIG_FLD_GEN_INSTR_BYTE_4(bytes)            ((uint32_t)((uint32_t)((bytes)[4]) & 0xFFU) << MODULO_32_BIT_POS(40U))
#define STIG_FLD_GEN_INSTR_BYTE_3(bytes)            ((uint32_t)((uint32_t)((bytes)[3]) & 0xFFU) << MODULO_32_BIT_POS(32U))
#define STIG_FLD_GEN_INSTR_BYTE_2(bytes)            ((uint32_t)((uint32_t)((bytes)[2]) & 0xFFU) << MODULO_32_BIT_POS(24U))
#define STIG_FLD_GEN_INSTR_BYTE_1(bytes)            ((uint32_t)((uint32_t)((bytes)[1]) & 0xFFU) << MODULO_32_BIT_POS(16U))
#define STIG_FLD_GEN_INSTR_BYTE_0(bytes)            ((uint32_t)((uint32_t)((bytes)[0]) & 0xFFU) << MODULO_32_BIT_POS(8U))

/* Data sequence layout specific fields */
#define STIG_FLD_CRC_CHUNK_SIZE(size)               ((uint32_t)((uint32_t)(size) & 0x07U) << MODULO_32_BIT_POS(120U))
#define STIG_FLD_CRC_INV(crcInv)                    ((uint32_t)((uint32_t)(crcInv) & 1U) << MODULO_32_BIT_POS(119U))
#define STIG_FLD_CRC_OE(crcOe)                      ((uint32_t)((uint32_t)(crcOe) & 1U) << MODULO_32_BIT_POS(118U))
#define STIG_FLD_CRC_UAL_CHUNK_EN(crcChunkEn)       ((uint32_t)((uint32_t)(crcChunkEn) & 1U) << MODULO_32_BIT_POS(116U))
#define STIG_FLD_CRC_UAL_CHUNK_CHK(crcChunkChk)     ((uint32_t)((uint32_t)(crcChunkChk) & 1U) << MODULO_32_BIT_POS(115U))
#define STIG_FLD_DATA_SWAP(dataSwap)                ((uint32_t)((uint32_t)(dataSwap) & 1U) << MODULO_32_BIT_POS(112U))
#define STIG_FLD_DATA_EDGE_MODE(mode)               ((uint32_t)((uint32_t)(mode) & 1U) << MODULO_32_BIT_POS(107U))
#define STIG_FLD_DATA_NO_OF_IOS(ios)                ((uint32_t)((uint32_t)(ios) & 0x03U) << MODULO_32_BIT_POS(104U))
#define STIG_FLD_TRANSFER_DIR(dir)                  ((uint32_t)((uint32_t)(dir) & 1U) << MODULO_32_BIT_POS(100U))
#define STIG_FLD_DATA_PER_ADDR(dataPerAddr)         ((uint32_t)((uint32_t)(dataPerAddr) & 1U) << MODULO_32_BIT_POS(92U))
#define STIG_FLD_NO_OF_DUMMY(noOfDummy)             ((uint32_t)((uint32_t)(noOfDummy) & 0x3FU) << MODULO_32_BIT_POS(84U))
#define STIG_FLD_HF_READ_BOUND_EN(hfRdBoundEn)      ((uint32_t)((uint32_t)(hfRdBoundEn) & 1U) << MODULO_32_BIT_POS(83U))
#define STIG_FLD_STATUS_SOURCE(src)                 ((uint32_t)((uint32_t)(src) & 1U) << MODULO_32_BIT_POS(24U))

/* Other instruction fields */
#define STIG_FLD_JEDEC_RST_VARIANT                  (((uint32_t)(1U)) << MODULO_32_BIT_POS(126U))

/* parasoft-end-suppress MISRA2012-DIR-4_9-4 */

#endif
