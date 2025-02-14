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
 * sgdma_regs.h
 * Header file describing USB DMA SG controllers
 ******************************************************************************/

#ifndef SGDMA_REGS_H
#define SGDMA_REGS_H

/* set PRECISE_BURST_LENGTH to one above */
#define PRECISE_BURST_LENGTH 0x00000000U
#define TD_SIZE_MASK         0x00001FFFFU

#define TD_SIZE                    12u
#define TD_DMULT_MAX_TRB_DATA_SIZE 65536u
#define TD_DMULT_MAX_TD_DATA_SIZE  (~1u)
#define TD_SING_MAX_TRB_DATA_SIZE  65536u
#define TD_SING_MAX_TD_DATA_SIZE   65536u

#define TD_PTR_SIZE 4

#define TD_DIRECTION_OUT 0u
#define TD_DIRECTION_IN  1u

#define TD_LITTLE_ENDIAN 0u
#define TD_BIG_ENDIAN    1u

/* Transfer Descriptor flags */
#define TD_TYPE_NORMAL          0x00000400U
#define TD_TYPE_LINK            0x00001800U
#define TDF_CYCLE_BIT           0x00000001U
#define TDF_TOGGLE_CYCLE_BIT    0x00000002U
#define TDF_INT_ON_SHORT_PACKET 0x00000004U
#define TDF_FIFO_MODE           0x00000008U
#define TDF_CHAIN_BIT           0x00000010U /* Set automaticly by TD Generator */
#define TDF_INT_ON_COMPLECTION  0x00000020U
#define TDF_STREAMID_VALID      0x00000200U

/*SFR maps*/
typedef struct {
  uint32_t conf; /*address 0x00*/
  uint32_t sts;  /*address 0x04*/
  uint32_t reserved5[5];
  uint32_t ep_sel;     /*address 0x1C*/
  uint32_t traddr;     /*address 0x20*/
  uint32_t ep_cfg;     /*address 0x24*/
  uint32_t ep_cmd;     /*address 0x28*/
  uint32_t ep_sts;     /*address 0x2c*/
  uint32_t ep_sts_sid; /*address 0x30*/
  uint32_t ep_sts_en;  /*address 0x34*/
  uint32_t drbl;       /*address 0x38*/
  uint32_t ep_ien;     /*address 0x3C*/
  uint32_t ep_ists;    /*address 0x40*/
  uint32_t usb_pwr;    /* address 0x44: Global Power Conf. Reg. */
  uint32_t usb_conf2;  /* address 0x48: Global Conf. Reg. 2 */
  uint32_t usb_cap1;   /* adderss 0x4C: Capability Reg. 1 */
  uint8_t reserved[32];
  uint32_t ep_dma_ext_addr; /* address 0x70: Upper 16 bit of EP DMA address */
  uint32_t buf_addr;        /* address 0x74: Address for on-chip buffer */
  uint32_t buf_data;        /* address 0x78: Data for on-chip buffer */
  uint32_t buf_ctrl;        /* address 0x7C: on-chip buffer access control */
  uint32_t dtrans;          /* address 0x80: DMA transfer mode */
  uint32_t tdl_from_trb;    /* address 0x84: Source of TDL configuration */
  uint32_t tdl_beh;         /* address 0x88: TDL Behavior configuration */
  uint32_t ep_tdl;          /* address 0x8C: Endpoint TDL */
  uint32_t tdl_beh2;        /* address 0x90: TDL Behavior-2 configuration */
  uint32_t dma_adv_td;      /* address 0x94: DMA Advance TD Configuration */
} __attribute__((packed)) DmaRegs;

/*-----------------------------------------------------------------------------
 */
/* DMA_CONF - Global Configuration Register */
/*-----------------------------------------------------------------------------
 */

/* Flags */
#define DMARF_RESET   0x00000001U
#define DMARF_LENDIAN 0x00000020U
#define DMARF_BENDIAN 0x00000040U
#define DMARF_SWRST   0x00000080U
#define DMARF_DSING   0x00000100U
#define DMARF_DMULT   0x00000200U

/*-----------------------------------------------------------------------------
 */
/* DMA_STS - Global Status Register */
/*-----------------------------------------------------------------------------
 */

/* Flags */
#define DMARF_DTRANS  0x00000008U
#define DMARF_ENDIAN  0x00000080U
#define DMARF_ENDIAN2 0x80000000U

/*-----------------------------------------------------------------------------
 */
