/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2004, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

/**
 * @file
 * Definitions and imports for cdvdman
 */

#ifndef __CDVDMAN_H__
#define __CDVDMAN_H__

#include <types.h>
#include <irx.h>

#include <libcdvd-common.h>

//IOP-only libcdvd function prototypes.
int sceCdCheckCmd(void);
int sceCdNop(void);
void *sceGetFsvRbuf(void);
int sceCdstm0Cb(void (*p)(int));
int sceCdstm1Cb(void (*p)(int));
int sceCdSC(int code, int *param);
/*	Within all CDVDMAN modules, sceCdReadClock and sceCdRC both exist. In the old one, both have exactly the same code.
	In the newer ones, sceCdReadClock would automatically file off the most significant bit within the month field,
	while sceCdRC continued having its original behaviour of not changing the data.	*/
int sceCdRC(sceCdCLOCK *clock);
int sceCdRead0(u32 lsn, u32 sectors, void *buffer, sceCdRMode *mode, int csec, void *callback);

/** Reads DVD video.
 * SUPPORTED IN NEWER CDVDMAN MODULES WITHIN DVD PLAYER IOPRP ONLY
 *
 * @return 1 on success, 0 on failure.
 */
int sceCdRV(u32 lsn, u32 sectors, void *buf, sceCdRMode *mode, int arg5, void *cb);

/** send an s-command by function number
 * 
 * @param cmdNum command number
 * @param inBuff input buffer  (can be null)
 * @param inBuffSize size of input buffer  (0 - 16 bytes)
 * @param outBuff output buffer (can be null)
 * @return 1 on success, 0 on failure.
 */
int sceCdApplySCmd(u8 cmdNum, const void* inBuff, u16 inBuffSize, void *outBuff);

/** send an s-command by function number
 * 
 * @param cmdNum command number
 * @param inBuff input buffer  (can be null)
 * @param inBuffSize size of input buffer  (>= 16 bytes)
 * @param outBuff output buffer (can be null)
 * @return 1 on success, 0 on failure.
 */
int sceCdApplySCmd2(u8 cmdNum, const void* inBuff, unsigned long int inBuffSize, void *outBuff);

/** send an n-command by function number
 * 
 * @param cmdNum command number
 * @param inBuff input buffer  (can be null)
 * @param inBuffSize size of input buffer  (0 - 16 bytes)
 * @param outBuff output buffer (can be null)
 * @return 1 on success, 0 on failure.
 */
int sceCdApplyNCmd(u8 cmdNum, const void* inBuff, u16 inBuffSize, void* outBuff);

/** Controls spindle speed? Not sure what it really does.
 * SUPPORTED IN XCDVDMAN ONLY
 *
 * @param speed Speed mode.
 * @return 1 on success, 0 on failure.
 */
int sceCdSpinCtrlIOP(u32 speed);

//DNAS functions

/** Reads the Disk ID.
 * SUPPORTED IN NEWER CDVDMAN MODULES INCLUDED WITHIN DNAS IOPRP ONLY
 *
 * @param id integer where the Disk ID is stored.
 * @return 1 on success, 0 on failure.
 */
int sceCdReadDiskID(unsigned int *id);

#endif /* __CDVDMAN_H__ */
