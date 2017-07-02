// BSPFile.cpp: implementation of the CBSPFile class.
//
//////////////////////////////////////////////////////////////////////

#include "BSPFile.h"
#include "../WAD/wadtypes.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBSPFile::CBSPFile()
{
	memset(this->FilePath, 0, sizeof(this->FilePath));
	memset(&this->FileLumps, 0, sizeof(this->FileLumps));

	this->TextureCount = 0;
	this->AllocmiptexCount = 0;
	this->FileTextures = 0;
	this->FileData = 0;
}

CBSPFile::~CBSPFile()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CBSPFile::Clear()
{
	CBaseFile::Clear();

	if (this->FileTextures)
	{
		delete [] this->FileTextures;
		this->FileTextures = 0;
	}
	this->TextureCount = 0;
	this->AllocmiptexCount = 0;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CBSPFile::LoadBSPFile(const char* filename)
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
bool CBSPFile::ParseData()
{
	tHeader* hdr;
	
	hdr = (tHeader*)this->FileData;
	if (hdr->version != BSPVERSION)
		return false;

	for (int i = 0; i < HEADER_LUMPS; i++)
	{
		if (!this->FileLumps[i].InitData(this->FileData + hdr->lumps[i].fileofs, hdr->lumps[i].filelen, i, GetLumpSize(i)))
			return false;
	}

	InitTextures();
	InitEntities();
	FindWadFiles();
	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CBSPFile::InitTextures()
{
	char* miptex = 0;

	int len = this->FileLumps[Textures].GetData(&miptex);

	tMiptexlump* lmp = (tMiptexlump*)miptex;

	this->TextureCount = 0;
	this->AllocmiptexCount = lmp->nummiptex;
	this->FileTextures = new CWADMiptex[lmp->nummiptex];

	for (int i = 0; i < lmp->nummiptex; i++)
	{
		tMiptex* pMipTex = (tMiptex*)(miptex + lmp->dataofs[i]);

		int width = pMipTex->width;
		int height = pMipTex->height;

		int size = width * height;

		if (pMipTex->offsets[0] != 0)
		{
			int length;

			if (i == lmp->nummiptex-2)
				length = lmp->dataofs[i+1] - lmp->dataofs[i];
			else
				length = len - lmp->dataofs[i];

			this->FileTextures[this->TextureCount++].InitData(pMipTex->name, (char*)pMipTex, length);
		}
		else
		{
			this->FileTextures[this->TextureCount++].InitName(pMipTex->name);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CBSPFile::InitEntities()
{
	char* data = 0;

	this->FileLumps[Entities].GetData(&data);

	FileEntities.LoadMAPBuffer((char*)data, this->FilePath);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CBSPFile::FindWadFiles()
{
	CMAPEntity* ent = this->FileEntities.GetEntity(this->FileEntities.GetNextEntity("worldspawn", 0));

	this->FileWadfiles.Resize(0);

	if (ent != 0)
	{
		CMAPPropertie* prop = ent->GetPropertie("wad");
		if (prop != 0)
		{
			char* val = prop->GetValue();
			if (val != 0)
			{
				int start = 0;
				int length = 0;
				int vallen = (int)strlen(val);

				while (start + length < vallen)
				{
					if (val[start + length] == ';')
					{
						char* wad = new char[length];
						int i, j;

						for (i = start, j = 0; i < start + length; i++, j++)
						{
							wad[j] = val[i];
						}

						wad[j] = '\0';
						this->FileWadfiles.Add(wad);

						start += length + 1;
						length = 0;
					}
					else
						length++;
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CBSPFile::GetTextureName(int index)
{
	return this->FileTextures[index].GetName();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CBSPFile::GetNumTextures()
{
	return this->TextureCount;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CWADMiptex* CBSPFile::GetMiptex(int i)
{
	return &this->FileTextures[i];
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CBSPFile::WriteBMP(char* path, int index)
{
	bool res = false;

	if (index < this->TextureCount)
		res = this->FileTextures[index].WriteBMP(path);

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CBSPFile::WriteEntities(char* filename)
{
	bool res = false;

	res = FileEntities.SaveMAPFile(filename);

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CBSPFile::GetNumEntities()
{
	return this->FileEntities.GetNumEntities();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CMAPEntity* CBSPFile::GetEntity(int index)
{
	return this->FileEntities.GetEntity(index);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CBSPFile::GetNumWadfiles()
{
	return this->FileWadfiles.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CBSPFile::GetWadfilePath(int index)
{
	char* res = 0;

	if (index < (int)this->FileWadfiles.Length())
	{
		res = this->FileWadfiles[index];
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CBSPFile::GetLumpSize(int lump)
{
	switch (lump)
	{
	case Entities:
		{
			return 1;
		}
	case Planes:
		{
			return sizeof(tPlane);
		}
	case Textures:
		{
			return 1;
		}
	case Vertexes:
		{
			return sizeof(tVertex);
		}
	case Visibility:
		{
			return 1;
		}
	case Nodes:
		{
			return sizeof(tNode);
		}
	case Texinfo:
		{
			return sizeof(tTexinfo);
		}
	case Faces:
		{
			return sizeof(tFace);
		}
	case Lighting:
		{
			return 1;
		}
	case Clipnodes:
		{
			return sizeof(tClipnode);
		}
	case Leafs:
		{
			return sizeof(tLeaf);
		}
	case Marksurfaces:
		{
			return sizeof(short);
		}
	case Edges:
		{
			return sizeof(tEdge);
		}
	case Surfedges:
		{
			return sizeof(short);
		}
	case Models:
		{
			return sizeof(tModel);
		}
	}
	return 0;
}
