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
 * ROM file system driver routines.
 * Not available on the protokernel version of ROMDRV.
 */

#ifndef __ROMDRV_H__
#define __ROMDRV_H__

#include <irx.h>

extern int romdrv_mount(int unit, void *start);
extern int romdrv_unmount(int unit);

#endif /* __ROMDRV_H__ */
