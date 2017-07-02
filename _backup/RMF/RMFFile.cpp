// RMFFile.cpp: implementation of the CRMFFile class.
//
//////////////////////////////////////////////////////////////////////

#include "RMFFile.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRMFFile::CRMFFile()
{
}

CRMFFile::~CRMFFile()
{
	Clear();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
void CRMFFile::Clear()
{
	int i;

	for (i = 0; i < (int)this->FileSolids.Length(); i++)
	{
		CRMFSolid* solid = this->FileSolids[i];

		delete solid;
	}

	for (i = 0; i < (int)this->FileEntities.Length(); i++)
	{
		CRMFEntity* entity = this->FileEntities[i];

		delete entity;
	}

	for (i = 0; i < (int)this->FileGroups.Length(); i++)
	{
		CRMFGroup* group = this->FileGroups[i];

		delete group;
	}

	for (i = 0; i < (int)this->FilePaths.Length(); i++)
	{
		CRMFPath* path = this->FilePaths[i];

		delete path;
	}

	for (i = 0; i < (int)this->FileVisGroups.Length(); i++)
	{
		CRMFVisGroup* visgroup = this->FileVisGroups[i];

		delete visgroup;
	}

	this->FileSolids.Resize(0);
	this->FileEntities.Resize(0);
	this->FileGroups.Resize(0);
	this->FilePaths.Resize(0);
	this->FileVisGroups.Resize(0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CRMFFile::LoadRMFFile(const char* filename) throw()
{
	bool res = true;

	try
	{
		CBaseFile::LoadFile(filename);
	}
	catch(char* err)
	{
		res = false;
		throw(err);
	}

	if (!ParseData())
		throw("Can\'t parse the data from the file");

	CBaseFile::Clear();

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CRMFFile::ParseData()
{
	bool res = true;
	char mapworld[256];
	char worldspawn[256];
	CByteIterator I(this->FileData, this->FileLength);
	char* tmp = this->FileData;
	byte header[7] = {0};
	int keycount = 0;

	// byte[7]        start of every file: CD CC 0C 40 52 4D 46 ("????RMF")
	I.GetByte(header, 7);

	// int            number of vis groups
	// VisGroup[]     visgroups
	GetVisGroups(&I);

	// nstring        "CMapWorld"
	GetNString(&I, mapworld);
	
	// byte[7]        ? (probably visgroup and Color fields but not used by VHE)
	I.Next(Byte, 7);

	// int            number of objects
	// Object[]       world brushes, entities and groups
	GetObjects(&I, &this->FileSolids, &this->FileGroups, &this->FileEntities);

	// nstring        classname of worldspawn entity (should be "worldspawn")
	GetNString(&I, worldspawn);
	if (strcmp(worldspawn, "worldspawn") != 0)
		res = false;

	// byte[4]        ?
	I.Next(Byte, 4);

	// int            worldspawn entity flags (VHE does not allow you to set any flags for the worldspawn so these are probably unused)
	I.GetInteger(&this->FileWorldspawn.EntityFlags);

	// int            number of worldspawn entity key/value pairs
	// nstring[]      worldspawn key/value pairs (standard keys are "classname"="worldspawn", "sounds"="#", "MaxRange"="#", "mapversion"="220")
	GetKeys(&I, &this->FileWorldspawn.EntiyKeys);

	// byte[12]       ?
	I.Next(Byte, 12);

	// int            number of paths
	// Path[]         paths
	GetPaths(&I, &this->FilePaths);

	// string(7)      "DOCINFO"

	// byte[?]        ? (usually 13 bytes but not always)

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetVisGroups(CByteIterator* I)
{
	float color[4] = {0};
	byte b[3] = {0};
	int visgroupcount = 0;

	// int            number of vis groups
	I->GetInteger(&visgroupcount);

	if (visgroupcount != 0)
	{
		for (int i = 0; i < visgroupcount; i++)
		{
			CRMFVisGroup* visgroup = new CRMFVisGroup();

			// string(128)     name of vis group
			I->GetCharacter(visgroup->VisgroupName, 128);

			// Color           display color
			I->GetByte(b, 3);
			color[0] = (1.0f / 255) * (int)b[0];
			color[1] = (1.0f / 255) * (int)b[1];
			color[2] = (1.0f / 255) * (int)b[2];
			visgroup->VisgroupColor.Set(color);

			// byte            ?
			I->Next(Byte);

			//int             index of visgroup (other objects refer to visgroups with this number)
			I->GetInteger(&visgroup->VisgroupIndex);

			// byte            1=visible, 0=not visible
			I->GetBoolean(&visgroup->VisgroupVisible);

			// byte[3]         ?
			I->Next(Byte, 3);

			this->FileVisGroups.Add(visgroup);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetObjects(CByteIterator* I, SolidList* solids, GroupList* groups, EntityList* entities)
{
	int ObjectCount = 0;
	char naam[256] = {0};

	// int            number of objects
	I->GetInteger(&ObjectCount);

	// Object[]       world brushes, entities and groups
	for (int i = 0; i < ObjectCount; i++)
	{
		// nstring        "CMapSolid"
		// of 
		// nstring        "CMapEntity"
		// of 
		// nstring        "CMapGroup"
		GetNString(I, naam);

		if (strstr(naam, "CMapSolid") != 0)
		{
			CRMFSolid* solid = new CRMFSolid();

			GetSolid(I, solid);
			
			solids->Add(solid);
		}
		else if (strstr(naam, "CMapGroup") != 0)
		{
			CRMFGroup* group = new CRMFGroup();

			GetGroup(I, group);
			
			groups->Add(group);
		}
		else if (strstr(naam, "CMapEntity") != 0)
		{
			CRMFEntity* entity = new CRMFEntity();

			GetEntity(I, entity);
			
			entities->Add(entity);
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetSolid(CByteIterator* I, CRMFSolid* solid)
{
	float color[3] = {0};
	byte b[3] = {0};
	int facecount = 0;

	// int            visgroup
	I->GetInteger(&solid->SolidVisgroup);

	// Color          display color (VHE ignores this if the solid is part of an entity or group)
	I->GetByte(b, 3);
	color[0] = (1.0f / 255) * (int)b[0];
	color[1] = (1.0f / 255) * (int)b[1];
	color[2] = (1.0f / 255) * (int)b[2];
	solid->SolidColor.Set(color);

	// byte[4]        ?
	I->Next(Byte, 4);

	// int            number of faces
	// Face[]         faces in no particular order
	GetFaces(I, &solid->SolidFaces);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetGroup(CByteIterator* I, CRMFGroup* group)
{
	float color[3] = {0};
	byte b[3] = {0};

	// int            visgroup
	I->GetInteger(&group->GroupVisgroup);

	// Color          display color (overrides color of any contained solids)
	I->GetByte(b, 3);
	color[0] = (1.0f / 255) * (int)b[0];
	color[1] = (1.0f / 255) * (int)b[1];
	color[2] = (1.0f / 255) * (int)b[2];
	group->GroupColor.Set(color);

	// int            number of objects in group
	// Object[]       objects (can contain solids, entities or nested groups!)
	GetObjects(I, &group->GroupSolids, &group->GroupGroups, &group->GroupEntities);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetEntity(CByteIterator* I, CRMFEntity* entity)
{
	int solidcount = 0;
	float color[3] = {0};
	byte b[3] = {0};
	char str[256] = {0};
	int keycount = 0;
	float v[3] = {0};

	// int            visgroup
	I->GetInteger(&entity->EntityVisgroup);

	// byte[3]        display color (VHE draws all entities purple regardless of this or any other color value)
	I->GetByte(b, 3);
	color[0] = (1.0f / 255) * (int)b[0];
	color[1] = (1.0f / 255) * (int)b[1];
	color[2] = (1.0f / 255) * (int)b[2];
	entity->EntityColor.Set(color);

	// int            number of brushes (0 for point entity)
	I->GetInteger(&solidcount);

	// Solid[]        entity brushes
	for (int i = 0; i < solidcount; i++)
	{
		GetNString(I, str);

		CRMFSolid* solid = new CRMFSolid();
		GetSolid(I, solid);
		entity->EntitySolids.Add(solid);
	}

	// nstring        classname (max length is 128)
	GetNString(I, entity->EntityClassname, 128);

	// byte[4]        ?
	I->Next(Byte, 4);

	// int            entity flags
	I->GetInteger(&entity->EntityFlags);

	// int            number of key/value pairs
	// nstring[]      entity key/value pairs (array contains key, value, key value, etc.. max length is 32 for keys and 100 for values)
	GetKeys(I, &entity->EntiyKeys);

	// byte[14]       ?
	I->Next(Byte, 14);

	// Vector         position of entity in world coordinates (only used for point entities)
	I->GetFloat(v, 3);
	entity->EntityPosition.Fill(v[0], v[1], v[2]);

	// byte[4]        ?
	I->Next(Byte, 4);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetFaces(CByteIterator* I, FaceList* facelist)
{
	float v[3] = {0};
	int facecount = 0;
	int vertexcount = 0;

	// int            number of faces
	I->GetInteger(&facecount);

	// Face[]         faces in no particular order
	for (int i = 0; i < facecount; i++)
	{
		CRMFFace* face = new CRMFFace();

		// string(256)     texture name
		I->GetCharacter(face->FaceTexture, 256);

		// float           ?
		I->Next(Float);

		// Vector          texture U axis
		I->GetFloat(v, 3);
		face->FaceUAxis.Fill(v[0], v[1], v[2]);

		// float           texture X shift
		I->GetFloat(&face->FaceXShift);

		// Vector          texture V axis
		I->GetFloat(v, 3);
		face->FaceVAxis.Fill(v[0], v[1], v[2]);

		// float           texture Y shift
		I->GetFloat(&face->FaceYShift);

		// float           texture rotation in degrees
		I->GetFloat(&face->FaceRotation);

		// float           texture X scale factor
		I->GetFloat(&face->FaceXScale);

		// float           texture Y scale factor
		I->GetFloat(&face->FaceYScale);

		// byte[16]        ?
		I->Next(Byte, 16);

		// int             number of vertices
		I->GetInteger(&vertexcount);

		// Vector[]        vertex coordinates in clockwise order looking from front of face
		face->InitVertices(vertexcount);
		for (int i = 0; i < vertexcount; i++)
		{
			GetVertex(I, &face->FaceVertices[i]);
		}

		// Vector[3]       3 points defining plane of face (VHE simply uses a copy of the first 3 vertices)
		for (i = 0; i < 3; i++)
		{
			GetVertex(I, &face->FacePlaneVertices[i]);
		}

		// Create Face Plane
		face->FacePlane.Init(face->FacePlaneVertices[0], face->FacePlaneVertices[1], face->FacePlaneVertices[2]);

		facelist->Add(face);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetPaths(CByteIterator* I, PathList* pathlist)
{
	int pathcount = 0;

	// int            number of paths
	I->GetInteger(&pathcount);

	// Path[]         paths
	for (int j = 0; j < pathcount; j++)
	{
		CRMFPath* path = new CRMFPath();

		// string(128)    path name
		I->GetCharacter(path->PathName, 128);

		// string(128)    path class (should be "path_corner" or "path_track")
		I->GetCharacter(path->PathClass, 128);

		// int            path type: 0=one way, 1=circular, 2=ping-pong
		I->GetInteger(&path->PathType);

		// int            number of corners
		// Corner[]       corners in the order they appear in the path
		GetCorners(I, &path->PathCorners);

		pathlist->Add(path);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetCorners(CByteIterator* I, CornerList* cornerlist)
{
	float v[3] = {0};
	int keycount = 0;
	int cornercount = 0;

	// int            number of corners
	I->GetInteger(&cornercount);

	// Corner[]       corners in the order they appear in the path
	for (int i = 0; i < cornercount; i++)
	{
		CRMFCorner* corner = new CRMFCorner();

		// Vector         position in world coordinates
		I->GetFloat(v, 3);
		corner->CornerPosition.Fill(v[0], v[1], v[2]);
		
		// int            index for this corner.. used to generate targetnames (corner01, corner02, etc..)
		I->GetInteger(&corner->CornerIndex);
		
		// string(128)    name override (empty string if not overridden)
		I->GetCharacter(corner->CornerName, 128);
		
		// int            number of key/value pairs
		// nstring[]      key/value pairs (array contains key, value, key value, etc.)
		GetKeys(I, &corner->CornerKeys);

		cornerlist->Add(corner);
	}

	// 			  NOTE: these are supposed to be entity properties for the corner but VHE doesn't save them correctly
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetVertex(CByteIterator* I, Vector* vertex)
{
	float v[3] = {0};

	// float[3]        x, y and z components, respectively
	I->GetFloat(v, 3);

	vertex->Fill(v[0], v[1], v[2]);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetKeys(CByteIterator* I, KeyList* keylist)
{
	int keycount = 0;

	// int            number of worldspawn entity key/value pairs
	I->GetInteger(&keycount);

	// nstring[]      worldspawn key/value pairs (standard keys are "classname"="worldspawn", "sounds"="#", "MaxRange"="#", "mapversion"="220")
	for (int i = 0; i < keycount; i++)
	{
		char ckey[32] = {0};
		char cvalue[100] = {0};

		// string(32)      Key name
		GetNString(I, ckey, 32);

		// string(100)     Key value
		GetNString(I, cvalue, 100);

		keylist->Add(new CRMFKey(ckey, cvalue));
	}
}


//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetNString(CByteIterator* I, char* str)
{
	GetNString(I, str, 256);
}


//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::GetNString(CByteIterator* I, char* str, int max)
{
	int i = 0;
	byte b = {0};

	I->GetByte(&b);

	while (i < (int)b && i < max)
	{
		I->GetCharacter(&str[i]);
		i++;
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CRMFFile::GetNumVisGroups()
{
	return this->FileVisGroups.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CRMFFile::GetVisGroupName(int index)
{
	char* res = 0;

	if (index < (int)this->FileVisGroups.Length())
		res = this->FileVisGroups[index]->VisgroupName;

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CRMFFile::DrawGl()
{
	glPushMatrix();

	glScalef(0.2f, 0.2f, 0.2f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);
	
	GLfloat LightAmbient1[]= { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat LightDiffuse1[]= { 0.01f, 0.01f, 0.01f, 1.0f };
	GLfloat LightPosition1[]= { 100.0f, 100.0f, 100.0f, 1.0f };
	GLfloat LightAmbient2[]= { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat LightDiffuse2[]= { 0.01f, 0.01f, 0.01f, 1.0f };
	GLfloat LightPosition2[]= { -100.0f, -100.0f, 100.0f, 1.0f };

	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);

	GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse1);
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition1);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse2);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition2);
	glEnable(GL_LIGHT1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	for (int i = 0; i < (int)this->FileSolids.Length(); i++)
	{
		this->FileSolids[i]->DrawGl();
	}

	for (i = 0; i < (int)this->FileGroups.Length(); i++)
	{
		this->FileGroups[i]->DrawGl();
	}

	for (i = 0; i < (int)this->FileEntities.Length(); i++)
	{
		this->FileEntities[i]->DrawGl();
	}

	for (i = 0; i < (int)this->FilePaths.Length(); i++)
	{
		this->FilePaths[i]->DrawGl();
	}

	glPopMatrix();
}
