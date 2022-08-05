/**
 * @file
 * Multitap manager functions
 */

#ifndef __XMTAPMAN_H__
#define __XMTAPMAN_H__

#include <types.h>
#include <irx.h>

s32 mtapPortOpen(u32 port);
s32 mtapPortClose(u32 port);
s32 mtapGetSlotNumber(u32 port);
s32 mtapChangeSlot(u32 port, u32 slot);

#endif /* __XMTAPMAN_H__ */
