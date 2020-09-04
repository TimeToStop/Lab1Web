#pragma once


typedef unsigned short WORD;
typedef unsigned int   DWORD;

#pragma pack(push, 1)

struct BMP
{
	WORD header;
	DWORD size;
	WORD reserved1;
	WORD reserved2;
	DWORD offset;
	DWORD sizeOfBitMap;
	DWORD width;
	DWORD height;
	WORD planes;
	WORD bpp;
	DWORD compression;
	DWORD imageSize;
	DWORD hResolution;
	DWORD vResolution;
	DWORD numberOfColors;
	DWORD numberOfImportantColors;	
};

#pragma pack(pop)
