// MS3DGroup.h: interface for the CMS3DGroup class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MS3DGROUP_H
#define MS3DGROUP_H

typedef unsigned char byte;
typedef unsigned short word;

#include "ArrayList.h"
#include "MS3DObject.h"

class CMS3DGroup;
typedef CArrayList <CMS3DGroup*> MS3DGroupList;
typedef CArrayList <word> IndexList;

class CMS3DGroup : public CMS3DObject
{
public:
	friend class CMS3DFile;
private:
    byte GroupFlags;
    char GroupName[32];
	IndexList GroupTriangleIndices;
    char GroupMaterialIndex;
public:
	CMS3DGroup();
	virtual ~CMS3DGroup();

	MS3DObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
