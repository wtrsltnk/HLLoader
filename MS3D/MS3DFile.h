// MS3DFile.h: interface for the CMS3DFile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MS3DFILE_H
#define MS3DFILE_H

#include "../common/BaseFile.h"
#include "../common/ByteIterator.h"
//#include "common/ByteContainer.h"
#include "MS3DJoint.h"
#include "MS3DMaterial.h"
#include "MS3DGroup.h"
#include "MS3DTriangle.h"
#include "MS3DVertex.h"

#define MAX_VERTICES    65534
#define MAX_TRIANGLES   65534
#define MAX_GROUPS      255
#define MAX_MATERIALS   128
#define MAX_JOINTS      128
#define MAX_KEYFRAMES   216

class CMS3DFile : public CBaseFile
{
private:
	MS3DVertexList FileVertices;
	MS3DTriangleList FileTriangles;
	MS3DGroupList FileGroups;
	MS3DMaterialList FileMaterials;
	MS3DJointList FileJoints;

	char FileID[10];
	int FileVersion;
	float FileAnimationFPS;
	float FileCurrentTime;
	int FileTotalFrames;

	bool ParseData();
//	bool PrepareFile();

	void GetVertices(CByteIterator* I, MS3DVertexList* vertices);
	void GetTriangles(CByteIterator* I, MS3DTriangleList* triangles);
	void GetIndices(CByteIterator* I, IndexList* indices);
	void GetGroups(CByteIterator* I, MS3DGroupList* groups);
	void GetMaterials(CByteIterator* I, MS3DMaterialList* materials);
	void GetJoints(CByteIterator* I, MS3DJointList* joints);
	void GetKeyFrameRot(CByteIterator* I, MS3DKeyFrameRotList* keyframerot, int rotcount);
	void GetKeyFramePos(CByteIterator* I, MS3DKeyFramePosList* keyframepos, int poscount);
/*
	void PutVertices(CByteContainer* C, MS3DVertexList* vertices);
	void PutTriangles(CByteContainer* C, MS3DTriangleList* triangles);
	void PutIndices(CByteContainer* C, IndexList* indices);
	void PutGroups(CByteContainer* C, MS3DGroupList* groups);
	void PutMaterials(CByteContainer* C, MS3DMaterialList* materials);
	void PutJoints(CByteContainer* C, MS3DJointList* joints);
	void PutKeyFrameRot(CByteContainer* C, MS3DKeyFrameRotList* keyframerot);
	void PutKeyFramePos(CByteContainer* C, MS3DKeyFramePosList* keyframepos);
*/
public:
	CMS3DFile();
	virtual ~CMS3DFile();

	bool LoadMS3DFile(const char* filename) throw();
//	bool SaveMS3DFile(const char* filename) throw();
	void Clear();
	void DrawGl();

	int GetNumGroups();
	char* GetGroup(int index);

	int GetNumMaterials();
	char* GetMaterial(int index);
};

#endif
