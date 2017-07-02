// BSPFile.h: interface for the CBSPFile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BSPFILE_H
#define BSPFILE_H

////////////////////////////////////////////////////////////
// Header & Lump information specification
////////////////////////////////////////////////////////////
#define BSPVERSION	30
#define	TOOLVERSION	2
#define HEADER_LUMPS 15

#include "../common/BaseFile.h"
#include "BSPLump.h"
#include "../WAD/WADMiptex.h"
#include "../MAP/MAPFile.h"

typedef struct
{
	int			version;	
	tBspLump	lumps[HEADER_LUMPS];
} tHeader;

enum HLBSPLumpTypes
{
	Entities		 = 0,
	Planes			 = 1,
	Textures		 = 2,
	Vertexes		 = 3,
	Visibility		 = 4,
	Nodes			 = 5,
	Texinfo			 = 6,
	Faces			 = 7,
	Lighting		 = 8,
	Clipnodes		 = 9,
	Leafs			 = 10,
	Marksurfaces	 = 11,
	Edges			 = 12,
	Surfedges		 = 13,
	Models			 = 14
};

class CBSPFile : public CBaseFile
{
private:
	CBSPLump FileLumps[HEADER_LUMPS];

	int TextureCount;
	int AllocmiptexCount;
	CWADMiptex* FileTextures;

	typedef CArrayList <char*> WadfilesList;
	WadfilesList FileWadfiles;

	CMAPFile FileEntities;

	bool ParseData();
	int GetLumpSize(int lump);

	void InitTextures();
	void InitEntities();
	void FindWadFiles();
public:
	CBSPFile();
	virtual ~CBSPFile();

	bool LoadBSPFile(const char* filename);
	void Clear();

	char* GetTextureName(int index);
	int GetNumTextures();
	CWADMiptex* GetMiptex(int i);
	bool WriteBMP(char* path, int index);
	bool WriteEntities(char* filename);

	int GetNumEntities();
	CMAPEntity* GetEntity(int index);

	int GetNumWadfiles();
	char* GetWadfilePath(int index);
};

#endif
