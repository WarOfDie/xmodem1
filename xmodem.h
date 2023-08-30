/*
 * xmodem.h
 *
 *  Created on: Aug 30, 2023
 *      Author: alper
 */

#ifndef SRC_XMODEM_H_
#define SRC_XMODEM_H_


#define PACKET_HEADER           3    /* SOH 00 FF; or STX 01 FE, etc */
#define PACKET_CRC              2    /* 2 bytes CRC */
#define PACKET_SIZE             128  /* The packet in SOH, normally for 1st packet used for filename and file szie*/

#define FILENAME_LEN            96   /* The filename cannot include space */
#define FILESIZE_LEN            16   /* I use unsigned int which is 4 bytes long */

#define SOH                     0x01  /* start of 128-byte data packet */
#define EOT                     0x04  /* end of transmission */
#define ACK                     0x06  /* acknowledge */
#define NAK                     0x15  /* negative acknowledge */
#define CAN                     0x18  /* two of these in succession aborts transfer */
#define CRC                     0x43  /* 'C' == 0x43, request 16-bit CRC */
int xmodemReceive(int *huart,char *buf);


#endif /* SRC_XMODEM_H_ */
