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
 * Heap library.
 */

#ifndef __HEAPLIB_H__
#define __HEAPLIB_H__

#include <types.h>
#include <irx.h>

void *CreateHeap(int heapblocksize, int flag);
void DeleteHeap(void *heap);
void *AllocHeapMemory(void *heap, size_t nbytes);
int FreeHeapMemory(void *heap, void *ptr);
int HeapTotalFreeSize(void *heap);

void HeapPrepare(void* mem, int size);
int HeapChunkSize(void* chunk);

#endif /* __HEAPLIB_H__ */
