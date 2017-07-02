// BaseFile.cpp: implementation of the CBaseFile class.
//
//////////////////////////////////////////////////////////////////////

#include "BaseFile.h"
#include <windows.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseFile::CBaseFile()
{
}

CBaseFile::~CBaseFile()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CBaseFile::LoadFile(const char* filepath)
{
	bool res = false;
	FILE* file;

	if (filepath)
	{
		if (strcmp(filepath, "") != 0)
		{
			SetFilePath(filepath);

			file = ::fopen(filepath, "rb");
			if (file)
			{
				int pos = ::ftell(file);
				::fseek(file, 0, SEEK_END);
				int end = ::ftell(file);
				::fseek(file, pos, SEEK_SET);

				this->FileLength = end;
				this->FileData = new char[this->FileLength];

				if (this->FileData)
				{
					::fread(this->FileData, sizeof(char), this->FileLength, file);
					::fclose(file);
					res = true;
				}
			}
		}
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CBaseFile::SaveFile(const char* filepath)
{
	bool res = false;

	return res;
}
	
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CBaseFile::SetFilePath(const char* filepath)
{
	strcpy(this->FilePath, filepath);

	int len = strlen(filepath);

	int dot = 0;
	int slash = 0;

	int i = len;
	while (i > 0)
	{
		if (filepath[i] == '.')
			dot = i;
		if (filepath[i] == '\\' || filepath[i] == '/')
		{
			slash = i;
			break;
		}
		i--;
	}

	slash++;
	i = 0;
	while (i < dot-slash)
	{
		this->FileName[i] = this->FilePath[slash+i];
		i++;
	}
	this->FileName[i] = '\0';
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CBaseFile::Clear()
{
	if (this->FileData)
	{
		delete [] this->FileData;
		this->FileData = 0;
		this->FileLength = 0;
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CBaseFile::GetFilePath()
{
	return this->FilePath;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CBaseFile::GetFileName()
{
	return this->FileName;
}
