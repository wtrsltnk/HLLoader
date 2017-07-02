// MAPEntity.cpp: implementation of the CMAPEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "MAPEntity.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////

int CMAPEntity::StaticEntCount = 0;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMAPEntity::CMAPEntity()
{
	this->EntIndex = StaticEntCount++;
	sprintf(this->EntName, "Entitie %i", this->EntIndex);
}

CMAPEntity::~CMAPEntity()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMAPEntity::Clear()
{
	for (int i = 0; i < (int)this->EntBrushes.Length(); i++)
	{
		CMAPBrush* brush = this->EntBrushes[i];

		delete brush;
	}

	for (int j = 0; j < (int)this->EntProperties.Length(); j++)
	{
		CMAPPropertie* prop = this->EntProperties[j];

		delete prop;
	}

	this->EntBrushes.Resize(0);
	this->EntProperties.Resize(0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CMAPEntity::ToString()
{
	return this->EntName;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPEntity::ReadEntity(CMAPParser* mp)
{
	bool res = true;
	int i = 0;

	while ((mp->GoToNextToken()) && (mp->GetType() != eEndBracket) && (res == true))
	{
		switch (mp->GetType())
		{
		case eString:
			{
				if (!ReadProperties(mp))
					res = false;
				break;
			}

		case eComment:
			{
				continue;
			}

		case eStartBracket:
			{
				CMAPBrush* newBr = new CMAPBrush(i++);

				if (newBr && newBr->ReadBrush(mp))
					this->EntBrushes.Add(newBr);
				else
					res = false;
				break;
			}

		default:
			{
				res = false;
			}

		}
	}

	CMAPPropertie* prop = this->GetPropertie("classname");
	if (prop != 0)
	{
		sprintf(this->EntName, "%s %i", prop->GetValue(), this->EntIndex);
	}
	
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPEntity::SaveEntity(FILE* file)
{
	bool res = true;

	::fwrite("{\n", sizeof(char), 2, file);
	
	SaveProperties(file);
	SaveBrushes(file);

	::fwrite("}\n", sizeof(char), 2, file);

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPEntity::ReadProperties(CMAPParser* mp)
{
	bool res = false;

	CMAPPropertie* prop = new CMAPPropertie(mp->GetToken());

	if (prop != 0)
	{
		if (mp->GoToNextToken())
		{
			prop->SetValue(mp->GetToken());
			this->EntProperties.Add(prop);
			res = true;
		}
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPEntity::SaveProperties(FILE* file)
{
	for (int i = (int)this->EntProperties.Length()-1; i >= 0; i--)
	{
		::fprintf(file, "\"%s\" \"%s\"\n", this->EntProperties[i]->GetName(), this->EntProperties[i]->GetValue());
	}
	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPEntity::SaveBrushes(FILE* file)
{
	bool res = true;

	for (int i = 0; i < (int)this->EntBrushes.Length(); i++)
	{
		if (!this->EntBrushes[i]->SaveBrush(file))
		{
			res = false;
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
int CMAPEntity::GetNumBrushes()
{
	return this->EntBrushes.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CMAPBrush* CMAPEntity::GetBrush(int index)
{
	CMAPBrush* res = 0;

	if (index < (int)this->EntBrushes.Length())
	{
		res = this->EntBrushes[index];
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CMAPEntity::GetClassname()
{
	return GetPropertie("classname")->GetValue();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CMAPEntity::GetNumProperties()
{
	return this->EntProperties.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CMAPPropertie* CMAPEntity::GetPropertie(int index)
{
	CMAPPropertie* res = 0;

	if (index < (int)this->EntProperties.Length())
	{
		res = this->EntProperties[index];
	}
	
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CMAPPropertie* CMAPEntity::GetPropertie(char* name)
{
	CMAPPropertie* res = 0;

	for (int i = 0; i < (int)this->EntProperties.Length(); i++)
	{
		if (strcmp(this->EntProperties[i]->GetName(), name) == 0)
		{
			res = this->EntProperties[i];
			break;
		}
	}
	return res;
}