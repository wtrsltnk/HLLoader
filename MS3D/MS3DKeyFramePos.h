// MS3DKeyFramePos.h: interface for the CMS3DKeyFramePos class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MS3DKEYFRAMEPOS_H
#define MS3DKEYFRAMEPOS_H

#include "../common/ArrayList.h"

class CMS3DKeyFramePos;
typedef CArrayList <CMS3DKeyFramePos*> MS3DKeyFramePosList;

class CMS3DKeyFramePos  
{
public:
	friend class CMS3DFile;
private:
    float PosTime;
    float PosPosition[3];
public:
	CMS3DKeyFramePos();
	virtual ~CMS3DKeyFramePos();

};

#endif
