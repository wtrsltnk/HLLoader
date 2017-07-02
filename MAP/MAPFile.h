// MAPFile.h: interface for the CMAPFile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MAPFILE_H
#define MAPFILE_H

#include "../common/BaseFile.h"
#include "MAPParser.h"
#include "MAPEntity.h"
#include "../WAD/WADMiptex.h"

#include "../common/ArrayList.h"

class CMAPFile : public CBaseFile
{
private:
	typedef CArrayList <CMAPEntity*> EntityList;
	EntityList FileEntities;

	typedef CArrayList <char*> WadfilesList;
	WadfilesList FileWadfiles;

	typedef CArrayList <CWADMiptex*> TextureList;
	TextureList FileTextures;

	bool ParseEntites(CMAPParser* mp);
    bool SaveEntities(FILE* file) throw();
	void FindWadFiles();
	char* GetWadfile(char* val, int start, int length);
	void FindTextures();
public:
	CMAPFile();
	virtual ~CMAPFile();

	bool LoadMAPFile(const char* filename) throw();
	bool LoadMAPBuffer(char* buffer, const char* name) throw();
	bool SaveMAPFile(const char* filename) throw();
	bool SaveMAPFile(FILE* file) throw();
	void Clear();

	int GetNumEntities();
	int GetNextEntity(char* classname, int current);
	CMAPEntity* GetEntity(int index);

	int GetNumWadfiles();
	char* GetWadfilePath(int index);

	int GetNumTextures();
	char* GetTexture(int index);
};

#endif
