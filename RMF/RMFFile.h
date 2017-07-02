// RMFFile.h: interface for the CRMFFile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFFILE_H
#define RMFFILE_H

#include "../common/BaseFile.h"
#include "../common/ByteIterator.h"
#include "RMFVisGroup.h"
#include "RMFSolid.h"
#include "RMFEntity.h"
#include "RMFGroup.h"
#include "RMFPath.h"

typedef CArrayList <char*> WadList;

class CRMFFile : public CBaseFile
{
private:
	SolidList FileSolids;
	EntityList FileEntities;
	GroupList FileGroups;
	PathList FilePaths;
	VisGroupList FileVisGroups;
	WadList RegWadFiles;

	CRMFEntity FileWorldspawn;

	bool ParseData();

	void GetNString(CByteIterator* I, char* str);
	void GetNString(CByteIterator* I, char* str, int max);
	void GetVisGroups(CByteIterator* I);
	void GetObjects(CByteIterator* I, SolidList* solids, GroupList* groups, EntityList* entities);
	void GetSolid(CByteIterator* I, CRMFSolid* solid);
	void GetGroup(CByteIterator* I, CRMFGroup* group);
	void GetEntity(CByteIterator* I, CRMFEntity* entity);
	void GetFaces(CByteIterator* I, FaceList* facelist);
	void GetVertex(CByteIterator* I, Vector* vertex);
	void GetKeys(CByteIterator* I, KeyList* keylist);
	void GetPaths(CByteIterator* I, PathList* pathlist);
	void GetCorners(CByteIterator* I, CornerList* cornerlist);
	void GetWadfiles(WadList* wadlist);
public:
	CRMFFile();
	virtual ~CRMFFile();

	bool LoadRMFFile(const char* filename) throw();
	void Clear();

	void DrawGl();

	int GetNumVisGroups();
	char* GetVisGroupName(int index);
	CRMFEntity* GetWorldSpawn();
};

#endif
