/***************************************************************************
 *   Copyright (C) 2007 Ryan Schultz, PCSX-df Team, PCSX team              *
 *   schultz.ryan@gmail.com, http://rschultz.ath.cx/code.php               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Steet, Fifth Floor, Boston, MA 02111-1307 USA.            *
 ***************************************************************************/


#ifndef _SIO_H_
#define _SIO_H_

#include "psxcommon.h"
#include "r3000a.h"
#include "psxmem.h"
#include "plugins.h"
#include "psemu_plugin_defs.h"

#define MCD_SIZE	(1024 * 8 * 16)

typedef struct {
	u16 StatReg;
	u16 ModeReg;
	u16 CtrlReg;
	u16 BaudReg;

	u8  buf[256];
	u32 bufcount;
	u32 parp;
	u32 mcdst,rdwr;
	u8  adrH,adrL;
	u32 padst;
	u32 mtapst;
	u32 packetsize;

	u8  terminator;
	u8  mode;
	u8  mc_command;
	u32 lastsector;
	u32 sector;
	u32 k;
	u32 count;
} sio_t;

extern sio_t sio;

// Status Flags
#define TX_RDY		0x0001
#define RX_RDY		0x0002
#define TX_EMPTY	0x0004
#define PARITY_ERR	0x0008
#define RX_OVERRUN	0x0010
#define FRAMING_ERR	0x0020
#define SYNC_DETECT	0x0040
#define DSR			0x0080
#define CTS			0x0100
#define IRQ			0x0200

// Control Flags
#define TX_PERM		0x0001
#define DTR			0x0002
#define RX_PERM		0x0004
#define BREAK		0x0008
#define RESET_ERR	0x0010
#define RTS			0x0020
#define SIO_RESET	0x0040

extern char Mcd1Data[MCD_SIZE], Mcd2Data[MCD_SIZE];

void sioInit();
unsigned char sioRead8();
void sioWrite8(unsigned char value);
void sioWriteCtrl16(unsigned short value);
void sioInterrupt();
int sioFreeze(gzFile f, int Mode);

void LoadMcd(int mcd, char *str);
void LoadMcds();
void SaveMcd(char *mcd, char *data, uint32_t adr, int size);
void CreateMcd(char *mcd);
void ConvertMcd(char *mcd, char *data);

typedef struct {
	char Title[48];
	short sTitle[48];
	char ID[14];
	char Name[16];
	int IconCount;
	short Icon[16*16*3];
	unsigned char Flags;
} McdBlock;

void GetMcdBlockInfo(int mcd, int block, McdBlock *info);

#endif