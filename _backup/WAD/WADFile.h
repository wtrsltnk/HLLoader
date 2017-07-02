// WADFile.h: interface for the CWADFile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WADFILE_H
#define WADFILE_H

#include "BaseFile.h"
#include "WADLump.h"
#include "WADMiptex.h"

class CWADFile : public CBaseFile
{
private:
	int LumpCount;
	CWADLump* FileLumps;

	bool ParseData();
public:
	CWADFile();
	virtual ~CWADFile();

	bool LoadWADFile(const char* filename);
	void Clear();

	char* GetTextureName(int index);
	int GetNumTextures();
	CWADMiptex* GetMiptex(int index);
	bool WriteBMP(char* path, int index);
};

#endif
