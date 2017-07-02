// WADLump.h: interface for the CWADLump class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WADLUMP_H
#define WADLUMP_H

#include <stdio.h>
#include "WADMiptex.h"
#include "wadtypes.h"

class CWADLump  
{
private:	
	int LumpLength;
	char* LumpData;
	
	CWADMiptex miptex;
public:
	CWADLump();
	virtual ~CWADLump();

	bool InitData(char* data, int len, char* name);

	CWADMiptex* GetMiptex();
	char* GetName();

	bool WriteBMP(char* path);
};

#endif
