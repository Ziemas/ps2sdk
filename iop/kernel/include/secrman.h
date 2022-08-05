/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# Copyright (c) 2009 jimmikaelkael
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
*/

/**
 * @file
 * Definitions and imports for secrman module.
 */

#ifndef __SECRMAN_H__
#define __SECRMAN_H__

#include <types.h>
#include <irx.h>
#include <sio2man.h>
#include <libsecr-common.h>

typedef int (*McCommandHandler_t)(int port, int slot, sio2_transfer_data_t *sio2_trans_data);
typedef int (*McDevIDHandler_t)(int port, int slot);

void SecrSetMcCommandHandler(McCommandHandler_t handler);
void SecrSetMcDevIDHandler(McDevIDHandler_t handler);

int SecrAuthCard(int port, int slot, int cnum);
void SecrResetAuthCard(int port, int slot, int cnum);

#endif /* IOP_SECRMAN_H */
