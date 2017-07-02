// RMFPath.h: interface for the CRMFPath class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFPATH_H
#define RMFPATH_H

#include "ArrayList.h"

#include "RMFObject.h"
#include "RMFCorner.h"

class CRMFPath;
typedef CArrayList <CRMFPath*> PathList;

class CRMFPath : public CRMFObject
{
public:
	friend class CRMFFile;
private:
	char PathName[128];
	char PathClass[128];
	int PathType;

	CornerList PathCorners;
public:
	CRMFPath();
	virtual ~CRMFPath();

	CRMFObject::ObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
