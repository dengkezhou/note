/*
 *  linux/include/linux/mtd/onenand_regs.h
 *
 *  OneNAND Register header file
 *
 *  Copyright (C) 2005-2007 Samsung Electronics
 *  Kyungmin Park <kyungmin.park@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ONENAND_REG_H
#define __ONENAND_REG_H

/* Memory Address Map Translation (Word order) */
#define ONENAND_MEMORY_MAP(x) ((x) << 1)

/*
 * External BufferRAM area
 */
#define ONENAND_BOOTRAM  ONENAND_MEMORY_MAP(0x0000)
#define ONENAND_DATARAM  ONENAND_MEMORY_MAP(0x0200)
#define ONENAND_SPARERAM ONENAND_MEMORY_MAP(0x8010)

/*
 * OneNAND Registers
 */
#define ONENAND_REG_MANUFACTURER_ID  ONENAND_MEMORY_MAP(0xF000)
#define ONENAND_REG_DEVICE_ID        ONENAND_MEMORY_MAP(0xF001)
#define ONENAND_REG_VERSION_ID       ONENAND_MEMORY_MAP(0xF002)
#define ONENAND_REG_DATA_BUFFER_SIZE ONENAND_MEMORY_MAP(0xF003)
#define ONENAND_REG_BOOT_BUFFER_SIZE ONENAND_MEMORY_MAP(0xF004)
#define ONENAND_REG_NUM_BUFFERS      ONENAND_MEMORY_MAP(0xF005)
#define ONENAND_REG_TECHNOLOGY       ONENAND_MEMORY_MAP(0xF006)

#define ONENAND_REG_START_ADDRESS1 ONENAND_MEMORY_MAP(0xF100)
#define ONENAND_REG_START_ADDRESS2 ONENAND_MEMORY_MAP(0xF101)
#define ONENAND_REG_START_ADDRESS3 ONENAND_MEMORY_MAP(0xF102)
#define ONENAND_REG_START_ADDRESS4 ONENAND_MEMORY_MAP(0xF103)
#define ONENAND_REG_START_ADDRESS5 ONENAND_MEMORY_MAP(0xF104)
#define ONENAND_REG_START_ADDRESS6 ONENAND_MEMORY_MAP(0xF105)
#define ONENAND_REG_START_ADDRESS7 ONENAND_MEMORY_MAP(0xF106)
#define ONENAND_REG_START_ADDRESS8 ONENAND_MEMORY_MAP(0xF107)

#define ONENAND_REG_START_BUFFER        ONENAND_MEMORY_MAP(0xF200)
#define ONENAND_REG_COMMAND             ONENAND_MEMORY_MAP(0xF220)
#define ONENAND_REG_SYS_CFG1            ONENAND_MEMORY_MAP(0xF221)
#define ONENAND_REG_SYS_CFG2            ONENAND_MEMORY_MAP(0xF222)
#define ONENAND_REG_CTRL_STATUS         ONENAND_MEMORY_MAP(0xF240)
#define ONENAND_REG_INTERRUPT           ONENAND_MEMORY_MAP(0xF241)
#define ONENAND_REG_START_BLOCK_ADDRESS ONENAND_MEMORY_MAP(0xF24C)
#define ONENAND_REG_END_BLOCK_ADDRESS   ONENAND_MEMORY_MAP(0xF24D)
#define ONENAND_REG_WP_STATUS           ONENAND_MEMORY_MAP(0xF24E)

#define ONENAND_REG_ECC_STATUS ONENAND_MEMORY_MAP(0xFF00)
#define ONENAND_REG_ECC_M0     ONENAND_MEMORY_MAP(0xFF01)
#define ONENAND_REG_ECC_S0     ONENAND_MEMORY_MAP(0xFF02)
#define ONENAND_REG_ECC_M1     ONENAND_MEMORY_MAP(0xFF03)
#define ONENAND_REG_ECC_S1     ONENAND_MEMORY_MAP(0xFF04)
#define ONENAND_REG_ECC_M2     ONENAND_MEMORY_MAP(0xFF05)
#define ONENAND_REG_ECC_S2     ONENAND_MEMORY_MAP(0xFF06)
#define ONENAND_REG_ECC_M3     ONENAND_MEMORY_MAP(0xFF07)
#define ONENAND_REG_ECC_S3     ONENAND_MEMORY_MAP(0xFF08)

/*
 * Device ID Register F001h (R)
 */
#define ONENAND_DEVICE_DENSITY_MASK  (0xf)
#define ONENAND_DEVICE_DENSITY_SHIFT (4)
#define ONENAND_DEVICE_IS_DDP        (1 << 3)
#define ONENAND_DEVICE_IS_DEMUX      (1 << 2)
#define ONENAND_DEVICE_VCC_MASK      (0x3)

#define ONENAND_DEVICE_DENSITY_512Mb (0x002)
#define ONENAND_DEVICE_DENSITY_1Gb   (0x003)
#define ONENAND_DEVICE_DENSITY_2Gb   (0x004)
#define ONENAND_DEVICE_DENSITY_4Gb   (0x005)

/*
 * Version ID Register F002h (R)
 */
