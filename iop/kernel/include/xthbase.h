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
 * Additional thbase functions only found in newer IOPRP images
 */

#ifndef __XTHBASE_H__
#define __XTHBASE_H__

#include <thbase.h>

int GetThreadCurrentPriority(void);
unsigned int GetSystemTimeLow(void);
int ReferSystemStatus(iop_sys_status_t *info, size_t size);
int ReferThreadRunStatus(int thid, iop_thread_run_status_t *stat, size_t size);
int GetThreadStackFreeSize(int thid);
int GetThreadmanIdList(int type, int *readbuf, int readbufsize, int *objectcount);

#endif /* __XTHBASE_H__ */
