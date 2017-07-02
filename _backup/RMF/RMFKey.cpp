// RMFKey.cpp: implementation of the CRMFKey class.
//
//////////////////////////////////////////////////////////////////////

#include "RMFKey.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRMFKey::CRMFKey(char* key, char* value)
{
	strncpy(this->Key, key, 32);
	strncpy(this->Value, value, 100);
}

CRMFKey::~CRMFKey()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CRMFKey::GetKey()
{
	return this->Key;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CRMFKey::GetValue()
{
	return this->Value;
}