// MS3DJoint.h: interface for the CMS3DJoint class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MS3DJOINT_H
#define MS3DJOINT_H

typedef unsigned char byte;
typedef unsigned short word;

#include "MS3DObject.h"
#include "MS3DKeyFramePos.h"
#include "MS3DKeyFrameRot.h"
#include "../common/ArrayList.h"

class CMS3DJoint;
typedef CArrayList <CMS3DJoint*> MS3DJointList;

class CMS3DJoint : public CMS3DObject
{
public:
	friend class CMS3DFile;
private:
    byte JointFlags;
    char JointName[32];
    char JointParentName[32];
    float JointRotation[3];
    float JointPosition[3];

	MS3DKeyFramePosList KeyFramePos;
	MS3DKeyFrameRotList KeyFrameRot;
public:
	CMS3DJoint();
	virtual ~CMS3DJoint();

	MS3DObjectType GetType();
	void Clear();
	void DrawGl();
};

#endif
