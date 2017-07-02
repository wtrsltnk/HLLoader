// RMFEntity.h: interface for the CRMFEntity class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFENTITY_H
#define RMFENTITY_H

#include "wiskunde.h"
#include "ArrayList.h"

#include "RMFObject.h"
#include "RMFSolid.h"
#include "RMFKey.h"

class CRMFEntity;
typedef CArrayList <CRMFEntity*> EntityList;

class CRMFEntity : public CRMFObject
{
public:
	friend class CRMFFile;
private:
	int EntityVisgroup;
	Color EntityColor;
	char EntityClassname[128];
	int EntityFlags;
	Vector EntityPosition;

	KeyList EntiyKeys;
	SolidList EntitySolids;
public:
	CRMFEntity();
	virtual ~CRMFEntity();

	CRMFObject::ObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
