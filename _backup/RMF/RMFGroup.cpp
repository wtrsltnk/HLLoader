// RMFGroup.cpp: implementation of the CRMFGroup class.
//
//////////////////////////////////////////////////////////////////////

#include "RMFGroup.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRMFGroup::CRMFGroup()
{
}

CRMFGroup::~CRMFGroup()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFGroup::Clear()
{
	int i = 0;

	for (i = 0; i < (int)this->GroupSolids.Length(); i++)
	{
		CRMFSolid* solid = this->GroupSolids[i];

		delete solid;
	}

	for (i = 0; i < (int)this->GroupEntities.Length(); i++)
	{
		CRMFEntity* entity = this->GroupEntities[i];

		delete entity;
	}

	for (i = 0; i < (int)this->GroupGroups.Length(); i++)
	{
		CRMFGroup* group = this->GroupGroups[i];

		delete group;
	}

	this->GroupSolids.Resize(0);
	this->GroupEntities.Resize(0);
	this->GroupGroups.Resize(0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CRMFObject::ObjectType CRMFGroup::GetType()
{
	return CRMFObject::Group;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFGroup::DrawGl()
{
	int i = 0;
	float color[4] = {0};
	this->GroupColor.Get(color);
	glColor3fv(color);

	for (i = 0; i < (int)this->GroupSolids.Length(); i++)
	{
		this->GroupSolids[i]->DrawGl();
	}

	for (i = 0; i < (int)this->GroupGroups.Length(); i++)
	{
		this->GroupGroups[i]->DrawGl();
	}

	for (i = 0; i < (int)this->GroupEntities.Length(); i++)
	{
		this->GroupEntities[i]->DrawGl();
	}
}
