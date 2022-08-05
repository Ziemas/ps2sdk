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
 * Additional loadcore functions only found in newer IOPRP images
 */

#ifndef __XLOADCORE_H__
#define __XLOADCORE_H__

#include <loadcore.h>

void ApplyElfRelSection(void *buffer, const void *module, int element_count);
void InitLoadedModInfo(FileInfo_t *ModuleInfo, ModuleInfo_t *ModInfo);
int SetRebootTimeLibraryHandlingMode(struct irx_export_table *exports, int mode);

#endif /* __XLOADCORE_H__ */
