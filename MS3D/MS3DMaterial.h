// MS3DMaterial.h: interface for the CMS3DMaterial class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MS3DMATERIAL_H
#define MS3DMATERIAL_H

#include "../common/ArrayList.h"
#include "MS3DObject.h"

class CMS3DMaterial;
typedef CArrayList <CMS3DMaterial*> MS3DMaterialList;

class CMS3DMaterial : public CMS3DObject
{
public:
	friend class CMS3DFile;
private:
    char MaterialName[32];
    float MaterialAmbient[4];
    float MaterialDiffuse[4];
    float MaterialSpecular[4];
    float MaterialEmissive[4];
    float MaterialShininess;
    float MaterialTransparency;
    char MaterialMode;
    char MaterialTexture[128];
    char MaterialAlphamap[128];
public:
	CMS3DMaterial();
	virtual ~CMS3DMaterial();

	MS3DObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
