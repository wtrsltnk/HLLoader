// RMFFace.cpp: implementation of the CRMFFace class.
//
//////////////////////////////////////////////////////////////////////

#include "RMFFace.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRMFFace::CRMFFace()
{
	this->FaceXShift = 0.0f;
	this->FaceYShift = 0.0f;
	this->FaceRotation = 0.0f;
	this->FaceXScale = 0.0f;
	this->FaceYScale = 0.0f;
	this->FaceVertices = 0;
	this->FaceVertexCount = 0;
}

CRMFFace::~CRMFFace()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFace::Clear()
{
	if (this->FaceVertices)
	{
		delete [] this->FaceVertices;
		this->FaceVertexCount = 0;
		this->FaceVertices = 0;
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CRMFFace::InitVertices(int count)
{
	bool res = false;

	if (this->FaceVertices)
	{
		delete [] this->FaceVertices;
		this->FaceVertexCount = 0;
	}

	this->FaceVertices = new Vector[count];

	if (this->FaceVertices)
	{
		this->FaceVertexCount = count;
		res = true;
	}

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CRMFObject::ObjectType CRMFFace::GetType()
{
	return CRMFObject::Face;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFace::DrawGl()
{
	bool drawwire = false;

	glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);

	glNormal3f(		this->FacePlane.GetNormal().X,
					this->FacePlane.GetNormal().Y,
					this->FacePlane.GetNormal().Z);
	{
		for (int i = this->FaceVertexCount-1; i > -1; i--)
		{
			glVertex3f(		this->FaceVertices[i].X,
							this->FaceVertices[i].Y,
							this->FaceVertices[i].Z);
		}
	}

	glEnd();

	if (drawwire)
	{
		glColor3f(0.0f, 0.0f, 0.0f);
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

		glBegin(GL_POLYGON);

		glNormal3f(		this->FacePlane.GetNormal().X,
						this->FacePlane.GetNormal().Y,
						this->FacePlane.GetNormal().Z);
		{
			for (int j = this->FaceVertexCount-1; j > -1; j--)
			{
				glVertex3f(		this->FaceVertices[j].X,
								this->FaceVertices[j].Y,
								this->FaceVertices[j].Z);
			}
		}

		glEnd();
	}
}
