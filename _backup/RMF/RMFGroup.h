// RMFGroup.h: interface for the CRMFGroup class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFGROUP_H
#define RMFGROUP_H

#include "wiskunde.h"
#include "ArrayList.h"

#include "RMFSolid.h"
#include "RMFEntity.h"

class CRMFGroup;
typedef CArrayList <CRMFGroup*> GroupList;

class CRMFGroup : public CRMFObject
{
public:
	friend class CRMFFile;
private:
	int GroupVisgroup;
	Color GroupColor;

	SolidList GroupSolids;
	EntityList GroupEntities;
	GroupList GroupGroups;
public:
	CRMFGroup();
	virtual ~CRMFGroup();

	CRMFObject::ObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
