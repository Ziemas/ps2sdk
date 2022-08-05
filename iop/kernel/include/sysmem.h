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
 * System memory manager.
 */

#ifndef __SYSMEM_H__
#define __SYSMEM_H__

#include <types.h>
#include <irx.h>
#include <stdarg.h>

// Allocation strategies
#define ALLOC_FIRST	0
#define ALLOC_LAST	1
#define ALLOC_ADDRESS	2

// see QueryBlockTopAddress, QueryBlockSize
#define USED	0x00000000
#define FREE	0x80000000

void * AllocSysMemory(int mode, int size, void *ptr);

int FreeSysMemory(void *ptr);

u32 QueryMemSize();
u32 QueryMaxFreeMemSize();
u32 QueryTotalFreeMemSize();
void * QueryBlockTopAddress(void *address);
int QueryBlockSize(void *address);

typedef int (KprintfHandler_t)(void *context, const char *format, va_list ap);

int Kprintf(const char *format,...);
void KprintfSet(KprintfHandler_t *, void *context);

#endif /* IOP_SYSMEM_H */
