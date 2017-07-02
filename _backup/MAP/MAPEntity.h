// MAPEntity.h: interface for the CMAPEntity class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MAPENTITY_H
#define MAPENTITY_H

#include "MAPParser.h"
#include "MAPBrush.h"
#include "MAPPropertie.h"

#include "ArrayList.h"

class CMAPEntity  
{
private:
	typedef CArrayList <CMAPBrush*> BrushList;
	BrushList EntBrushes;

	typedef CArrayList <CMAPPropertie*> PropertieList;
	PropertieList EntProperties;
	
	int EntIndex;
	char EntName[64];
	static int StaticEntCount;

	bool ReadProperties(CMAPParser* mp);
	bool SaveProperties(FILE* file);
	bool SaveBrushes(FILE* file);
public:
	CMAPEntity();
	virtual ~CMAPEntity();

	void Clear();

	bool ReadEntity(CMAPParser* mp);
	bool SaveEntity(FILE* file);

	int GetNumBrushes();
	CMAPBrush* GetBrush(int index);

	char* GetClassname();

	int GetNumProperties();
	CMAPPropertie* GetPropertie(int index);
	CMAPPropertie* GetPropertie(char* name);

	char* ToString();
};

#endif