// WADFile.cpp: implementation of the CWADFile class.
//
//////////////////////////////////////////////////////////////////////

#include "WADFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWADFile::CWADFile()
{
	this->LumpCount = 0;
	this->FileLumps = 0;
}

CWADFile::~CWADFile()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWADFile::Clear()
{
	CBaseFile::Clear();

	if (this->FileLumps)
	{
		delete [] this->FileLumps;
		this->FileLumps = 0;
	}

	this->LumpCount = 0;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CWADFile::LoadWADFile(const char* filename)
{
	bool res = true;

	try
	{
		CBaseFile::LoadFile(filename);
	}
	catch(char* err)
	{
		res = false;
		throw(err);
	}

	if (!ParseData())
		throw("Can\'t parse the data from the file");
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CWADFile::ParseData()
{
	tWadHeader* hdr;

	hdr = (tWadHeader*)this->FileData;
	if (strncmp(hdr->identification, "WAD3", 4))
		return false;

	this->LumpCount = hdr->numlumps;
	this->FileLumps = new CWADLump[this->LumpCount];

	tWadLump* lumpshdr;
	lumpshdr = (tWadLump*)(this->FileData + hdr->infotableofs);

	for (int i = 0; i < this->LumpCount; i++)
	{
		this->FileLumps[i].InitData(this->FileData + lumpshdr[i].filepos, lumpshdr[i].size, lumpshdr[i].name);
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CWADFile::GetTextureName(int index)
{
	char* res = 0;

	if (index < this->LumpCount)
		res = this->FileLumps[index].GetName();

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CWADFile::GetNumTextures()
{
	return this->LumpCount;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CWADMiptex* CWADFile::GetMiptex(int index)
{
	CWADMiptex* res = 0;

	if (index < this->LumpCount)
		res = this->FileLumps[index].GetMiptex();

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CWADFile::WriteBMP(char* path, int index)
{
	bool res = false;

	if (index < this->LumpCount)
		res = this->FileLumps[index].WriteBMP(path);

	return res;
}
