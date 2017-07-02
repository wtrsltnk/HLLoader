// WADMiptex.h: interface for the CWADMiptex class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WADMIPTEX_H
#define WADMIPTEX_H

#include <windows.h>
#include "wadtypes.h"

class CWADMiptex  
{
private:
	char TextureName[64];
	int TextureWidth, TextureHeight;
	char* TextureData;
	byte* TextureBits;
	byte* TexturePalette;
public:
	CWADMiptex();
	CWADMiptex(char* texname);
	virtual ~CWADMiptex();

	void InitName(char* name);
	void InitData(char* name, char* data);
	bool HasData();

	char* GetName();
	bool WriteBMP(char* path);

	int GetWidth();
	int GetHeight();

	char* GetData();
	byte* GetPalette();
};

#endif
