// MAPBrush.cpp: implementation of the CMAPBrush class.
//
//////////////////////////////////////////////////////////////////////

#include "MAPBrush.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMAPBrush::CMAPBrush(int index)
{
	this->BrushIndex = index;
}

CMAPBrush::~CMAPBrush()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMAPBrush::Clear()
{
	for (int i = 0; i < (int)this->BrushFaces.Length(); i++)
	{
		CMAPFace* face = this->BrushFaces[i];

		delete face;
	}

	this->BrushFaces.Resize(0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPBrush::ReadBrush(CMAPParser* mp)
{
	bool res = true;

	if (mp->GoToNextToken())
	{
		while ((mp->GoToNextToken()) && (mp->GetType() != eEndBracket) && (res == true))
		{
			switch (mp->GetType())
			{
			case ePlane:
				{
					CMAPFace* face = new CMAPFace();

					if (face && face->ReadPlane(mp))
						this->BrushFaces.Add(face);
					else
						res = false;

					break;
				}

			case eComment:
				{
					break;
				}
			}
		}
	}
	else
	{
		res = false;
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPBrush::SaveBrush(FILE* file)
{
	::fwrite("{\n", sizeof(char), 2, file);
	for (int i = 0; i < (int)this->BrushFaces.Length(); i++)
	{
		this->BrushFaces[i]->SavePlane(file);
	}
	::fwrite("}\n", sizeof(char), 2, file);

	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CMAPBrush::GetNumFaces()
{
	return (int)this->BrushFaces.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CMAPFace* CMAPBrush::GetFace(int index)
{
	CMAPFace* res = 0;

	if (index < (int)this->BrushFaces.Length())
		res = this->BrushFaces[index];

	return res;
}