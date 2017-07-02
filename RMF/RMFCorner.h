// RMFCorner.h: interface for the CRMFCorner class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFCORNER_H
#define RMFCORNER_H

#include "../common/wiskunde.h"
#include "../common/ArrayList.h"

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
