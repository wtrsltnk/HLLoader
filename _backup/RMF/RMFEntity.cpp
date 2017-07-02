// RMFGroup.cpp: implementation of the CRMFEntity class.
//
//////////////////////////////////////////////////////////////////////

#include "RMFEntity.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRMFEntity::CRMFEntity()
{
}

CRMFEntity::~CRMFEntity()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFEntity::Clear()
{
	int i = 0;

	for (i = 0; i < (int)this->EntiyKeys.Length(); i++)
	{
		CRMFKey* key= this->EntiyKeys[i];

		delete key;
	}

	for (i = 0; i < (int)this->EntitySolids.Length(); i++)
	{
		CRMFSolid* solid= this->EntitySolids[i];

		delete solid;
	}

	this->EntiyKeys.Resize(0);
	this->EntitySolids.Resize(0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CRMFObject::ObjectType CRMFEntity::GetType()
{
	return CRMFObject::Entity;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFEntity::DrawGl()
{
	float color[4] = {0};
	this->EntityColor.Get(color);
	glColor3fv(color);

	if ((int)this->EntitySolids.Length())
	{
		for (int i = 0; i < (int)this->EntitySolids.Length(); i++)
		{
			this->EntitySolids[i]->DrawGl();
		}
	}
	else
	{
		float m_fWidth = 50.0f;
		float m_fHeight = 50.0f;
		float m_fDepth = 50.0f;

		glPushMatrix();
		{
			glTranslatef(this->EntityPosition.X, this->EntityPosition.Y, this->EntityPosition.Z);

			glBegin(GL_QUADS);
			{
				glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  m_fDepth);			// Point 1 (Front)
				glTexCoord2f(1.0f, 0.0f); glVertex3f( m_fWidth,  0.0f,  m_fDepth);		// Point 2 (Front)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( m_fWidth,  m_fHeight,  m_fDepth);	// Point 3 (Front)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  m_fHeight,  m_fDepth);		// Point 4 (Front)
				// Back Face
				glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  0.0f);				// Point 1 (Back)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  m_fHeight,  0.0f);			// Point 2 (Back)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( m_fWidth,  m_fHeight,  0.0f);		// Point 3 (Back)
				glTexCoord2f(0.0f, 0.0f); glVertex3f( m_fWidth,  0.0f,  0.0f);			// Point 4 (Back)
				// Top Face
				glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  m_fHeight,  0.0f);			// Point 1 (Top)
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  m_fHeight,  m_fDepth);		// Point 2 (Top)
				glTexCoord2f(1.0f, 0.0f); glVertex3f( m_fWidth,  m_fHeight,  m_fDepth);	// Point 3 (Top)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( m_fWidth,  m_fHeight,  0.0f);		// Point 4 (Top)
				// Bottom Face
				glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  0.0f);				// Point 1 (Bottom)
				glTexCoord2f(1.0f, 0.0f); glVertex3f( m_fWidth,  0.0f,  0.0f);			// Point 2 (Bottom)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( m_fWidth,  0.0f,  m_fDepth);		// Point 3 (Bottom)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  0.0f,  m_fDepth);			// Point 4 (Bottom)
				// Right face
				glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
				glTexCoord2f(1.0f, 0.0f); glVertex3f( m_fWidth,  0.0f,  0.0f);			// Point 1 (Right)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( m_fWidth,  m_fHeight,  0.0f);		// Point 2 (Right)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( m_fWidth,  m_fHeight,  m_fDepth);	// Point 3 (Right)
				glTexCoord2f(0.0f, 0.0f); glVertex3f( m_fWidth,  0.0f,  m_fDepth);		// Point 4 (Right)
				// Left Face
				glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
				glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  0.0f);				// Point 1 (Left)
				glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0f,  0.0f,  m_fDepth);			// Point 2 (Left)
				glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f,  m_fHeight,  m_fDepth);		// Point 3 (Left)
				glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f,  m_fHeight,  0.0f);			// Point 4 (Left)
			}
			glEnd();
		}
		glPopMatrix();
	}
}
