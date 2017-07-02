// MS3DTriangle.h: interface for the CMS3DTriangle class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MS3DTRIANGLE_H
#define MS3DTRIANGLE_H

typedef unsigned char byte;
typedef unsigned short word;

#include "ArrayList.h"
#include "MS3DObject.h"

class CMS3DTriangle;
typedef CArrayList <CMS3DTriangle*> MS3DTriangleList;

class CMS3DTriangle : public CMS3DObject
{
public:
	friend class CMS3DFile;
private:
	word TriangleFlags;
    word TriangleVertexIndices[3];
    float TriangleVertexNormals[3][3];
    float TriangleS[3];
    float TriangleT[3];
    byte TriangleSmoothingGroup;
    byte TriangleGroupIndex;
public:
	CMS3DTriangle();
	virtual ~CMS3DTriangle();

	MS3DObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
