// MAPFace.h: interface for the CMAPFace class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MAPFACE_H
#define MAPFACE_H

#include "MAPParser.h"

#include "../common/wiskunde.h"

class CMAPFace  
{
	Vector FaceVerts[3];
	Plane FacePlane;

	char FaceTexture[64];
	float FaceCoord[2][4];
	float FaceRotation, FaceScaleX, FaceScaleY;

	bool ParsePlane(char* data, int len);
	bool ParseVector(Vector* v, char* data);
	bool ParseCoord(float coord[], char* data);
	bool ParseRotScale(char* data);
public:
	CMAPFace();
	virtual ~CMAPFace();

	bool ReadPlane(CMAPParser* mp);
	bool SavePlane(FILE* file);

	char* GetTexture();
};

#endif
