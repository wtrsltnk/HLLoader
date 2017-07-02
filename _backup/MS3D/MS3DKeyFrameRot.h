// MS3DKeyFrameRot.h: interface for the CMS3DKeyFrameRot class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MS3DKEYFRAMEROT_H
#define MS3DKEYFRAMEROT_H

#include "ArrayList.h"

class CMS3DKeyFrameRot;
typedef CArrayList <CMS3DKeyFrameRot*> MS3DKeyFrameRotList;

class CMS3DKeyFrameRot  
{
public:
	friend class CMS3DFile;
private:
    float RotTime;
    float RotRotation[3];
public:
	CMS3DKeyFrameRot();
	virtual ~CMS3DKeyFrameRot();

};

#endif
