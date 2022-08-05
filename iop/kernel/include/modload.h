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
 * Kernel module loader.
 */

#ifndef __MODLOAD_H__
#define __MODLOAD_H__

#include <types.h>
#include <irx.h>

void *GetModloadInternalData(void **pInternalData);

int ReBootStart(const char *command, unsigned int flags);
int LoadModuleAddress(const char *name, int, int);
int LoadModule(const char *name);
int LoadStartModule(const char *name, int arglen, const char *args, int *result);
int StartModule(int, const char *name, int arglen, const char *args, int *result);
int LoadModuleBufferAddress(void *buffer, int, int);
int LoadModuleBuffer(void *buffer);
int LoadStartKelfModule(const char *name, int arglen, const char *args, int *result);
void SetSecrmanCallbacks(void *SecrCardBootFile_fnc, void *SecrDiskBootFile_fnc, void *SetLoadfileCallbacks_fnc);
void SetCheckKelfPathCallback(void *CheckKelfPath_fnc);
void GetLoadfileCallbacks(void **CheckKelfPath_fnc, void **SetLoadfileCallbacks_fnc);
int IsIllegalBootDevice(const char *path);

#endif /* __MODLOAD_H__ */
