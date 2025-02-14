#ifndef __CCI_H__
#define __CCI_H__

#define BIT(nr) (1 << nr)

#define CCI400_BASE (ITCS_C_CCI_BASE + 0x90000)

/* Slave interface register offsets */
#define SNOOP_CTRL_REG			(0x0)
#define STATUS_REG			(0xc)

/* Slave interface offsets from PERIPHBASE */
#define SLAVE_IFACE6_OFFSET		(0x7000)
#define SLAVE_IFACE5_OFFSET		(0x6000)
#define SLAVE_IFACE4_OFFSET		(0x5000)
#define SLAVE_IFACE3_OFFSET		(0x4000)
#define SLAVE_IFACE2_OFFSET		(0x3000)
#define SLAVE_IFACE1_OFFSET		(0x2000)
#define SLAVE_IFACE0_OFFSET		(0x1000)
#define SLAVE_IFACE_OFFSET(index)	(SLAVE_IFACE0_OFFSET + \
					((0x1000) * (index)))

/* Snoop Control register bit definitions */
#define DVM_EN_BIT			BIT(1)
#define SNOOP_EN_BIT			BIT(0)
#define SUPPORT_SNOOPS			BIT(30)
#define SUPPORT_DVM			BIT(31)

/* Status register bit definitions */
#define CHANGE_PENDING_BIT		BIT(0)

void cci_enable_coherency(void);

#endif
