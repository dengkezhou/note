#ifndef CDNS_I2S_MC_REGS_H
#define CDNS_I2S_MC_REGS_H

#include <asm/bits.h>

#define CDNS_I2S_MC_DEPTH (6UL)

#define BIT_WIDTH(n)  ((1  << (n)) - 1)          /*eg: BIT_WIDTH(3), as 0b111 = 2 ^ 3 - 1 = 0x7*/

#define I2S_MC_TX_CFG       1
#define I2S_MC_RX_CFG       0

#define I2S_MC_MASTER_CFG   1
#define I2S_MC_SLAVE_CFG    0

#define I2S_MC_CTRL_RST_ALL  0 

#define I2S_MC_DEV_PHILIPS_MODE         (0x208)
#define I2S_MC_DEV_R_JUSTIFIED_MODE     (0x492)
#define I2S_MC_DEV_L_JUSTIFIED_MODE     (0x69a)
#define I2S_MC_DEV_DSP_MODE             (0xA28)   

#define I2S_MC_CTRL                     (0x00UL)
#define I2S_MC_I2S_EN(ch)               BIT(ch)                     /* 1-enable, 0-disable; bit0-7 for channel0-7 */
#define I2S_MC_TR_CFG(ch)               BIT((ch) + 8)               /* 1-tx, 0-rx;          bit8-15 for channel0-7 */
#define I2S_MC_TR_CFG_ALL               (BIT_WIDTH(8) << 8)           
#define I2S_MC_TR_CFG_OFFSET            (8)       
#define I2S_MC_LOOP_BACK_EN             (BIT_WIDTH(4) << 16)        /* 1-enable, 0-disable; bit16-19*/
#define I2S_MC_SFT_RST                  BIT(20)                     /* register reset*/
#define I2S_MC_TX_MS                    BIT(21)                     /* set tx master or slave*/
#define I2S_MC_RX_MS                    BIT(22)                     /* set rx master or slave*/
#define I2S_MC_TFIFO_RST                BIT(23)                     /* TX FIFO reset*/
#define I2S_MC_RFIFO_RST                BIT(24)                     /* RX FIFO reset*/
#define I2S_MC_TSYNC_RST                BIT(25)                     /* TX SYNC reset*/
#define I2S_MC_RSYNC_RST                BIT(26)                     /* RX SYNC reset*/
#define I2S_MC_TSYNC_LOOP_BACK          BIT(27)                     /* TX SYNC, 1-loop back mode; 0-normal mode*/
#define I2S_MC_RSYNC_LOOP_BACK          BIT(28)                     /* RX SYNC, 1-loop back mode; 0-normal mode*/

#define I2S_MC_INTR_STAT                (0x04UL)
#define I2S_MC_T_UNDERR                 BIT(0)                      /*TX underrun event*/
#define I2S_MC_T_UNDERR_CODE            (BIT_WIDTH(3) << 1)         /*TX underrun channel's number, clear by reset I2S_MC_T_UNDERR*/
#define I2S_MC_R_OVERR                  BIT(4)                      /*RX overrun error*/
#define I2S_MC_R_OVERR_CODE             (BIT_WIDTH(3) << 5)         /*RX overrun channel's number, clear by reset I2S_MC_R_OVERR*/
#define I2S_MC_TFIFO_EMPTY              BIT(8) 
#define I2S_MC_TFIFO_AEMPTY             BIT(9)
#define I2S_MC_TFIFO_FULL               BIT(10)
#define I2S_MC_TFIFO_AFULL              BIT(11)
#define I2S_MC_RFIFO_EMPTY              BIT(12)
#define I2S_MC_RFIFO_AEMPTY             BIT(13)
#define I2S_MC_RFIFO_FULL               BIT(14)          
#define I2S_MC_RFIFO_AFULL              BIT(15)

#define I2S_MC_SRR                      (0x08UL)
#define I2S_MC_T_SAMPLE_RATE            (BIT_WIDTH(10))                       
#define I2S_MC_T_RESOLUTION             (BIT_WIDTH(5)  << 11)       /* value = resolution - 1*/
#define I2S_MC_R_SAMPLE_RATE            (BIT_WIDTH(10) << 16)                       
#define I2S_MC_R_RESOLUTION             (BIT_WIDTH(5)  << 27)       /* value = resolution - 1*/
#define I2S_MC_T_SAMPLE_RATE_OFFSET     (0)                       
#define I2S_MC_T_RESOLUTION_OFFSET      (11)       
#define I2S_MC_R_SAMPLE_RATE_OFFSET     (16)                      
#define I2S_MC_R_RESOLUTION_OFFSET      (27)       

