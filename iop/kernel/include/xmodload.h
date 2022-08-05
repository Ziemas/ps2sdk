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
 * Additional modload functions only found in newer IOPRP images
 */

#ifndef __XMODLOAD_H__
#define __XMODLOAD_H__

#include <modload.h>

int GetModuleIdList(int *readbuf, int readbufsize, int *modulecount);

typedef struct {
	char name[56];
	u16 version;
	u16 flags;
	int id;
	u32 entry_addr;
	u32 gp_value;
	u32 text_addr;
	u32 text_size;
	u32 data_size;
	u32 bss_size;
	u32 lreserve[2];
} ModuleStatus;

int ReferModuleStatus(int, ModuleStatus *status);
int GetModuleIdListByName(const char *name, int *readbuf, int readbufsize, int *modulecount);

typedef struct {
	int (*beforeOpen)(void *opt, const char *filename, int flag);
	int (*afterOpen)(void *opt, int fd);
	int (*close)(void *opt, int fd);
	int (*setBufSize)(void *opt, int fd, size_t nbyte);
	int (*beforeRead)(void *opt, int fd, size_t nbyte);
	int (*read)(void *opt, int fd, void *buf, size_t nbyte);
	int (*lseek)(void *opt, int fd, long offset, int whence);
	int (*getfsize)(void *opt, int fd);
} LDfilefunc;

typedef struct {
	char position;
	char access;
	char creserved[2];
	void *distaddr;
	int distoffset;
	LDfilefunc *functable;
	void *funcopt;
	int ireserved[3];
} LMWOoption;

int LoadModuleWithOption(const char *filename, const LMWOoption *option);
int StopModule(int, int arglen, const char *args, int *result);
int UnloadModule(int);
int SearchModuleByName(const char *name);
int SearchModuleByAddress(const void *addr);
int SelfStopModule(int arglen, const char *args, int *result);
void SelfUnloadModule(void);
void *AllocLoadMemory(int type, unsigned long size, void *addr);
int FreeLoadMemory(void *area);
int SetModuleFlags(int, int flag);

#endif /* __XMODLOAD_H__ */
