#ifndef YMODEM_H
#define YMODEM_H

//#define DEBUG

#define ETX  0x3  /* ^C */
#define ENQ  0x5  /* ^E */
#define BEL  0x7  /* ^G */
#define DLE  0x10 /* ^P */
#define XON  0x11 /* ^Q */
#define XOFF 0x13 /* ^S */
#define NAK  0x15 /* ^U */
#define CAN  0x18 /* ^X */

#define CPMEOF 0x1A /* ^Z */

#define HEAD_OK          0 /*format,blknum and crc check all OK*/
#define COM_TRANS_CONTI  1
#define FORMAT_UNSUPPORT 0xFFFF0001
#define CRC_ERR          0xFFFF0002
#define CHECKSUM_ERR     0xFFFF0003
#define BLK_UNVILID      0xFFFF0004
#define BLK_REPEAT       0xFFFF0005
#define BLK_LOSS         0xFFFF0006

#define FILE_OPEN_ERR 0xFFFF0007
#define NO_MORE_FILE  0xFFFF0008
#define FILE_READ_ERR 0xFFFF0009

#define FILE_UNVILID 0xFFFF000A
#define MALLOC_ERROR 0xFFFF000B

#define COM_OPEN_ERR  0xFFFF000C
#define COM_SET_ERR   0xFFFF000D
#define COM_READ_ERR  0xFFFF000E
#define COM_WRITE_ERR 0xFFFF000F

#define SET_EV_MASK_ERR  0xFFFF0010
#define GET_EV_MASK_ERR  0xFFFF0011
#define CMD_UNVILID      0xFFFF0012
#define COM_TRANS_REPEAT 0xFFFF0013

#define FIRST_ACK       1
#define CAN_IND         2
#define ALL_NEED_OFFSET 3

#ifdef WINYWY
#define _O_NONBLOCK 0
#else
#define _O_NONBLOCK     O_NONBLOCK
#define _O_RDWR         O_RDWR
#define _O_RDONLY       O_RDONLY
#define _O_BINARY       0
#define _open(a, b)     open(a, b)
#define _read(a, b, c)  read(a, b, c)
#define _write(a, b, c) write(a, b, c)
#define _close(a)       close(a)
#define _lseek(a, b, c) lseek(a, b, c)
#endif

char CrcFlag;
unsigned int FileLen;
unsigned int FileLenBkup;

void delay(int clock_count);
int set_com_common(char *device); // common for receive and send
int control_recv(char *device);
int control_send(char *mem, int count);
void out_message(void);

/*
 * * updcrc macro derived from article Copyright (C) 1986 Stephen Satchell.
 * *  NOTE: First srgument must be in range 0 to 255.
 * *        Second argument is referenced twice.
 * *
 * * Programmers may incorporate any or all code into their programs,
 * * giving proper credit within the source. Publication of the
 * * source routines is permitted so long as proper credit is given
 * * to Stephen Satchell, Satchell Evaluations and Chuck Forsberg,
 * * Omen Technology.
 * */

extern uint16_t crc16_tab[];
#define updcrc(cp, crc) (crc16_tab[((crc >> 8) & 255)] ^ (crc << 8) ^ cp)

#endif
