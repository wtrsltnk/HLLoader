// RMFKey.h: interface for the CRMFKey class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFKEY_H
#define RMFKEY_H

#include "../common/ArrayList.h"

class CRMFKey;
typedef CArrayList <CRMFKey*> KeyList;

class CRMFKey
{
private:
	char Key[32];
	char Value[100];
public:
	CRMFKey(char* key, char* value);
	virtual ~CRMFKey();

	char* GetKey();
	char* GetValue();
};

#endif
