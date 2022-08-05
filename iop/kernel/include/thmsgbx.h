/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright (c) 2003 Marcus R. Brown <mrbrown@0xd6.org>
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

/**
 * @file
 * Inter-thread message boxes.
 */

#ifndef __THMSGBX_H__
#define __THMSGBX_H__

#include <types.h>
#include <irx.h>

//Message box attributes
#define MBA_THFIFO	0x000
#define MBA_THPRI	0x001
#define MBA_MSFIFO	0x000
#define MBA_MSPRI	0x004

typedef struct {
	unsigned int attr;
	unsigned int option;
} iop_mbx_t;

/* Besides the next pointer, this struct is actually user-defined.  You can
   define messages specific to your program:
       typedef struct {
           iop_message_t msg;
	   u32    mystuff;
	   ...
       } my_message_t;
*/
typedef struct _iop_message {
	struct iop_message *next;
	unsigned char priority;
	unsigned char unused[3];
} iop_message_t;

typedef struct _iop_mbx_status {
	unsigned int attr;
	unsigned int option;
	int numWaitThreads;
	int numMessage;
	iop_message_t *topPacket;
	int reserved[2];
} iop_mbx_status_t;

int CreateMbx(iop_mbx_t *mbx);
int DeleteMbx(int mbxid);

int SendMbx(int mbxid, void *msg);
int iSendMbx(int mbxid, void *msg);
int ReceiveMbx(void **msgvar, int mbxid);
int PollMbx(void **msgvar, int mbxid);

int ReferMbxStatus(int mbxid, iop_mbx_status_t *info);
int iReferMbxStatus(int mbxid, iop_mbx_status_t *info);

#endif /* __THMSGBX_H__ */
