/*****************************
** Written by Shell25       **
** 1396/11/1                **
******************************/
#ifndef _PE_LDR_H
#define _PE_LDR_H

#include <windows.h>

typedef struct
{
	PIMAGE_DOS_HEADER		pDosHeader;
	PIMAGE_NT_HEADERS		pNtHeaders;
	PIMAGE_SECTION_HEADER   pNtSectionHeader;

	DWORD					dwImage;
	DWORD					dwImageSizeOnDisk;
} PE_LDR_PARAM;

union HexToChar
{
	unsigned int twoChar;
	unsigned char character[2];
};
#endif