/*
 * Copyright (C) 2017-2023 Alibaba Group Holding Limited
 */


/******************************************************************************
 * @file     core_rv64.h
 * @brief    CSI RV32 Core Peripheral Access Layer Header File
 * @version  V1.0
 * @date     01. Sep 2018
 ******************************************************************************/

#ifndef __CORE_RV64_H_GENERIC
#define __CORE_RV64_H_GENERIC

#include <stdint.h>
#include <common.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *                 CSI definitions
 ******************************************************************************/
/**
  \ingroup RV32
  @{
 */

#ifndef __RV64
#define __RV64                (0x01U)
#endif

/** __FPU_USED indicates whether an FPU is used or not.
    This core does not support an FPU at all
*/
#define __FPU_USED       0U

#if defined ( __GNUC__ )
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
#error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RV32_H_GENERIC */

#ifndef __CSI_GENERIC

#ifndef __CORE_RV32_H_DEPENDANT
#define __CORE_RV32_H_DEPENDANT

#ifdef __cplusplus
extern "C" {
#endif

/* check device defines and use defaults */
#ifndef __RV64_REV
#define __RV64_REV               0x0000U
#endif

#ifndef __VIC_PRIO_BITS
#define __VIC_PRIO_BITS           2U
#endif

#ifndef __Vendor_SysTickConfig
#define __Vendor_SysTickConfig    1U
#endif

#ifndef __MPU_PRESENT
#define __MPU_PRESENT             1U
#endif

#ifndef __ICACHE_PRESENT
#define __ICACHE_PRESENT          1U
#endif

#ifndef __DCACHE_PRESENT
#define __DCACHE_PRESENT          1U
#endif

#ifndef __L2CACHE_PRESENT
#define __L2CACHE_PRESENT         1U
#endif

#include <csi_rv64_gcc.h>

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CSI_glob_defs CSI Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#ifdef __cplusplus
#define     __I      volatile             /*!< Defines 'read only' permissions */
#else
#define     __I      volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O      volatile             /*!< Defines 'write only' permissions */
#define     __IO     volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const       /*! Defines 'read only' structure member permissions */
#define     __OM     volatile             /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile             /*! Defines 'read / write' structure member permissions */

/*@} end of group C9xx/R9xx */

/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core CLINT Register
 ******************************************************************************/
/**
  \defgroup CSI_core_register Defines and Type Definitions
  \brief Type definitions and defines for CK80X processor based devices.
*/

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_CORE  Status and Control Registers
  \brief      Core Register type definitions.
  @{
 */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_CLINT Core-Local Interrupt Controller (CLINT)
  \brief      Type definitions for the CLINT Registers
  @{
 */

/**
  \brief Access to the structure of a vector interrupt controller.
 */

typedef struct {
    uint32_t RESERVED0;                 /*!< Offset: 0x000 (R/W)  CLINT configure register */
    __IOM uint32_t PLIC_PRIO[1023];
    __IOM uint32_t PLIC_IP[32];
    uint32_t RESERVED1[3972 / 4 - 1];
    __IOM uint32_t PLIC_H0_MIE[32];
    __IOM uint32_t PLIC_H0_SIE[32];
    __IOM uint32_t PLIC_H1_MIE[32];
    __IOM uint32_t PLIC_H1_SIE[32];
    __IOM uint32_t PLIC_H2_MIE[32];
    __IOM uint32_t PLIC_H2_SIE[32];
    __IOM uint32_t PLIC_H3_MIE[32];
    __IOM uint32_t PLIC_H3_SIE[32];
    uint32_t RESERVED2[(0x01FFFFC - 0x00023FC) / 4 - 1];
    __IOM uint32_t PLIC_PER;
    __IOM uint32_t PLIC_H0_MTH;
    __IOM uint32_t PLIC_H0_MCLAIM;
    uint32_t RESERVED3[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H0_STH;
    __IOM uint32_t PLIC_H0_SCLAIM;
    uint32_t RESERVED4[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H1_MTH;
    __IOM uint32_t PLIC_H1_MCLAIM;
    uint32_t RESERVED5[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H1_STH;
    __IOM uint32_t PLIC_H1_SCLAIM;
    uint32_t RESERVED6[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H2_MTH;
    __IOM uint32_t PLIC_H2_MCLAIM;
    uint32_t RESERVED7[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H2_STH;
    __IOM uint32_t PLIC_H2_SCLAIM;
    uint32_t RESERVED8[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H3_MTH;
    __IOM uint32_t PLIC_H3_MCLAIM;
    uint32_t RESERVED9[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H3_STH;
    __IOM uint32_t PLIC_H3_SCLAIM;
    uint32_t RESERVED10[0xFFC / 4 - 1];
} PLIC_Type;


/**
  \ingroup    CSI_core_register
  \defgroup   CSI_PMP Physical Memory Protection (PMP)
  \brief      Type definitions for the PMP Registers
  @{
 */

#define PMP_PMPCFG_R_Pos                       0U                                    /*!< PMP PMPCFG: R Position */
#define PMP_PMPCFG_R_Msk                       (0x1UL << PMP_PMPCFG_R_Pos)           /*!< PMP PMPCFG: R Mask */

#define PMP_PMPCFG_W_Pos                       1U                                    /*!< PMP PMPCFG: W Position */
#define PMP_PMPCFG_W_Msk                       (0x1UL << PMP_PMPCFG_W_Pos)           /*!< PMP PMPCFG: W Mask */

#define PMP_PMPCFG_X_Pos                       2U                                    /*!< PMP PMPCFG: X Position */
#define PMP_PMPCFG_X_Msk                       (0x1UL << PMP_PMPCFG_X_Pos)           /*!< PMP PMPCFG: X Mask */

#define PMP_PMPCFG_A_Pos                       3U                                    /*!< PMP PMPCFG: A Position */
#define PMP_PMPCFG_A_Msk                       (0x3UL << PMP_PMPCFG_A_Pos)           /*!< PMP PMPCFG: A Mask */

#define PMP_PMPCFG_L_Pos                       7U                                    /*!< PMP PMPCFG: L Position */
#define PMP_PMPCFG_L_Msk                       (0x1UL << PMP_PMPCFG_L_Pos)           /*!< PMP PMPCFG: L Mask */

typedef enum {
    REGION_SIZE_4B       = -1,
    REGION_SIZE_8B       = 0,
    REGION_SIZE_16B      = 1,
    REGION_SIZE_32B      = 2,
    REGION_SIZE_64B      = 3,
    REGION_SIZE_128B     = 4,
    REGION_SIZE_256B     = 5,
    REGION_SIZE_512B     = 6,
    REGION_SIZE_1KB      = 7,
    REGION_SIZE_2KB      = 8,
    REGION_SIZE_4KB      = 9,
    REGION_SIZE_8KB      = 10,
    REGION_SIZE_16KB     = 11,
    REGION_SIZE_32KB     = 12,
    REGION_SIZE_64KB     = 13,
    REGION_SIZE_128KB    = 14,
    REGION_SIZE_256KB    = 15,
    REGION_SIZE_512KB    = 16,
    REGION_SIZE_1MB      = 17,
    REGION_SIZE_2MB      = 18,
    REGION_SIZE_4MB      = 19,
    REGION_SIZE_8MB      = 20,
    REGION_SIZE_16MB     = 21,
    REGION_SIZE_32MB     = 22,
    REGION_SIZE_64MB     = 23,
    REGION_SIZE_128MB    = 24,
    REGION_SIZE_256MB    = 25,
    REGION_SIZE_512MB    = 26,
    REGION_SIZE_1GB      = 27,
    REGION_SIZE_2GB      = 28,
    REGION_SIZE_4GB      = 29,
    REGION_SIZE_8GB      = 30,
    REGION_SIZE_16GB     = 31
} region_size_e;

typedef enum {
    ADDRESS_MATCHING_TOR   = 1,
    ADDRESS_MATCHING_NAPOT = 3
} address_matching_e;

typedef struct {
    uint32_t r: 1;           /* readable enable */
    uint32_t w: 1;           /* writeable enable */
    uint32_t x: 1;           /* execable enable */
    address_matching_e a: 2; /* address matching mode */
    uint32_t reserved: 2;    /* reserved */
    uint32_t l: 1;           /* lock enable */
} mpu_region_attr_t;

/*@} end of group CSI_PMP */

/* CACHE Register Definitions */
#define CACHE_MHCR_WBR_Pos                     8U                                            /*!< CACHE MHCR: WBR Position */
#define CACHE_MHCR_WBR_Msk                     (0x1UL << CACHE_MHCR_WBR_Pos)                 /*!< CACHE MHCR: WBR Mask */

#define CACHE_MHCR_IBPE_Pos                    7U                                            /*!< CACHE MHCR: IBPE Position */
#define CACHE_MHCR_IBPE_Msk                    (0x1UL << CACHE_MHCR_IBPE_Pos)                /*!< CACHE MHCR: IBPE Mask */

#define CACHE_MHCR_L0BTB_Pos                   6U                                            /*!< CACHE MHCR: L0BTB Position */
#define CACHE_MHCR_L0BTB_Msk                   (0x1UL << CACHE_MHCR_L0BTB_Pos)               /*!< CACHE MHCR: BTB Mask */

#define CACHE_MHCR_BPE_Pos                     5U                                            /*!< CACHE MHCR: BPE Position */
#define CACHE_MHCR_BPE_Msk                     (0x1UL << CACHE_MHCR_BPE_Pos)                 /*!< CACHE MHCR: BPE Mask */

#define CACHE_MHCR_RS_Pos                      4U                                            /*!< CACHE MHCR: RS Position */
#define CACHE_MHCR_RS_Msk                      (0x1UL << CACHE_MHCR_RS_Pos)                  /*!< CACHE MHCR: RS Mask */

#define CACHE_MHCR_WB_Pos                      3U                                            /*!< CACHE MHCR: WB Position */
#define CACHE_MHCR_WB_Msk                      (0x1UL << CACHE_MHCR_WB_Pos)                  /*!< CACHE MHCR: WB Mask */

#define CACHE_MHCR_WA_Pos                      2U                                            /*!< CACHE MHCR: WA Position */
#define CACHE_MHCR_WA_Msk                      (0x1UL << CACHE_MHCR_WA_Pos)                  /*!< CACHE MHCR: WA Mask */

#define CACHE_MHCR_DE_Pos                      1U                                            /*!< CACHE MHCR: DE Position */
#define CACHE_MHCR_DE_Msk                      (0x1UL << CACHE_MHCR_DE_Pos)                  /*!< CACHE MHCR: DE Mask */

#define CACHE_MHCR_IE_Pos                      0U                                            /*!< CACHE MHCR: IE Position */
#define CACHE_MHCR_IE_Msk                      (0x1UL << CACHE_MHCR_IE_Pos)                  /*!< CACHE MHCR: IE Mask */

#define CACHE_INV_ADDR_Pos                     6U
#define CACHE_INV_ADDR_Msk                     (0xFFFFFFFFUL << CACHE_INV_ADDR_Pos)

/*@} end of group CSI_CACHE */

// MSTATUS Register
#define MSTATUS_TVM_MASK (1L << 20)     // mstatus.TVM                      [20]
#define MSTATUS_MPP_MASK (3L << 11)     // mstatus.SPP                      [11:12]
#define MSTATUS_MPP_M    (3L << 11)     // Machine mode                     11
#define MSTATUS_MPP_S    (1L << 11)     // Supervisor mode                  01
#define MSTATUS_MPP_U    (0L << 11)     // User mode                        00

// SSTATUS Register
#define SSTATUS_SPP_MASK (3L << 8)      // sstatus.SPP                      [8:9]
#define SSTATUS_SPP_S    (1L << 8)      // Supervisor mode                  01
#define SSTATUS_SPP_U    (0L << 8)      // User mode                        00

typedef enum {
    USER_MODE        = 0,
    SUPERVISOR_MODE  = 1,
    MACHINE_MODE     = 3,
} cpu_work_mode_t;

/**
  \brief   Get CPU WORK MODE
  \details Returns CPU WORK MODE.
  \return  CPU WORK MODE
 */
__STATIC_INLINE int csi_get_cpu_work_mode(void)
{
    return (int)__get_CPU_WORK_MODE();
}

/**
  \ingroup  CSI_core_register
  \defgroup CSI_CINT     Core Local Interrupt (CLINT)
  \brief    Type definitions for the Core Local Interrupt Registers.
  @{
 */

/**
  \brief  The data structure of the access Clint.
 */
typedef struct {
	__IOM uint32_t MSIP0;
	__IOM uint32_t MSIP1;
	__IOM uint32_t MSIP2;
	__IOM uint32_t MSIP3;
	uint32_t RESERVED0[(0x4004000-0x400000C)/4 - 1];
	__IOM uint32_t MTIMECMPL0;
	__IOM uint32_t MTIMECMPH0;
	__IOM uint32_t MTIMECMPL1;
	__IOM uint32_t MTIMECMPH1;
	__IOM uint32_t MTIMECMPL2;
	__IOM uint32_t MTIMECMPH2;
	__IOM uint32_t MTIMECMPL3;
	__IOM uint32_t MTIMECMPH3;
	uint32_t RESERVED1[(0x400C000-0x400401C)/4 - 1];
	__IOM uint32_t SSIP0;
	__IOM uint32_t SSIP1;
	__IOM uint32_t SSIP2;
	__IOM uint32_t SSIP3;
	uint32_t RESERVED2[(0x400D000-0x400C00C)/4 - 1];
	__IOM uint32_t STIMECMPL0;
	__IOM uint32_t STIMECMPH0;
	__IOM uint32_t STIMECMPL1;
	__IOM uint32_t STIMECMPH1;
	__IOM uint32_t STIMECMPL2;
	__IOM uint32_t STIMECMPH2;
	__IOM uint32_t STIMECMPL3;
	__IOM uint32_t STIMECMPH3;
} CORET_Type;

typedef struct {
#ifdef CONFIG_RISCV_SMODE
        __IOM uint32_t STIMECMPL0;
        __IOM uint32_t STIMECMPH0;
#else
        __IOM uint32_t MTIMECMPL0;
        __IOM uint32_t MTIMECMPH0;
#endif
} CLINT_CMP_Type;


/*@} end of group CSI_SysTick */


/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_bitfield     Core register bit field macros
  \brief      Macros for use with bit field definitions (xxx_Pos, xxx_Msk).
  @{
 */

/**
  \brief   Mask and shift a bit field value for use in a register bit range.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of the bit field.
  \return           Masked and shifted value.
*/
#define _VAL2FLD(field, value)    ((value << field ## _Pos) & field ## _Msk)

/**
  \brief     Mask and shift a register value to extract a bit filed value.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of register.
  \return           Masked and shifted bit field value.
*/
#define _FLD2VAL(field, value)    ((value & field ## _Msk) >> field ## _Pos)

/*@} end of group CSI_core_bitfield */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */
//#define CORET_BASE          (PLIC_BASE + 0x4000000UL)		/*!< CORET Base Address */
#define CORET               ((CORET_Type *) CORET_BASE)       	/*!< SysTick configuration struct */
#define CLINT               ((CLINT_Type *) CLINT_BASE)       	/*!< CLINT configuration struct */
#define PLIC                ((PLIC_Type *) PLIC_BASE)       	/*!< PLIC configuration struct */

/*@} */

/*******************************************************************************
 *                Hardware Abstraction Layer
  Core Function Interface contains:
  - Core VIC Functions
  - Core CORET Functions
  - Core Register Access Functions
 ******************************************************************************/
/**
  \defgroup CSI_Core_FunctionInterface Functions and Instructions Reference
*/

/* ##########################   VIC functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_VICFunctions VIC Functions
  \brief    Functions that manage interrupts and exceptions via the VIC.
  @{
 */

/* The following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn)         (  ((((uint32_t)(int32_t)(IRQn))         )      &  0x03UL) * 8UL)
#define _IP_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    5UL)      )
#define _IP2_IDX(IRQn)           (   (((uint32_t)(int32_t)(IRQn))                >>    2UL)      )

/**
  \brief   Enable External Interrupt
  \details Enable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_enable_irq(int32_t IRQn)
{
#ifdef CONFIG_RISCV_SMODE
    PLIC->PLIC_H0_SIE[IRQn/32] = PLIC->PLIC_H0_SIE[IRQn/32] | (0x1 << (IRQn%32));
#else
    PLIC->PLIC_H0_MIE[IRQn/32] = PLIC->PLIC_H0_MIE[IRQn/32] | (0x1 << (IRQn%32));
#endif
}

/**
  \brief   Disable External Interrupt
  \details Disable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_disable_irq(int32_t IRQn)
{
#ifdef CONFIG_RISCV_SMODE
    PLIC->PLIC_H0_SIE[IRQn/32] = PLIC->PLIC_H0_SIE[IRQn/32] & (~(0x1 << (IRQn%32)));
#else
    PLIC->PLIC_H0_MIE[IRQn/32] = PLIC->PLIC_H0_MIE[IRQn/32] & (~(0x1 << (IRQn%32)));
#endif
}

/**
  \brief   Enable External Secure Interrupt
  \details Enable a secure device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_enable_sirq(int32_t IRQn)
{
	csi_vic_enable_irq(IRQn);
}

/**
  \brief   Disable External Secure Interrupt
  \details Disable a secure device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_disable_sirq(int32_t IRQn)
{
    csi_vic_disable_irq(IRQn);
}

/**
  \brief   Check Interrupt is Enabled or not
  \details Read the enabled register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not enabled.
  \return             1  Interrupt status is enabled.
 */
__STATIC_INLINE uint32_t csi_vic_get_enabled_irq(int32_t IRQn)
{
#ifdef CONFIG_RISCV_SMODE
    return (uint32_t)((PLIC->PLIC_H0_SIE[IRQn/32] >> IRQn%32) & 0x1);
#else
    return (uint32_t)((PLIC->PLIC_H0_MIE[IRQn/32] >> IRQn%32) & 0x1);
#endif
}

/**
  \brief   Check Interrupt is Pending or not
  \details Read the pending register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
 */
__STATIC_INLINE uint32_t csi_vic_get_pending_irq(int32_t IRQn)
{
    return (uint32_t)((PLIC->PLIC_IP[IRQn/32] >> IRQn%32) & 0x1);
}

/**
  \brief   Set Pending Interrupt
  \details Set the pending bit of an external interrupt.
  \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_set_pending_irq(int32_t IRQn)
{
    PLIC->PLIC_IP[IRQn/32] = PLIC->PLIC_IP[IRQn/32] | (0x1 << (IRQn%32));
}

/**
  \brief   Clear Pending Interrupt
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_clear_pending_irq(int32_t IRQn)
{
    PLIC->PLIC_H0_SCLAIM = IRQn;
}

/**
  \brief   Set Interrupt Priority
  \details Set the priority of an interrupt.
  \note    The priority cannot be set for every core interrupt.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
 */
__STATIC_INLINE void csi_vic_set_prio(int32_t IRQn, uint32_t priority)
{
    PLIC->PLIC_PRIO[IRQn - 1] = priority;
}

/**
  \brief   Get Interrupt Priority
  \details Read the priority of an interrupt.
           The interrupt number can be positive to specify an external (device specific) interrupt,
           or negative to specify an internal (core) interrupt.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t csi_vic_get_prio(int32_t IRQn)
{
    uint32_t prio = PLIC->PLIC_PRIO[IRQn - 1];

    return prio;
}


/*@} end of CSI_Core_VICFunctions */

/* ##########################   PMP functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_PMPFunctions PMP Functions
  \brief    Functions that manage interrupts and exceptions via the VIC.
  @{
 */

/**
  \brief  configure memory protected region.
  \details
  \param [in]  idx        memory protected region (0, 1, 2, ..., 15).
  \param [in]  base_addr  base address must be aligned with page size.
  \param [in]  size       \ref region_size_e. memory protected region size.
  \param [in]  attr       \ref region_size_t. memory protected region attribute.
  \param [in]  enable     enable or disable memory protected region.
  */
__STATIC_INLINE void
csi_mpu_config_region(uint32_t idx, unsigned long base_addr, region_size_e size,
                      mpu_region_attr_t *attr, uint32_t enable) {
  uint8_t pmpxcfg    = 0;
  unsigned long addr = 0;

  if (idx > 15) {
    return;
  }

  if (!enable) {
    attr->a = 0;
  }

  if (attr->a == ADDRESS_MATCHING_TOR) {
    addr = base_addr >> 2;
  } else {
    if (size == REGION_SIZE_4B) {
      addr    = base_addr >> 2;
      attr->a = 2;
    } else {
      addr = ((base_addr >> 2) & (0xFFFFFFFFU - ((1 << (size + 1)) - 1))) |
             ((1 << size) - 1);
    }
  }

  __set_PMPADDRx(idx, addr);

  pmpxcfg |= (attr->r << PMP_PMPCFG_R_Pos) | (attr->w << PMP_PMPCFG_W_Pos) |
             (attr->x << PMP_PMPCFG_X_Pos) | (attr->a << PMP_PMPCFG_A_Pos) |
             (attr->l << PMP_PMPCFG_L_Pos);
  __set_PMPxCFG(idx, pmpxcfg);
}

/**
  \brief  disable mpu region by idx.
  \details
  \param [in]  idx        memory protected region (0, 1, 2, ..., 15).
  */
__STATIC_INLINE void csi_mpu_disable_region(uint32_t idx)
{
    __set_PMPxCFG(idx, __get_PMPxCFG(idx) & (~PMP_PMPCFG_A_Msk));
}

/*@} end of CSI_Core_PMPFunctions */

/* ##################################    SysTick function  ############################################ */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_SysTickFunctions SysTick Functions
  \brief    Functions that configure the System.
  @{
 */

/**
        \brief CORE soft irq trigger
        */
__STATIC_INLINE uint32_t csi_softirq_trigger(int coreid, int en) {
#ifdef __SMODE_SUPPORT
  volatile uint32_t *reg = &(CORET->SSIP0);
#else
  volatile uint32_t *reg  = &(CORET->MSIP0);
#endif

  reg += coreid;
  if (en)
    *reg |= 1;
  else
    *reg &= ~1;
  return (0UL);
}

/**
  \brief   CORE timer Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \param [in]  IRQn   core timer Interrupt number.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
#ifdef CONFIG_RISCV_SMODE
__STATIC_INLINE uint32_t csi_coret_config(int core, uint32_t ticks, int32_t IRQn)
{
    CLINT_CMP_Type * clint_cmp = ((CLINT_CMP_Type *) (CORET_BASE + 0xd000 + core * 0x8));

#ifdef __QEMU_RUN
    uint64_t value = (((uint64_t)clint_cmp->STIMECMPH0) << 32) + (uint64_t)clint_cmp->STIMECMPL0;

    value = value + (uint64_t)ticks;
    clint_cmp->STIMECMPH0 = (uint32_t)(value >> 32);
    clint_cmp->STIMECMPL0 = (uint32_t)value;
#else
    uint64_t value = (((uint64_t)clint_cmp->STIMECMPH0) << 32) + (uint64_t)clint_cmp->STIMECMPL0;

    if ((value != 0) && (value != 0xffffffffffffffff)) {
        value = value + (uint64_t)ticks;
    } else {
        value = __get_MTIME() + ticks;
    }
    clint_cmp->STIMECMPH0 = (uint32_t)(value >> 32);
    clint_cmp->STIMECMPL0 = (uint32_t)value;
#endif

    return (0UL);
}
#else
__STATIC_INLINE uint32_t csi_coret_config(int core, uint32_t ticks, int32_t IRQn)
{
    CLINT_CMP_Type * clint_cmp = ((CLINT_CMP_Type *) (CORET_BASE + 0x4000 + core * 0x8));

#ifdef __QEMU_RUN
    uint64_t value = (((uint64_t)clint_cmp->MTIMECMPH0) << 32) + (uint64_t)clint_cmp->MTIMECMPL0;

    value = value + (uint64_t)ticks;
    clint_cmp->MTIMECMPH0 = (uint32_t)(value >> 32);
    clint_cmp->MTIMECMPL0 = (uint32_t)value;
#else
    uint64_t value = (((uint64_t)clint_cmp->MTIMECMPH0) << 32) + (uint64_t)clint_cmp->MTIMECMPL0;

    if ((value != 0) && (value != 0xffffffffffffffff)) {
        value = value + (uint64_t)ticks;
    } else {
        value = __get_MTIME() + ticks;
    }
    clint_cmp->MTIMECMPH0 = (uint32_t)(value >> 32);
    clint_cmp->MTIMECMPL0 = (uint32_t)value;
#endif

    return (0UL);
}
#endif

/**
  \brief   get CORE timer reload value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint64_t csi_coret_get_load(void)
{
#ifdef CONFIG_RISCV_SMODE
    CLINT_CMP_Type * clint_cmp = ((CLINT_CMP_Type *) (CORET_BASE + 0xd000 + __get_MHARTID() * 0x8));
#else
    CLINT_CMP_Type * clint_cmp = ((CLINT_CMP_Type *) (CORET_BASE + 0x4000 + __get_MHARTID() * 0x8));
#endif

#ifdef CONFIG_RISCV_SMODE
    uint64_t value = (((uint64_t)clint_cmp->STIMECMPH0) << 32) + (uint64_t)clint_cmp->STIMECMPL0;
#else
    uint64_t value = (((uint64_t)clint_cmp->MTIMECMPH0) << 32) + (uint64_t)clint_cmp->MTIMECMPL0;
#endif

    return value;
}

/**
  \brief   get CORE timer reload high value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_coret_get_loadh(void)
{
#ifdef CONFIG_RISCV_SMODE
    CLINT_CMP_Type * clint_cmp = ((CLINT_CMP_Type *) (CORET_BASE + 0xd000 + __get_MHARTID() * 0x8));
#else
    CLINT_CMP_Type * clint_cmp = ((CLINT_CMP_Type *) (CORET_BASE + 0x4000 + __get_MHARTID() * 0x8));
#endif

#ifdef CONFIG_RISCV_SMODE
    uint64_t value = (((uint64_t)clint_cmp->STIMECMPH0) << 32) + (uint64_t)clint_cmp->STIMECMPL0;
#else
    uint64_t value = (((uint64_t)clint_cmp->MTIMECMPH0) << 32) + (uint64_t)clint_cmp->MTIMECMPL0;
#endif

    return (value >> 32) & 0xFFFFFFFF;
}

/**
  \brief   get CORE timer counter value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint64_t csi_coret_get_value(void)
{
    uint64_t result;
    __ASM volatile("csrr %0, 0xc01" : "=r"(result));
    return result;
}

/**
  \brief   get CORE timer counter high value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_coret_get_valueh(void)
{
    uint64_t result;
    __ASM volatile("csrr %0, time" : "=r"(result));
    return (result >> 32) & 0xFFFFFFFF;
}

/*@} end of CSI_core_DebugFunctions */

/* ##########################  Cache functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_CacheFunctions Cache Functions
  \brief    Functions that configure Instruction and Data cache.
  @{
 */

/**
  \brief   whether I-Cache enable
  */
__STATIC_INLINE int csi_icache_is_enable(void)
{
    uint32_t cache = __get_MHCR();
    return (cache & CACHE_MHCR_IE_Msk) >> CACHE_MHCR_IE_Pos;
}

/**
  \brief   Enable I-Cache
  \details Turns on I-Cache
  */
__STATIC_INLINE void csi_icache_enable(void)
{
#if (__ICACHE_PRESENT == 1U)
    if (!csi_icache_is_enable()) {
        uint32_t cache;
        __DSB();
        __ISB();
        __ICACHE_IALL();
        cache = __get_MHCR();
        cache |= CACHE_MHCR_IE_Msk;
        __set_MHCR(cache);
        __DSB();
        __ISB();
    }
#endif
}


/**
  \brief   Disable I-Cache
  \details Turns off I-Cache
  */
__STATIC_INLINE void csi_icache_disable(void)
{
#if (__ICACHE_PRESENT == 1U)
    if (csi_icache_is_enable()) {
        uint32_t cache;
        __DSB();
        __ISB();
        cache = __get_MHCR();
        cache &= ~CACHE_MHCR_IE_Msk;            /* disable icache */
        __set_MHCR(cache);
        __ICACHE_IALL();                        /* invalidate all icache */
        __DSB();
        __ISB();
    }
#endif
}


/**
  \brief   Invalidate I-Cache
  \details Invalidates I-Cache
  */
__STATIC_INLINE void csi_icache_invalid(void)
{
#if (__ICACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __ICACHE_IALL();                        /* invalidate all icache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   whether D-Cache enable
  */
__STATIC_INLINE int csi_dcache_is_enable(void)
{
    uint32_t cache = __get_MHCR();
    return (cache & CACHE_MHCR_DE_Msk) >> CACHE_MHCR_DE_Pos;
}

/**
  \brief   Enable D-Cache
  \details Turns on D-Cache
  \note    I-Cache also turns on.
  */
__STATIC_INLINE void csi_dcache_enable(void)
{
#if (__DCACHE_PRESENT == 1U)
    if (!csi_dcache_is_enable()) {
        uint32_t cache;
        __DSB();
        __ISB();
        __DCACHE_IALL();                        /* invalidate all dcache */
        cache = __get_MHCR();
        cache |= (CACHE_MHCR_DE_Msk | CACHE_MHCR_WB_Msk | CACHE_MHCR_WA_Msk | CACHE_MHCR_RS_Msk | CACHE_MHCR_BPE_Msk | CACHE_MHCR_L0BTB_Msk | CACHE_MHCR_IBPE_Msk | CACHE_MHCR_WBR_Msk);      /* enable all Cache */
        __set_MHCR(cache);

        __DSB();
        __ISB();
    }
#endif
}


/**
  \brief   Disable D-Cache
  \details Turns off D-Cache
  \note    I-Cache also turns off.
  */
__STATIC_INLINE void csi_dcache_disable(void)
{
#if (__DCACHE_PRESENT == 1U)
    if (csi_dcache_is_enable()) {
        uint32_t cache;
        __DSB();
        __ISB();
        cache = __get_MHCR();
        cache &= ~(uint32_t)CACHE_MHCR_DE_Msk; /* disable all Cache */
        __set_MHCR(cache);
        __DCACHE_IALL();                             /* invalidate all Cache */
        __DSB();
        __ISB();
    }
#endif
}

/**
  \brief   Invalidate D-Cache
  \details Invalidates D-Cache
  \note    I-Cache also invalid
  */
__STATIC_INLINE void csi_dcache_invalid(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __DCACHE_IALL();                            /* invalidate all Cache */
    __DSB();
    __ISB();
#endif
}


/**
  \brief   Clean D-Cache
  \details Cleans D-Cache
  \note    I-Cache also cleans
  */
__STATIC_INLINE void csi_dcache_clean(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __DCACHE_CALL();                                     /* clean all Cache */
    __DSB();
    __ISB();
#endif
}


/**
  \brief   Clean & Invalidate D-Cache
  \details Cleans and Invalidates D-Cache
  \note    I-Cache also flush.
  */
__STATIC_INLINE void csi_dcache_clean_invalid(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __DCACHE_CIALL();                                   /* clean and inv all Cache */
    __DSB();
    __ISB();
#endif
}


/**
  \brief   Invalidate L2-Cache
  \details Invalidates L2-Cache
  \note
  */
__STATIC_INLINE void csi_l2cache_invalid(void)
{
#if (__L2CACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __L2CACHE_IALL();                            /* invalidate l2 Cache */
    __DSB();
    __ISB();
#endif
}


/**
  \brief   Clean L2-Cache
  \details Cleans L2-Cache
  \note
  */
__STATIC_INLINE void csi_l2cache_clean(void)
{
#if (__L2CACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __L2CACHE_CALL();                                     /* clean l2 Cache */
    __DSB();
    __ISB();
#endif
}


/**
  \brief   Clean & Invalidate L2-Cache
  \details Cleans and Invalidates L2-Cache
  \note
  */
__STATIC_INLINE void csi_l2cache_clean_invalid(void)
{
#if (__L2CACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __L2CACHE_CIALL();                                   /* clean and inv l2 Cache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   D-Cache Invalidate by address
  \details Invalidates D-Cache for the given address
  \param[in]   addr    address (aligned to 64-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void csi_dcache_invalid_range(phys_addr_t addr, int64_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int64_t op_size = dsize + (uint64_t)addr % 64;
    uint64_t op_addr = (uint64_t)addr;
    int64_t linesize = 64;
    cpu_work_mode_t cpu_work_mode;
    cpu_work_mode = (cpu_work_mode_t)__get_CPU_WORK_MODE();

    __DSB();

    if (cpu_work_mode == MACHINE_MODE) {
        while (op_size > 0) {
            __DCACHE_IPA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    } else if (cpu_work_mode == SUPERVISOR_MODE) {
        while (op_size > 0) {
            __DCACHE_IVA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    }

    __DSB();
    __ISB();
#endif
}


/**
  \brief   D-Cache Clean by address
  \details Cleans D-Cache for the given address
  \param[in]   addr    address (aligned to 64-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void csi_dcache_clean_range(phys_addr_t addr, int64_t dsize)
{

#if (__DCACHE_PRESENT == 1)
    int64_t op_size = dsize + (uint64_t)addr % 64;
    uint64_t op_addr = (uint64_t) addr & CACHE_INV_ADDR_Msk;
    int64_t linesize = 64;
    cpu_work_mode_t cpu_work_mode;
    cpu_work_mode = (cpu_work_mode_t)__get_CPU_WORK_MODE();

    __DSB();

    if (cpu_work_mode == MACHINE_MODE) {
        while (op_size > 0) {
            __DCACHE_CPA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    } else if (cpu_work_mode == SUPERVISOR_MODE) {
        while (op_size > 0) {
            __DCACHE_CVA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    }

    __DSB();
    __ISB();
#endif

}


/**
  \brief   D-Cache Clean and Invalidate by address
  \details Cleans and invalidates D_Cache for the given address
  \param[in]   addr    address (aligned to 64-byte boundary)
  \param[in]   dsize   size of memory block (aligned to 64-byte boundary)
*/
__STATIC_INLINE void csi_dcache_clean_invalid_range(phys_addr_t addr, int64_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int64_t op_size = dsize + (uint64_t)addr % 64;
    uint64_t op_addr = (uint64_t) addr;
    int64_t linesize = 64;
    cpu_work_mode_t cpu_work_mode;
    cpu_work_mode = (cpu_work_mode_t)__get_CPU_WORK_MODE();

    __DSB();

    if (cpu_work_mode == MACHINE_MODE) {
        while (op_size > 0) {
            __DCACHE_CIPA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    } else if (cpu_work_mode == SUPERVISOR_MODE) {
        while (op_size > 0) {
            __DCACHE_CIVA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    }

    __DSB();
    __ISB();
#endif
}

/**
  \brief   setup cacheable range Cache
  \details setup Cache range
  */
__STATIC_INLINE void csi_cache_set_range (uint64_t index, uint64_t baseAddr, uint64_t size, uint64_t enable)
{
    ;
}

/**
  \brief   Enable cache profile
  \details Turns on Cache profile
  */
__STATIC_INLINE void csi_cache_enable_profile(void)
{
    ;
}

/**
  \brief   Disable cache profile
  \details Turns off Cache profile
  */
__STATIC_INLINE void csi_cache_disable_profile(void)
{
    ;
}

/**
  \brief   Reset cache profile
  \details Reset Cache profile
  */
__STATIC_INLINE void csi_cache_reset_profile(void)
{
    ;
}

/**
  \brief   cache access times
  \details Cache access times
  \note    every 256 access add 1.
  \return          cache access times, actual times should be multiplied by 256
  */
__STATIC_INLINE uint64_t csi_cache_get_access_time(void)
{
    return 0;
}

/**
  \brief   cache miss times
  \details Cache miss times
  \note    every 256 miss add 1.
  \return          cache miss times, actual times should be multiplied by 256
  */
__STATIC_INLINE uint64_t csi_cache_get_miss_time(void)
{
    return 0;
}

/*@} end of CSI_Core_CacheFunctions */


/* ##########################  MMU functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_MMUFunctions MMU Functions
  \brief    Functions that configure MMU.
  @{
  */

typedef enum {
    PAGE_SIZE_4KB   = 0x1000,
    PAGE_SIZE_2MB   = 0x200000,
    PAGE_SIZE_1GB   = 0x40000000,
} page_size_e;


typedef enum {
    MMU_MODE_39   = 0x8,
    MMU_MODE_48   = 0x9,
    MMU_MODE_57   = 0xa,
    MMU_MODE_64   = 0xb,
} mmu_mode_e;

/**
  \brief  enable mmu
  \details
  */
__STATIC_INLINE void csi_mmu_enable(mmu_mode_e mode)
{
    __set_SATP(__get_SATP() | ((uint64_t)mode << 60));
}

/**
  \brief  disable mmu
  \details
  */
__STATIC_INLINE void csi_mmu_disable(void)
{
    __set_SATP(__get_SATP() & (~((uint64_t)0xf << 60)));
}

/**
  \brief  flush all mmu tlb.
  \details
  */
__STATIC_INLINE void csi_mmu_invalid_tlb_all(void)
{
    __ASM volatile("sfence.vma" : : : "memory");
}

/**
  \brief  flush mmu tlb by asid.
  \details
  */
__STATIC_INLINE void csi_mmu_invalid_tlb_by_asid(unsigned long asid)
{
    __ASM volatile("sfence.vma zero, %0"
                   :
                   : "r"(asid)
                   : "memory");
}

/**
  \brief  flush mmu tlb by page.
  \details
  */
__STATIC_INLINE void csi_mmu_invalid_tlb_by_page(unsigned long asid, unsigned long addr)
{
    __ASM volatile("sfence.vma %0, %1"
                   :
                   : "r"(addr), "r"(asid)
                   : "memory");
}

/**
  \brief  flush mmu tlb by range.
  \details
  */
__STATIC_INLINE void csi_mmu_invalid_tlb_by_range(unsigned long asid, page_size_e page_size, unsigned long start_addr, unsigned long end_addr)
{
    start_addr &= ~(page_size - 1);
    end_addr += page_size - 1;
    end_addr &= ~(page_size - 1);

    while(start_addr < end_addr) {
        __ASM volatile("sfence.vma %0, %1"
                       :
                       : "r"(start_addr), "r"(asid)
                       : "memory");
    }
}

/*@} end of CSI_Core_MMUFunctions */

/* ##########################  TCM functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_TCMFunctions TCM Functions
  \brief    Functions that configure TCM.
  @{
  */

/**
 \ingroup    CSI_tcm_register
 \defgroup   CSI_TCM
 \brief      Type definitions for the tcm Registers
 @{
 */

/**
 \brief  Consortium definition for accessing protection area selection register(MITCMCR, 0x7f9).
 */
typedef union {
    struct {
        uint64_t EN: 1;                             /*!< bit:     0  Instruction Tightly-Coupled Memory enable */
        uint64_t ECC_EN: 1;                         /*!< bit:     1  ecc_en */
        uint64_t Interleave: 1;                     /*!< bit:     2  Interleave */
        uint64_t _reserved1: 1;                     /*!< bit:     3  Reserved */
        uint64_t Size: 4;                           /*!< bit:  4..7  Size of ITCM */
        uint64_t _reserved2: 4;                     /*!< bit:  8..11 Reserved */
        uint64_t Base_Address: 52;                  /*!< bit: 12..63 Base address of DTCM */
    } b;                                            /*!< Structure   Access by bit */
    uint64_t w;                                     /*!< Type        Access by whole register */
} MITCMCR_Type;

#define MITCMCR_Base_Address_Pos             12U                                              /*!< MITCMCR: Base_Address Position */
#define MITCMCR_Base_Address_Msk             (0xfffffffffffffULL << MITCMCR_Base_Address_Pos)  /*!< MITCMCR: Base_Address Mask */

#define MITCMCR_Size_Pos                     4U                                               /*!< MITCMCR: Size Position */
#define MITCMCR_Size_Msk                     (0xfULL << MITCMCR_Size_Pos)                      /*!< MITCMCR: Size Mask */

#define MITCMCR_INTERLEAVE_Pos               2U                                               /*!< MITCMCR: Interleave Position */
#define MITCMCR_INTERLEAVE_Msk               (0x1ULL << MITCMCR_SIF_Pos)                       /*!< MITCMCR: Interleave Mask */

#define MITCMCR_ECC_EN_Pos                   1U                                               /*!< MITCMCR: ECC_EN Position */
#define MITCMCR_ECC_EN_Msk                   (0x1ULL << MITCMCR_EN_Pos)                        /*!< MITCMCR: ECC_EN Mask */

#define MITCMCR_EN_Pos                       0U                                               /*!< MITCMCR: EN Position */
#define MITCMCR_EN_Msk                       (0x1ULL << MITCMCR_EN_Pos)                        /*!< MITCMCR: EN Mask */

/**
 \brief  Consortium definition for accessing protection area selection register(MDTCMCR, 0x7f8).
 */
typedef union {
    struct {
        uint64_t EN: 1;                             /*!< bit:     0  Data Tightly-Coupled Memory enable */
        uint64_t ECC_EN: 1;                         /*!< bit:     1  ecc_en */
        uint64_t Interleave: 1;                     /*!< bit:     2  Interleave */
        uint64_t _reserved1: 1;                     /*!< bit:     3  Reserved */
        uint64_t Size: 4;                           /*!< bit:  4..7  Size of ITCM */
        uint64_t _reserved2: 4;                     /*!< bit:  8..11 Reserved */
        uint64_t Base_Address: 52;                  /*!< bit: 12..63 Base address of DTCM */
    } b;                                            /*!< Structure   Access by bit */
    uint64_t w;                                     /*!< Type        Access by whole register */
} MDTCMCR_Type;

#define MDTCMCR_Base_Address_Pos             12U                                              /*!< MDTCMCR: Base_Address Position */
#define MDTCMCR_Base_Address_Msk             (0xfffffffffffffULL << MDTCMCR_Base_Address_Pos)  /*!< MDTCMCR: Base_Address Mask */

#define MDTCMCR_Size_Pos                     4U                                               /*!< MDTCMCR: Size Position */
#define MDTCMCR_Size_Msk                     (0xfULL << MDTCMCR_Size_Pos)                      /*!< MDTCMCR: Size Mask */

#define MDTCMCR_INTERLEAVE_Pos               2U                                               /*!< MDTCMCR: Interleave Position */
#define MDTCMCR_INTERLEAVE_Msk               (0x1ULL << MDTCMCR_SIF_Pos)                       /*!< MDTCMCR: Interleave Mask */

#define MDTCMCR_ECC_EN_Pos                   1U                                               /*!< MDTCMCR: ECC_EN Position */
#define MDTCMCR_ECC_EN_Msk                   (0x1ULL << MDTCMCR_EN_Pos)                        /*!< MDTCMCR: ECC_EN Mask */

#define MDTCMCR_EN_Pos                       0U                                               /*!< MDTCMCR: EN Position */
#define MDTCMCR_EN_Msk                       (0x1ULL << MDTCMCR_EN_Pos)                        /*!< MDTCMCR: EN Mask */

/*@} end of group CSI_TCM_bitfield */

/**
 \ingroup    CSI_ECC_register
 \defgroup   CSI_ECC
 \brief      Type definitions for the ECC Registers
 @{
 */

typedef union {
    struct {
        uint64_t Index: 17;                         /*!< bit:  0..16 RAM index */
        uint64_t Way: 2;                            /*!< bit: 17..18 ICACHE/DCACHE WAY */
        uint64_t _reserved1: 2;                     /*!< bit: 19..20 Reserved */
        uint64_t RAMID: 3;                          /*!< bit: 21..23 ECC RAM ID */
        uint64_t Fix_cnt: 6;                        /*!< bit: 24..29 ECC ERR TYPE */
        uint64_t ERR_TYPE: 1;                       /*!< bit: 30 ECC ERR TYPE */
        uint64_t INFO_VLD: 1;                        /*!< bit: 31 ECC info valid */
        uint64_t _reserved2: 32;                    /*!< bit: 32..63 Reserved */
    } b;
    uint64_t w;
} MCER_Type;

typedef union {
    struct {
        uint64_t INJ_EN: 1;                         /*!< bit:     0  ECC inject enable */
        uint64_t ERR_TYPE: 1;                       /*!< bit:     1  ECC error type */
        uint64_t _reserved0: 27;                    /*!< bit:  2..28 Reserved */
        uint64_t RAMID: 3;                          /*!< bit: 29..31 ECC RAMID */
        uint64_t _reserved1: 32;                    /*!< bit: 32..63 Reserved */
    } b;                                            /*!< Structure    Access by bit */
    uint64_t w;                                     /*!< Type         Access by whole register */
} MEICR_Type;

#define MEICR_RAMID_Pos                 29U                                               /*!< MEICR: RAMID Position */
#define MEICR_RAMID_Msk                 (0x7ULL << MEICR_RAMID_Pos)                    /*!< MEICR: RAMID Mask */

#define MEICR_ERR_TYPE_Pos              1U                                                /*!< MEICR: ERR_TYPE Position */
#define MEICR_ERR_TYPE_Msk              (0x1ULL << MEICR_ERR_TYPE_Pos)                  /*!< MEICR: ERR_TYPE Mask */

#define MEICR_INJ_EN_Pos                0U                                                /*!< MEICR: INJ_EN Position */
#define MEICR_INJ_EN_Msk                (0x1ULL << MEICR_INJ_EN_Pos)                    /*!< MEICR: INJ_EN Mask */

/*@} end of group CSI_ECC_bitfield */


/**
  \brief   Enable ITCM
  \details Turns on ITCM
  */
__STATIC_INLINE void csi_itcm_enable (void)
{
    __set_MITCMCR(__get_MITCMCR() | MITCMCR_EN_Msk);
}

/**
  \brief   Enable DTCM
  \details Turns on DTCM
  */
__STATIC_INLINE void csi_dtcm_enable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() | MDTCMCR_EN_Msk);
}

/**
  \brief   Enable ITCM
  \details Turns on ITCM
  */
__STATIC_INLINE void csi_itcm_disable (void)
{
    __set_MITCMCR(__get_MITCMCR() & (~MITCMCR_EN_Msk));
}

/**
  \brief   Enable DTCM
  \details Turns on DTCM
  */
__STATIC_INLINE void csi_dtcm_disable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() & (~MDTCMCR_EN_Msk));
}

/**
  \brief   Get ITCM Size
  \details Get ITCM Size
  \return         ITCM size (bytes).
  */
__STATIC_INLINE uint32_t csi_itcm_get_size(void)
{
    MITCMCR_Type sizemask;
    uint32_t ret;

    sizemask.w = __get_MITCMCR();
    ret = sizemask.b.Size;

    return (1 << ret) << 10;
}

/**
  \brief   Get DTCM Size
  \details Get DTCM Size
  \return         DTCM size (bytes).
  */
__STATIC_INLINE uint32_t csi_dtcm_get_size(void)
{
    MDTCMCR_Type sizemask;
    uint32_t ret;

    sizemask.w = __get_MDTCMCR();
    ret = sizemask.b.Size;

    return (1 << ret) << 10;
}

/**
  \brief   Set ITCM Base Address
  \details Set ITCM Base Address
  \param [in]  base_addr  itcm base address.
  */
__STATIC_INLINE void csi_itcm_set_base_addr(uint64_t base_addr)
{
    __set_MITCMCR((__get_MITCMCR() & (~MITCMCR_Base_Address_Msk)) | (base_addr & MITCMCR_Base_Address_Msk));
}

/**
  \brief   Set DTCM Base Address
  \details Set DTCM Base Address
  \param [in]  base_addr  dtcm base address.
  */
__STATIC_INLINE void csi_dtcm_set_base_addr(uint64_t base_addr)
{
    __set_MDTCMCR((__get_MDTCMCR() & (~MDTCMCR_Base_Address_Msk)) | (base_addr & MDTCMCR_Base_Address_Msk));
}

/*@} end of CSI_Core_TCMFunctions */

/* ##########################  ECC functions  #################################### */
/**
 \ingroup  CSI_Core_FunctionInterface
 \defgroup CSI_Core_ECCFunctions ECC Functions
 \brief    Functions that configure ECC.
 @{
 */

typedef enum {
    ECC_ERROR_CORRECTABLE = 0,    /* 1-bit error */
    ECC_ERROR_FATAL = 1           /* 2-bits errors, fatal */
} ecc_error_type_e;

typedef enum {
    ECC_INFO_UNVALID = 0,    /* unvalid */
    ECC_INFO_VALID = 1       /* valid */
} ecc_valid_type_e;

typedef enum {
    ECC_ICACHE_TAG_RAM = 0,
    ECC_ICACHE_DATA_RAM = 1,
    ECC_DCACHE_TAG_RAM = 2,
    ECC_DCACHE_DATA_RAM = 3,
    ECC_JTLB_TAG_RAM = 4,
    ECC_JTLB_DATA_RAM = 5,
    ECC_DTCM_RAM = 6,
    ECC_ITCM_RAM = 7,
} ecc_ramid_e;

typedef struct {
    uint32_t index;
    uint8_t way;
    ecc_ramid_e ramid: 3;
    uint8_t fix_cnt;
    ecc_error_type_e err_type: 1;
    ecc_valid_type_e info_vld: 1;
} ecc_error_info_t;

/**
 *   \brief   Enable ITCM-ECC
 *     \details Turns on ITCM-ECC
 *       */
__STATIC_INLINE void csi_itcm_ecc_enable (void)
{
    __set_MITCMCR(__get_MITCMCR() | MITCMCR_ECC_EN_Msk);
}

/**
 *   \brief   Disable ITCM-ECC
 *     \details Turns off ITCM-ECC
 *       */
__STATIC_INLINE void csi_itcm_ecc_disable (void)
{
    __set_MITCMCR(__get_MITCMCR() & (~MITCMCR_ECC_EN_Msk));
}

/**
 *   \brief   Enable DTCM-ECC
 *     \details Turns on DTCM-ECC
 *       */
__STATIC_INLINE void csi_dtcm_ecc_enable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() | MDTCMCR_ECC_EN_Msk);
}

/**
 *   \brief   Disable DTCM-ECC
 *     \details Turns off DTCM-ECC
 *       */
__STATIC_INLINE void csi_dtcm_ecc_disable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() & (~MDTCMCR_ECC_EN_Msk));
}

/**
  \brief   Inject ECC error
  \details Inject ECC error
  \param [in]      type ECC error type.
  \param [in]      ramid ECC ram id.
  */
__STATIC_INLINE void csi_ecc_inject_error(ecc_error_type_e type, ecc_ramid_e ramid)
{
    MEICR_Type errinjcr;

    errinjcr.b.ERR_TYPE = type;
    errinjcr.b.RAMID = ramid;
    errinjcr.b.INJ_EN = 1U;
    errinjcr.b._reserved0 = 0;
    errinjcr.b._reserved1 = 0;

    __set_MEICR(errinjcr.w);
}

/**
 \brief   Get ECC error info
 \details Inject ECC error info
 \param [out]      info ECC error info
 */
__STATIC_INLINE void csi_ecc_get_error_info(ecc_error_info_t *info)
{
    MCER_Type mcer;

    if (info != NULL) {
#ifdef CONFIG_RISCV_SMODE
        mcer.w = __get_SCER();
#else
        mcer.w = __get_MCER();
#endif
        info->index    = mcer.b.Index;
        info->way      = mcer.b.Way;
        info->ramid    = (ecc_ramid_e)mcer.b.RAMID;
        info->fix_cnt  = mcer.b.Fix_cnt;
        info->err_type = (ecc_error_type_e)mcer.b.ERR_TYPE;
        info->info_vld = (ecc_valid_type_e)mcer.b.INFO_VLD;
    }
}

/*@} end of CSI_Core_ECCFunctions */

/* ##################################    IRQ Functions  ############################################ */

/**
  \brief   Save the Irq context
  \details save the psr result before disable irq.
 */
__STATIC_INLINE uint64_t csi_irq_save(void)
{
    uint64_t result;
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    result = __get_SSTATUS();
#else
    result = __get_MSTATUS();
#endif
    __disable_irq();
    return(result);
}

/**
  \brief   Restore the Irq context
  \details restore saved primask state.
  \param [in]      irq_state  psr irq state.
 */
__STATIC_INLINE void csi_irq_restore(uint64_t irq_state)
{
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    __set_SSTATUS(irq_state);
#else
    __set_MSTATUS(irq_state);
#endif
}

/*@} end of IRQ Functions */

/**
  \brief   Get the byte-width of vector register
  \return  the byte-width of vector register
 */
__STATIC_INLINE int csi_vlenb_get_value(void)
{
    int result;
    __ASM volatile("csrr %0, vlenb" : "=r"(result) : : "memory");
    return result;
}

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RV32_H_DEPENDANT */

#endif /* __CSI_GENERIC */
