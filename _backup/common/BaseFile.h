// BaseFile.h: interface for the CBaseFile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BASEFILE_H
#define BASEFILE_H

class CBaseFile  
{
protected:
	char FileName[256];
	char FilePath[256];
	char* FileData;
	int FileLength;

	CBaseFile();
	virtual ~CBaseFile();

	bool LoadFile(const char* filepath);
	bool SaveFile(const char* filepath);
	void SetFilePath(const char* filepath);
	void Clear();

public:
	char* GetFilePath();
	char* GetFileName();
};

#endif