#define ONENAND_VERSION_PROCESS_SHIFT (8)

/*
 * Start Address 1 F100h (R/W)
 */
#define ONENAND_DDP_SHIFT (15)
#define ONENAND_DDP_CHIP0 (0)
#define ONENAND_DDP_CHIP1 (1 << ONENAND_DDP_SHIFT)

/*
 * Start Address 8 F107h (R/W)
 */
#define ONENAND_FPA_MASK  (0x3f)
#define ONENAND_FPA_SHIFT (2)
#define ONENAND_FSA_MASK  (0x03)

/*
 * Start Buffer Register F200h (R/W)
 */
#define ONENAND_BSA_MASK     (0x03)
#define ONENAND_BSA_SHIFT    (8)
#define ONENAND_BSA_BOOTRAM  (0 << 2)
#define ONENAND_BSA_DATARAM0 (2 << 2)
#define ONENAND_BSA_DATARAM1 (3 << 2)
#define ONENAND_BSC_MASK     (0x03)

/*
 * Command Register F220h (R/W)
 */
#define ONENAND_CMD_READ          (0x00)
#define ONENAND_CMD_READOOB       (0x13)
#define ONENAND_CMD_PROG          (0x80)
#define ONENAND_CMD_PROGOOB       (0x1A)
#define ONENAND_CMD_2X_PROG       (0x7D)
#define ONENAND_CMD_2X_CACHE_PROG (0x7F)
#define ONENAND_CMD_UNLOCK        (0x23)
#define ONENAND_CMD_LOCK          (0x2A)
#define ONENAND_CMD_LOCK_TIGHT    (0x2C)
#define ONENAND_CMD_UNLOCK_ALL    (0x27)
#define ONENAND_CMD_ERASE         (0x94)
#define ONENAND_CMD_RESET         (0xF0)
#define ONENAND_CMD_READID        (0x90)

/* NOTE: Those are not *REAL* commands */
#define ONENAND_CMD_BUFFERRAM (0x1978)

/*
 * System Configuration 1 Register F221h (R, R/W)
 */
#define ONENAND_SYS_CFG1_SYNC_READ (1 << 15)
#define ONENAND_SYS_CFG1_BRL_7     (7 << 12)
#define ONENAND_SYS_CFG1_BRL_6     (6 << 12)
#define ONENAND_SYS_CFG1_BRL_5     (5 << 12)
#define ONENAND_SYS_CFG1_BRL_4     (4 << 12)
#define ONENAND_SYS_CFG1_BRL_3     (3 << 12)
#define ONENAND_SYS_CFG1_BRL_10    (2 << 12)
#define ONENAND_SYS_CFG1_BRL_9     (1 << 12)
#define ONENAND_SYS_CFG1_BRL_8     (0 << 12)
#define ONENAND_SYS_CFG1_BRL_SHIFT (12)
#define ONENAND_SYS_CFG1_BL_32     (4 << 9)
#define ONENAND_SYS_CFG1_BL_16     (3 << 9)
#define ONENAND_SYS_CFG1_BL_8      (2 << 9)
#define ONENAND_SYS_CFG1_BL_4      (1 << 9)
#define ONENAND_SYS_CFG1_BL_CONT   (0 << 9)
#define ONENAND_SYS_CFG1_BL_SHIFT  (9)
#define ONENAND_SYS_CFG1_NO_ECC    (1 << 8)
#define ONENAND_SYS_CFG1_RDY       (1 << 7)
#define ONENAND_SYS_CFG1_INT       (1 << 6)
#define ONENAND_SYS_CFG1_IOBE      (1 << 5)
#define ONENAND_SYS_CFG1_RDY_CONF  (1 << 4)

/*
 * Controller Status Register F240h (R)
 */
#define ONENAND_CTRL_ONGO    (1 << 15)
#define ONENAND_CTRL_LOCK    (1 << 14)
#define ONENAND_CTRL_LOAD    (1 << 13)
#define ONENAND_CTRL_PROGRAM (1 << 12)
#define ONENAND_CTRL_ERASE   (1 << 11)
#define ONENAND_CTRL_ERROR   (1 << 10)
#define ONENAND_CTRL_RSTB    (1 << 7)

/*
 * Interrupt Status Register F241h (R)
 */
#define ONENAND_INT_MASTER (1 << 15)
#define ONENAND_INT_READ   (1 << 7)
#define ONENAND_INT_WRITE  (1 << 6)
#define ONENAND_INT_ERASE  (1 << 5)
#define ONENAND_INT_RESET  (1 << 4)
#define ONENAND_INT_CLEAR  (0 << 0)

/*
 * NAND Flash Write Protection Status Register F24Eh (R)
 */
#define ONENAND_WP_US  (1 << 2)
#define ONENAND_WP_LS  (1 << 1)
#define ONENAND_WP_LTS (1 << 0)

/*
 * ECC Status Reigser FF00h (R)
 */
#define ONENAND_ECC_1BIT     (1 << 0)
#define ONENAND_ECC_2BIT     (1 << 1)
#define ONENAND_ECC_2BIT_ALL (0xAAAA)

#endif /* __ONENAND_REG_H */
