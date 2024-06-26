/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright 2001-2009, ps2dev - http://www.ps2dev.org
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
# Defines all IRX imports.
*/

#ifndef IOP_IRX_IMPORTS_H
#define IOP_IRX_IMPORTS_H

#include <irx.h>

/* Please keep these in alphabetical order!  */
#if defined(BUILDING_RMMAN2) && !defined(BUILDING_RMMANX)
#include <cdvdman.h>
#endif
#include <intrman.h>
#ifdef BUILDING_RMMANX
#include <iomanX.h>
#endif
#include <loadcore.h>
#ifndef BUILDING_RMMAN2
#include <rsio2man.h>
#endif
#include <sifcmd.h>
#include <sifman.h>
#include <stdio.h>
#include <thbase.h>
#include <thevent.h>
#include <vblank.h>

#endif /* IOP_IRX_IMPORTS_H */
