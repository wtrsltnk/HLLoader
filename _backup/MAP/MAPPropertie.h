// MAPPropertie.h: interface for the CMAPPropertie class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MAPPROPERTIE_H
#define MAPPROPERTIE_H

#define MAX_VALUE_LENGTH 256

class CMAPPropertie  
{
	char PropName[64];
	char PropValue[MAX_VALUE_LENGTH];
public:
	CMAPPropertie(char* name);
	virtual ~CMAPPropertie();

	char* GetName();

	void SetValue(char* value);
	char* GetValue();
};

#endif
