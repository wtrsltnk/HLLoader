// RMFCorner.h: interface for the CRMFCorner class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFCORNER_H
#define RMFCORNER_H

#include "wiskunde.h"
#include "ArrayList.h"

#include "RMFKey.h"

class CRMFCorner;
typedef CArrayList <CRMFCorner*> CornerList;

class CRMFCorner  
{
public:
	friend class CRMFFile;
private:
	Vector CornerPosition;
	int CornerIndex;
	char CornerName[128];
	KeyList CornerKeys;

public:
	CRMFCorner();
	virtual ~CRMFCorner();

};

#endif
