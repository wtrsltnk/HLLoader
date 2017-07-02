// RMFFace.h: interface for the CRMFFace class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFFACE_H
#define RMFFACE_H

#include "wiskunde.h"
#include "ArrayList.h"

#include "RMFObject.h"

class CRMFFace;
typedef CArrayList <CRMFFace*> FaceList;

class CRMFFace : public CRMFObject
{
public:
	friend class CRMFFile;
private:
	char FaceTexture[256];
	Vector FaceUAxis;
	float FaceXShift;
	Vector FaceVAxis;
	float FaceYShift;
	float FaceRotation;
	float FaceXScale;
	float FaceYScale;
	int FaceVertexCount;
	Vector* FaceVertices;
	Vector FacePlaneVertices[3];
	Plane FacePlane;

	bool InitVertices(int count);
public:
	CRMFFace();
	virtual ~CRMFFace();

	CRMFObject::ObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
