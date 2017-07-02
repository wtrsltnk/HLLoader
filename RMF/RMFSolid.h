// RMFSolid.h: interface for the CRMFSolid class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFSOLID_H
#define RMFSOLID_H

#include "wiskunde.h"
#include "ArrayList.h"

#include "RMFObject.h"
#include "RMFFace.h"

class CRMFSolid;
typedef CArrayList <CRMFSolid*> SolidList;

class CRMFSolid : public CRMFObject
{
public:
	friend class CRMFFile;
private:
	int SolidVisgroup;
	Color SolidColor;

	FaceList SolidFaces;
public:
	CRMFSolid();
	virtual ~CRMFSolid();

	CRMFObject::ObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
