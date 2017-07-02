// RMFVisGroup.h: interface for the CRMFVisGroup class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFVISGROUP_H
#define RMFVISGROUP_H

#include "wiskunde.h"
#include "ArrayList.h"

class CRMFVisGroup;
typedef CArrayList <CRMFVisGroup*> VisGroupList;

class CRMFVisGroup  
{
public:
	friend class CRMFFile;
private:
	char VisgroupName[128];
	Color VisgroupColor;
	int VisgroupIndex;
	bool VisgroupVisible;

public:
	CRMFVisGroup();
	virtual ~CRMFVisGroup();

};

#endif