#define I2S_MC_CID_CRTL                 (0x0cUL)
#define I2S_MC_STROBE(ch)               BIT(ch)                     /* 0-clock enable, 1-clock is blocked*/
#define I2S_MC_STROBE_TS                BIT(8)
#define I2S_MC_STROBE_RS                BIT(9)
#define I2S_MC_INTREQ_MASK              BIT(15)                     /* 0-mask all of the int req, 1-irq use individual mask*/
#define I2S_MC_MASK(ch)                 BIT((ch) + 16)              /* overrun and underrun mask*/
#define I2S_MC_TFIFO_EMPTY_MASK         BIT(24)
#define I2S_MC_TFIFO_AEMPTY_MASK        BIT(25)
#define I2S_MC_TFIFO_FULL_MASK          BIT(26)
#define I2S_MC_TFIFO_AFULL_MASK         BIT(27)
#define I2S_MC_RFIFO_EMPTY_MASK         BIT(28)
#define I2S_MC_RFIFO_AEMPTY_MASK        BIT(29)
#define I2S_MC_RFIFO_FULL_MASK          BIT(30)
#define I2S_MC_RFIFO_AFULL_MASK         BIT(31)

#define I2S_MC_TFIFO_STAT               (0x10UL)        /*tx fifo level, ro*/

#define I2S_MC_RFIFO_STAT               (0x14UL)        /*rx fifo level, ro*/

#define I2S_MC_TFIFO_CTRL               (0x18UL)
#define I2S_MC_T_AEMPTY                 (BIT_WIDTH(15))
#define I2S_MC_T_AFULL                  (BIT_WIDTH(15) << 16)

#define I2S_MC_RFIFO_CTRL               (0x1cUL)
#define I2S_MC_R_AEMPTY                 (BIT_WIDTH(15))
#define I2S_MC_R_AFULL                  (BIT_WIDTH(15) << 16)
#define I2S_MC_AEMPTY_OFFSET            (0)
#define I2S_MC_AFULL_OFFSET             (16)

#define I2S_MC_DEV_CONF                 (0x20UL)
#define I2S_MC_TRAN_SCK_POLAR           BIT(0)          /*1-data updated on the falling edge of the bit clock ws, 0-rising edge*/
#define I2S_MC_TRAN_WS_POLAR            BIT(1)          /*1- ws high for left channel; 0-ws low for left channel*/    
#define I2S_MC_TRAN_APB_ALIGN_LR        BIT(2)          /*1- MSB side alignment of the resolution-width transmitted data sample at the apb bus*/
#define I2S_MC_TRAN_I2S_ALIGN_LR        BIT(3)          /*1- MSB align the digital data sample */
#define I2S_MC_TRAN_DATA_WS_DEL         BIT(4)          /*1- sampling data at the first rising/falling edge after ws signal, 0-at the second edge*/
#define I2S_MC_TRAN_WS_DSP_MOD          BIT(5)          /*1- DSP mode, 0- other mode*/
#define I2S_MC_REC_SCK_POLAR            BIT(6)
#define I2S_MC_REC_WS_POLAR             BIT(7)
#define I2S_MC_REC_APB_ALIGN_LR         BIT(8)
#define I2S_MC_REC_I2S_ALIGN_LR         BIT(9)
#define I2S_MC_REC_DATA_WS_DEL          BIT(10)
#define I2S_MC_REC_WS_DSP_MOD           BIT(11)

#define I2S_MC_POLL_STAT                (0x24UL)
#define I2S_MC_POLL_T_EMPTY             BIT(0)          /* 1-empty 0-not empty*/
#define I2S_MC_POLL_T_AEMPTY            BIT(1)          /* 1-aempty 0-not aempty*/
#define I2S_MC_POLL_T_UNDERR            BIT(2)          
#define I2S_MC_POLL_R_FULL              BIT(4) 
#define I2S_MC_POLL_R_AFULL             BIT(5) 
#define I2S_MC_POLL_R_OVERR             BIT(6) 

#define I2S_MC_TX_FIFO                  (0x3cUL)
#define I2S_MC_RX_FIFO                  (0x3cUL)

#define I2S_EN_TR_CFG_OFFSET            (8)
#define I2S_MC_FIFO_RST                 (I2S_MC_TFIFO_RST | I2S_MC_RFIFO_RST | I2S_MC_TSYNC_RST | I2S_MC_RSYNC_RST)
#define I2S_MC_INTREQ_TX_MASK           (I2S_MC_TFIFO_EMPTY_MASK | I2S_MC_TFIFO_AEMPTY_MASK)
#define I2S_MC_INTREQ_RX_MASK           (I2S_MC_RFIFO_FULL_MASK | I2S_MC_RFIFO_AFULL_MASK)

#define I2S_MC_INTREQ_TX_STAT           (I2S_MC_TFIFO_AEMPTY | I2S_MC_TFIFO_EMPTY)
#define I2S_MC_INTREQ_RX_STAT           (I2S_MC_RFIFO_AFULL | I2S_MC_RFIFO_FULL)
/*TSYNC_RST/RSYNC_RST must be setting to high simultaneously or after enable all tx/rx*/
//#define I2S_MC_I2S_EN_ALL               (BIT_WIDTH(8) | I2S_MC_TSYNC_RST | I2S_MC_RSYNC_RST) 
#define I2S_MC_I2S_EN_ALL               (BIT_WIDTH(8) | I2S_MC_TSYNC_RST | I2S_MC_RSYNC_RST)

#endif




