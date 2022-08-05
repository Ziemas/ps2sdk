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
 * rom0:XSIO2MAN module definitions
 */

#ifndef __XSIO2MAN_H__
#define __XSIO2MAN_H__

#include <sio2man.h>

typedef int (*sio2_mtap_change_slot_cb_t)(s32 *status);
typedef int (*sio2_mtap_get_slot_max_cb_t)(int port);
typedef int (*sio2_mtap_get_slot_max2_cb_t)(int port);
typedef void (*sio2_mtap_update_slots_t)(void);

void sio2_transfer_reset(void);
void sio2_mtap_transfer_init(void);
int sio2_transfer2(sio2_transfer_data_t *td);
void sio2_transfer_reset2(void);
void sio2_mtap_change_slot_set(sio2_mtap_change_slot_cb_t cb);
void sio2_mtap_get_slot_max_set(sio2_mtap_get_slot_max_cb_t cb);
void sio2_mtap_get_slot_max2_set(sio2_mtap_get_slot_max2_cb_t cb);
void sio2_mtap_update_slots_set(sio2_mtap_update_slots_t cb);
int sio2_mtap_change_slot(s32 *arg);
int sio2_mtap_get_slot_max(int port);
int sio2_mtap_get_slot_max2(int port);
void sio2_mtap_update_slots(void);

#endif /* __XSIO2MAN_H__ */
