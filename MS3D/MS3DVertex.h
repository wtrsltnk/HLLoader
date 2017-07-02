// MS3DVertex.h: interface for the CMS3DVertex class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MS3DVERTEX_H
#define MS3DVERTEX_H

typedef unsigned char byte;

#include "ArrayList.h"
#include "MS3DObject.h"

class CMS3DVertex;
typedef CArrayList <CMS3DVertex*> MS3DVertexList;

class CMS3DVertex : public CMS3DObject
{
public:
	friend class CMS3DFile;
private:
    byte VertexFlags;
    float VertexVertex[3];
    char VertexBoneId;
    byte VertexReferenceCount;
public:
	CMS3DVertex();
	virtual ~CMS3DVertex();

	MS3DObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
