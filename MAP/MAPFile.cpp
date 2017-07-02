// MAPFile.cpp: implementation of the CMAPFile class.
//
//////////////////////////////////////////////////////////////////////

#include "MAPFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMAPFile::CMAPFile()
{
	memset(this->FilePath, 0, sizeof(this->FilePath));
}

CMAPFile::~CMAPFile()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMAPFile::Clear()
{
	for (int i = 0; i < (int)this->FileEntities.Length(); i++)
	{
		CMAPEntity* ent = this->FileEntities[i];

		delete ent;
	}

    for (int i = 0; i < (int)this->FileTextures.Length(); i++)
	{
		CWADMiptex* miptex = this->FileTextures[i];

		delete miptex;
	}

	this->FileEntities.Resize(0);
	this->FileWadfiles.Resize(0);
	this->FileTextures.Resize(0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFile::LoadMAPFile(const char* filename) throw()
{
	bool res = true;
	CMAPParser mp;

	try
	{
		CBaseFile::LoadFile(filename);
	}
	catch(char* err)
	{
		res = false;
		throw(err);
	}

	mp.SetMAPBuffer((char*)this->FileData);
	if (!ParseEntites(&mp))
		throw("Can\'t parse the data from the file");

	FindWadFiles();
	FindTextures();

	CBaseFile::Clear();

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFile::LoadMAPBuffer(char* buffer, const char* name) throw()
{
	bool res = true;
	CMAPParser mp;

	if (name != 0)
	{
		if (buffer != 0)
		{
			strncpy(this->FilePath, name, 256);
			
			if (strcmp(this->FilePath, "") != 0)
			{
				if (mp.SetMAPBuffer(buffer))
				{
					try
					{
						ParseEntites(&mp);
					}
					catch(char* err)
					{
						throw(err);
					}
				}
				else
					throw("Can\'t setup MAP parser");
			}
			else
				throw("No valid Filename");
		}
		else
			throw("Buffer is empty");
	}
	else
		throw("No valid Name");

	FindWadFiles();
	FindTextures();

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFile::ParseEntites(CMAPParser* mp)
{
	bool res = true;

	do
	{
		switch (mp->GetType())
		{
		case eNull:
			{
				continue;
			}

		case eComment:
			{
				continue;
			}

		case eStartBracket:
			{
				CMAPEntity* newEnt = new CMAPEntity();
				
				if (newEnt)
				{
					if (!newEnt->ReadEntity(mp))
						throw("Can\'t read entity");

					this->FileEntities.Add(newEnt);
				}
				else
				{
					throw("Can\'t create new entity");
				}
				break;
			}

		default:
			{
				throw("Error with reading entity");
			}
		}
	} while ((mp->GoToNextToken()) && (mp->GetType() != eEnd) && (res == true));

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFile::SaveMAPFile(const char* filename) throw()
{
	FILE* file;
	bool res = false;

	if (filename != 0)
	{
		if (strcmp(filename, "") != 0)
		{
			if (file = ::fopen(filename, "wt"))
			{
				try
				{
					res = SaveEntities(file);
					::fclose(file);
				}
				catch (char* err)
				{
					::fclose(file);
					throw(err);
				}
			}
			else
				throw("Can\'t open file");
		}
		else
			throw("No valid Filename");
	}
	else
		throw("No valid Filename");

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFile::SaveMAPFile(FILE* file) throw()
{
	bool res = false;

	if (file)
	{
		try
		{
			res = SaveEntities(file);
		}
		catch (char* err)
		{
			throw(err);
		}
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFile::SaveEntities(FILE* file) throw()
{
	bool res = true;

	for (int i = 0; i < (int)this->FileEntities.Length(); i++)
	{
		if (!this->FileEntities[i]->SaveEntity(file))
		{
			char err[64] = {0};
			sprintf(err, "Can\'t save entity #%i", i);
			throw(err);
		}
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMAPFile::FindWadFiles()
{
	this->FileWadfiles.Resize(0);

	CMAPEntity* ent = GetEntity(GetNextEntity("worldspawn", 0));
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
						char* res = GetWadfile(val, start, length);
						this->FileWadfiles.Add(res);

						start += length + 1;
						length = 0;
					}
					else
						length++;
				}
				char* res = GetWadfile(val, start, length);
				this->FileWadfiles.Add(res);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CMAPFile::GetWadfile(char* val, int start, int length)
{
	char* res = new char[length];

	if (res != 0)
	{
		int i, j;

		for (i = start, j = 0; i < start + length; i++, j++)
		{
			res[j] = val[i];
		}

		res[j] = '\0';
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMAPFile::FindTextures()
{
	for (int i = 0; i < GetNumEntities(); i++)
	{
		CMAPEntity* ent = GetEntity(i);

		for (int j = 0; j < ent->GetNumBrushes(); j++)
		{
			CMAPBrush* brush = ent->GetBrush(j);

			for (int k = 0; k < brush->GetNumFaces(); k++)
			{
				CMAPFace* face = brush->GetFace(k);

				char* tex = face->GetTexture();
				bool isin = false;

				for (int l = 0; l < (int)this->FileTextures.Length(); l++)
				{
					if (strcmp(this->FileTextures[l]->GetName(), tex) == 0)
					{
						isin = true;
						break;
					}
				}

				if (!isin)
				{
					this->FileTextures.Add(new CWADMiptex(tex));
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
int CMAPFile::GetNumEntities()
{
	return this->FileEntities.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CMAPFile::GetNextEntity(char* classname, int current)
{
	int res = 0;

	for (int i = current; i < (int)this->FileEntities.Length(); i++)
	{
		if (strcmp(this->FileEntities[i]->GetClassname(), classname) == 0)
		{
			res = i;
			break;
		}
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CMAPEntity* CMAPFile::GetEntity(int index)
{
	CMAPEntity* res = 0;

	if (index < (int)this->FileEntities.Length())
	{
		res = this->FileEntities[index];
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CMAPFile::GetNumWadfiles()
{
	return this->FileWadfiles.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CMAPFile::GetWadfilePath(int index)
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
int CMAPFile::GetNumTextures()
{
	return this->FileTextures.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CMAPFile::GetTexture(int index)
{
	char* res = 0;

	if (index < (int)this->FileTextures.Length())
	{
		res = this->FileTextures[index]->GetName();
	}

	return res;
}