/* DMA_EP_SEL - Endpoint Select Register */
/*-----------------------------------------------------------------------------
 */
/* Masks */
#define DMARM_EP_NUM  0x0000000FU
#define DMARM_EP_DIR  0x00000080U
#define DMARM_EP_ADDR (DMARM_EP_NUM | DMARM_EP_DIR)

/* Defines */
#define DMARV_EP_TX 1U /*IN endpoint for device and out endpoint for Host*/
#define DMARV_EP_RX 0U

#define DMARD_EP_TX 0x80U /*IN endpoint for device and out endpoint for Host*/
#define DMARD_EP_RX 0x00U

#define DMA_EP_CMD_STDL     0x00000100U
#define DMA_EP_CMD_DFLUSH   0x00000080U
#define DMA_EP_CMD_DRDY     0x00000040U
#define DMA_EP_CMD_REQ_CMPL 0x00000020U
#define DMA_EP_CMD_ERDY     0x00000008U
#define DMA_EP_CMD_CSTALL   0x00000004U
#define DMA_EP_CMD_SSTALL   0x00000002U
#define DMA_EP_CMD_EPRST    0x00000001U

/*-----------------------------------------------------------------------------
 */
/* USB_EP_TRADDR - Endpoint transfer ring address Register */
/*-----------------------------------------------------------------------------
 */
/* Masks */
#define DMARM_EP_TRADDR 0xFFFFFFFFU

/*-----------------------------------------------------------------------------
 */
/* DMA_EP_CFG - Endpoint Configuration Register */
/*-----------------------------------------------------------------------------
 */

/* Flags */
#define DMARF_EP_ENABLE 0x00000001U
#define DMARF_EP_ENDIAN 0x00000080U
#define DMARF_EP_DSING  0x00001000U
#define DMARF_EP_DMULT  0x00002000U

/* Values */
#define DMARV_EP_DISABLED 0U
#define DMARV_EP_ENABLED  1U
#define DMARV_EP_DSING    0x1000U
#define DMARV_EP_DMULT    0x2000U

#define DMARV_EP_LITTLE_ENDIAN 0U
#define DMARV_EP_BIG_ENDIAN    1U

/* Masks */
#define DMARM_EP_ENABLE 0x00000001U
#define DMARM_EP_ENDIAN 0x00000080U
#define DMARM_EP_DSING  0x00001000U
#define DMARM_EP_DMULT  0x00002000U

/*-----------------------------------------------------------------------------
 */
/* DMA_EP_CMD - Endpoint Command Register */
/*-----------------------------------------------------------------------------
 */

/* Flags */
#define DMARF_EP_EPRST  0x00000001U
#define DMARF_EP_ERDY   0x00000008U
#define DMARF_EP_DRDY   0x00000040U
#define DMARF_EP_DFLUSH 0x00000080U
#define DMARF_EP_STDL   0x00000100U

/* Offsets */
#define DMARF_EP_TDL_OFST    9U
#define DMARF_EP_MAX_TDL_TRB 0x7FU
/*-----------------------------------------------------------------------------
 */
/* DMA_EP_STS - Endpoint Status Register */
/*-----------------------------------------------------------------------------
 */

/* Masks */
#define DMARF_EP_IOC     0x00000004U
#define DMARF_EP_ISP     0x00000008U
#define DMARF_EP_DESCMIS 0x00000010U
#define DMARF_EP_TRBERR  0x00000080U
#define DMARF_EP_DBUSY   0x00000200U
#define DMARF_EP_CCS     0x00000800U
#define DMARF_EP_OUTSMM  0x00004000U
#define DMARF_EP_ISOERR  0x00008000U
#define DMARF_EP_IOT     0x00080000U
#define DMARF_EP_SIDERR  0x00002000U
#define DMARF_EP_PRIME   0x00001000U
#define DMARF_EP_MD_EXIT 0x00000040U
#define DMARF_EP_STREAMR 0x00000020U
#define DMARF_EP_DTRANS  0x80000000U

/*-----------------------------------------------------------------------------
 */
/* DMA_EP_STS_EN - Endpoint Status Register Enable */
/*-----------------------------------------------------------------------------
 */

/* Flags */
#define DMARF_EP_DESCMISEN 0x00000010U
#define DMARF_EP_TRBERREN  0x00000080U
#define DMARF_EP_OUTSMMEN  0x00004000U
#define DMARF_EP_ISOERREN  0x00008000U

#endif /* SGDMA_REGS_H */
