// MAPBrush.h: interface for the CMAPBrush class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MAPBRUSH_H
#define MAPBRUSH_H

#include "MAPParser.h"
#include "MAPFace.h"

#include "ArrayList.h"

class CMAPBrush  
{
private:
	typedef CArrayList <CMAPFace*> FaceList;
	FaceList BrushFaces;

	int BrushIndex;
public:
	CMAPBrush(int index);
	virtual ~CMAPBrush();

	void Clear();

	bool ReadBrush(CMAPParser* mp);
	bool SaveBrush(FILE* file);

	int GetNumFaces();
	CMAPFace* GetFace(int index);
};

#endif
