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

#ifndef __LOADCORE_H__
#define __LOADCORE_H__

#include <types.h>
#include <irx.h>

#define MODULE_RESIDENT_END		0
#define MODULE_NO_RESIDENT_END	1
#define MODULE_REMOVABLE_END	2 // Only for 'modload' > v1.2

/** Module info entry. Taken from iopmgr. */
typedef struct _ModuleInfo {
	struct _ModuleInfo *next;
	char	*name;
	u16	version;
	/** For modload shipped with games. */
	u16	newflags;
	u16	id;
	/** I believe this is where flags are kept for BIOS versions. */
	u16	flags;
	/** _start */
	u32	entry;
	u32	gp;
	u32	text_start;
	u32	text_size;
	u32	data_size;
	u32	bss_size;
	u32	unused1;
	u32	unused2;
} ModuleInfo_t;

typedef struct _IopModuleID {
    const char *name;
    unsigned short int version;
} IopModuleID_t;

typedef struct _FileInfo {
	u32 ModuleType;
	void *EntryPoint;
	void *gp;
	void *text_start;
	u32 text_size;
	u32 data_size;
	u32 bss_size;
	u32 MemSize;
	IopModuleID_t *mod_id;
} FileInfo_t;

typedef struct _iop_library {
	struct	_iop_library *prev;
	struct	irx_import_table *caller;
	u16	version;
	u16	flags;
	char	name[8];
	void	*exports[];
} iop_library_t;

/** Loadcore internal data structure. Based on the one from loadcore.c of the FPS2BIOS project from PCSX2. */
typedef struct tag_LC_internals {
	iop_library_t* let_next, *let_prev;	//let_next = tail, let_prev = head. I don't know what "let" and "mda" stand for.
	iop_library_t* mda_next, *mda_prev;
	/** Points to the module image information structure chain that usually starts at 0x800. */
	ModuleInfo_t *image_info;
	int	module_count;
	int	module_index;
} lc_internals_t;

typedef struct {
	u16	value;
	u8	id;
	u8	len;
	u32	data[];
} iop_bootmode_t;


typedef struct{	//FIXME: Incomplete structure definition. Provided only for compatibility, as I don't know what the full structure is like.
	void *callback;
}iop_init_entry_t;

typedef int (*BootupCallback_t)(iop_init_entry_t* next, int delayed);

lc_internals_t *GetLoadcoreInternalData(void);

void FlushIcache(void);
void FlushDcache(void);

int RegisterLibraryEntries(struct irx_export_table *exports);
int ReleaseLibraryEntries(struct irx_export_table *exports);

int LinkImports(void* addr, int size);
int UnlinkImports(void* addr, int size);

int RegisterNonAutoLinkEntries(struct irx_export_table *exports);

void *QueryLibraryEntryTable(iop_library_t *library);
int * QueryBootMode(int mode);
void RegisterBootMode(iop_bootmode_t *b);

int SetNonAutoLinkFlag(struct irx_export_table *export);
int UnsetNonAutoLinkFlag(struct irx_export_table *export);

void LinkModule(ModuleInfo_t *mi);
void UnlinkModule(ModuleInfo_t *mi);

int RegisterPostBootCallback(BootupCallback_t func, int priority, int *stat);

void SetCacheCtrl(u32 val);

int ReadModuleHeader(void* image, FileInfo_t *result);
int LoadModuleImage(void* image, FileInfo_t *fi);
ModuleInfo_t *FindImageInfo(void* addr);

#endif /* __LOADCORE_H__ */
