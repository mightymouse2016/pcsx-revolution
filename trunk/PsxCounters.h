/*  Pcsx - Pc Psx Emulator
 *  Copyright (C) 1999-2003  Pcsx Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __PSXCOUNTERS_H__
#define __PSXCOUNTERS_H__

#include "PsxCommon.h"

struct PSXCNT_MODE
{
#if defined(__ppc__) || defined(__BIGENDIAN__)
	u32 garbage:22;

	u32 Div:1;

	u32 ClockSource:1;

	u32 IRQ2:2;
	u32 IRQ1:2;

	u32 Tar:1;

	u32 unused:2;

	u32 Disabled:1;
#else
	// General count enable/status.  If 0, no counting happens.
	// This flag is set/unset by the gates.
	u32 Disabled:1;

	// Unused / Gates status?
	u32 unused:2;

	// 0 Count to $ffff
	// 1 Count to value in target register
	u32 Tar:1;

	//Set both for IRQ on target reached.
	u32 IRQ1:2;
	u32 IRQ2:2;

	// 0 - System clock (it seems)
	// 1 - Pixel clock (counter 0)
	//     Horizontal retrace (counter 1)
	u32 ClockSource:1;

	// 0 - System clock (it seems)
	// 1 - 1/8 * System clock (counter 2)
	u32 Div:1;

/*
	When ClockSource of the counters is zero, they all run at the
		same speed. This speed seems to be about 8 times the normal
		speed of root counter 2, which is specified as 1/8 the system
		clock.
*/
#endif
};

typedef struct {
	u32 count, target;
	u32 IsFutureTarget:1;
	u32 IsCounting:1;
	union {
		u32 mode;
		struct PSXCNT_MODE mode_st;
	};
	u32 sCycle, Cycle, rate, interrupt;
} psxCounter;

extern psxCounter psxCounters[5];

void psxRcntInit();
void psxRcntUpdate();
void psxRcntUpdate0();
void psxRcntUpdate1();
void psxRcntUpdate2();
void psxRcntUpdate3();
void psxRcntUpdate4();
void psxRcntWcount(int index, u32 value);
void psxRcntWmode(int index, u32 value);
void psxRcntWtarget(int index, u32 value);
u32 psxRcntRcount(int index);
u32 psxRcntRmode(int index);
int psxRcntFreeze(gzFile f, int Mode);

void psxUpdateVSyncRate();

#endif /* __PSXCOUNTERS_H__ */
