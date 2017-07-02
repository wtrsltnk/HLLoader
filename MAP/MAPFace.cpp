// MAPFace.cpp: implementation of the CMAPFace class.
//
//////////////////////////////////////////////////////////////////////

#include "MAPFace.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMAPFace::CMAPFace()
{
	strcpy(this->FaceTexture, "");
	memset(this->FaceCoord, 0, sizeof(this->FaceCoord));
	this->FaceRotation = 0.0f;
	this->FaceScaleX = 0.0f;
	this->FaceScaleY = 0.0f;
}

CMAPFace::~CMAPFace()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFace::ReadPlane(CMAPParser* mp)
{
	bool res = false;
	char* plane = mp->GetToken();

	int len = strlen(plane);
	char* data = new char[len + 1];

	if (data)
	{
		strncpy(data, plane, len);
		data[len] = '\0';

		res = ParsePlane(data, len);

		if (data)
		{
			delete [] data;
		}
	}
	
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFace::SavePlane(FILE* file)
{
	::fprintf(file, "( %1.0f %1.0f %1.0f ) ", this->FaceVerts[0].X, this->FaceVerts[0].Y, this->FaceVerts[0].Z);
	::fprintf(file, "( %1.0f %1.0f %1.0f ) ", this->FaceVerts[1].X, this->FaceVerts[1].Y, this->FaceVerts[1].Z);
	::fprintf(file, "( %1.0f %1.0f %1.0f ) ", this->FaceVerts[2].X, this->FaceVerts[2].Y, this->FaceVerts[2].Z);
	::fprintf(file, "%s ", this->FaceTexture);
	::fprintf(file, "[ %1.0f %1.0f %1.0f %1.0f ] ", this->FaceCoord[0][0], this->FaceCoord[0][1], this->FaceCoord[0][2], this->FaceCoord[0][3]);
	::fprintf(file, "[ %1.0f %1.0f %1.0f %1.0f ] ", this->FaceCoord[1][0], this->FaceCoord[1][1], this->FaceCoord[1][2], this->FaceCoord[1][3]);
	::fprintf(file, "%1.0f %1.0f %1.0f\n", this->FaceRotation, this->FaceScaleX, this->FaceScaleY);
	return true;
}


//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFace::ParsePlane(char* data, int len)
{
	bool res = true;
	int parse_index = 0;
	int vector_index = 0;
	int coord_index = 0;

	char tmp[256];

	if (data[0] == '(')
	{
		while ((parse_index < len) && (res == true))
		{
			switch (data[parse_index])
			{
			case '(':
				{
					if (vector_index > 2)
						res = false;
					
					parse_index++;

					int i = 0;
					while (parse_index < len && data[parse_index] != ')')
					{
						if (data[parse_index] < 48 || data[parse_index] > 57 )
							if (data[parse_index] != '-')
								if (data[parse_index] != ' ')
									if (data[parse_index] != 46)
										if (data[parse_index] != 'e')
											res = false;

						tmp[i] = data[parse_index];
						i++;
						parse_index++;
					}
					tmp[i] = '\0';

					if (!ParseVector(&this->FaceVerts[vector_index], tmp))
						res = false;

					if (vector_index == 2)
						this->FacePlane = Plane(this->FaceVerts[0], this->FaceVerts[1], this->FaceVerts[2]);

					vector_index++;
					break;
				}

			case '[':
				{
					if (coord_index > 1)
						res = false;

					parse_index++;

					int i = 0;
					while (parse_index < len && data[parse_index] != ']')
					{
						if (data[parse_index] < 48 || data[parse_index] > 57 )
							if (data[parse_index] != '-')
								if (data[parse_index] != ' ')
									if (data[parse_index] != 46)
										if (data[parse_index] != 'e')
											res = false;

						tmp[i] = data[parse_index];
						i++;
						parse_index++;
					}
					tmp[i] = '\0';

					if (!ParseCoord(this->FaceCoord[coord_index], tmp))
						res = false;

					coord_index++;
					break;
				}

			case ' ':
				{
					break;
				}

			case '\n':
			case '\t':
				{
					res = false;
				}

			default:
				{
					if (strcmp(this->FaceTexture, "") != 0)
					{
						int i = 0;
						while (parse_index < len)
						{
							tmp[i] = data[parse_index];
							i++;
							parse_index++;
						}
						tmp[i] = '\0';

						if (!ParseRotScale(tmp))
							res = false;
					}
					else
					{
						int i = 0;
						while ((parse_index < len) && (data[parse_index] != ' '))
						{
							this->FaceTexture[i] = data[parse_index];
							i++;
							parse_index++;
						}
						this->FaceTexture[i] = '\0';
					}
					break;
				}
			}
			parse_index++;
		}
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPFace::ParseVector(Vector* v, char* data)
{
	bool res = true;

	if (sscanf(data, "%f %f %f", &v->X, &v->Y, &v->Z) != 3)
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
bool CMAPFace::ParseCoord(float coord[], char* data)
{
	bool res = true;

	if (sscanf(data, "%f %f %f %f", &coord[0], &coord[1], &coord[2], &coord[3]) != 4)
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
bool CMAPFace::ParseRotScale(char* data)
{
	bool res = true;

	if (sscanf(data, "%f %f %f", &this->FaceRotation, &this->FaceScaleX, &this->FaceScaleY) != 3)
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
char* CMAPFace::GetTexture()
{
	return this->FaceTexture;
}