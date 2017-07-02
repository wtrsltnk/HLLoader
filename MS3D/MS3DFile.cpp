// MS3DFile.cpp: implementation of the CMS3DFile class.
//
//////////////////////////////////////////////////////////////////////

#include "MS3DFile.h"
#include "common/ByteIterator.h"

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <time.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMS3DFile::CMS3DFile()
{
}

CMS3DFile::~CMS3DFile()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::Clear()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMS3DFile::LoadMS3DFile(const char* filename) throw()
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
	{
		throw("Can\'t parse the data from the file");
		res = false;
	}

	CBaseFile::Clear();

	return res;
}
/*
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMS3DFile::SaveMS3DFile(const char* filename) throw()
{
	bool res = true;

	if (!PrepareFile())
	{
		throw("Can\'t prepare the data for the file");
		res = false;
	}

	if (res)
	{
		try
		{
			CBaseFile::SaveFile(filename);
		}
		catch(char* err)
		{
			res = false;
			throw(err);
		}
	}

	CBaseFile::Clear();

	return res;
}
*/
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMS3DFile::ParseData()
{
	bool res  = false;
	CByteIterator I(this->FileData, this->FileLength);

	I.GetCharacter(this->FileID, 10);
	
	if (strncmp(this->FileID, "MS3D000000", 10) == 0)
	{
		I.GetInteger(&this->FileVersion);
		if (this->FileVersion == 4)
		{
			this->GetVertices(&I, &this->FileVertices);

			this->GetTriangles(&I, &this->FileTriangles);

			this->GetGroups(&I, &this->FileGroups);

			this->GetMaterials(&I, &this->FileMaterials);

			I.GetFloat(&this->FileAnimationFPS);
			I.GetFloat(&this->FileCurrentTime);
			I.GetInteger(&this->FileTotalFrames);

			this->GetJoints(&I, &this->FileJoints);

			res = true;
		}
	}

	return res;
}
/*
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMS3DFile::PrepareFile()
{
	bool res  = true;
	CByteContainer C;

	C.AddCharacter(this->FileID, 10);
	C.AddInteger(this->FileVersion);

	this->PutVertices(&C, &this->FileVertices);
	this->PutTriangles(&C, &this->FileTriangles);
	this->PutGroups(&C, &this->FileGroups);
	this->PutMaterials(&C, &this->FileMaterials);

	C.AddFloat(this->FileAnimationFPS);
	C.AddFloat(this->FileCurrentTime);
	C.AddInteger(this->FileTotalFrames);

	this->PutJoints(&C, &this->FileJoints);

	this->FileLength = C.GetData(&this->FileData);

	return res;
}
*/
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::GetVertices(CByteIterator* I, MS3DVertexList* vertices)
{
	word vertexcount;

	// word nNumVertices;
	I->GetWord(&vertexcount);

	for (int i = 0; i < vertexcount; i++)
	{
		CMS3DVertex* vertex = new CMS3DVertex();

		// byte    flags;
		I->GetByte(&vertex->VertexFlags);

		// float   vertex[3];
		I->GetFloat(vertex->VertexVertex, 3);

		// char    boneId;
		I->GetCharacter(&vertex->VertexBoneId);

		// byte    referenceCount;
		I->GetByte(&vertex->VertexReferenceCount);

		vertices->Add(vertex);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::GetTriangles(CByteIterator* I, MS3DTriangleList* triangles)
{
	word trianglecount;
	
	// word nNumTriangles;
	I->GetWord(&trianglecount);

	for (int i = 0; i < trianglecount; i++)
	{
		CMS3DTriangle* triangle = new CMS3DTriangle();

		// word    flags;
		I->GetWord(&triangle->TriangleFlags);

		// word    vertexIndices[3];
		I->GetWord(triangle->TriangleVertexIndices, 3);

		// float   vertexNormals[3][3];
		I->GetFloat(triangle->TriangleVertexNormals[0], 3);
		I->GetFloat(triangle->TriangleVertexNormals[1], 3);
		I->GetFloat(triangle->TriangleVertexNormals[2], 3);

		// float   s[3];
		I->GetFloat(triangle->TriangleS, 3);

		// float   t[3];
		I->GetFloat(triangle->TriangleT, 3);

		// byte    smoothingGroup;
		I->GetByte(&triangle->TriangleSmoothingGroup);

		// byte    groupIndex;
		I->GetByte(&triangle->TriangleGroupIndex);

		triangles->Add(triangle);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::GetIndices(CByteIterator* I, IndexList* indices)
{
	word indexcount;
	
	I->GetWord(&indexcount);

	for (int i = 0; i < indexcount; i++)
	{
		word index;

		I->GetWord(&index);

		indices->Add(index);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::GetGroups(CByteIterator* I, MS3DGroupList* groups)
{
	word groupcount;
	
	// word nNumGroups;
	I->GetWord(&groupcount);

	for (int i = 0; i < groupcount; i++)
	{
		CMS3DGroup* group = new CMS3DGroup();

		// byte            flags;
		I->GetByte(&group->GroupFlags);

		// char            name[32];
		I->GetCharacter(group->GroupName, 32);

		// word            numtriangles;
		// word            triangleIndices[numtriangles];
		GetIndices(I, &group->GroupTriangleIndices);

		// char            materialIndex;
		I->GetCharacter(&group->GroupMaterialIndex);

		groups->Add(group);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::GetMaterials(CByteIterator* I, MS3DMaterialList* materials)
{
	word materialcount;
	
	// word nNumMaterials;
	I->GetWord(&materialcount);

	for (int i = 0; i < materialcount; i++)
	{
		CMS3DMaterial* material = new CMS3DMaterial();

		// char            name[32];
		I->GetCharacter(material->MaterialName, 32);

		// float           ambient[4];
		I->GetFloat(material->MaterialAmbient, 4);

		// float           diffuse[4];
		I->GetFloat(material->MaterialDiffuse, 4);

		// float           specular[4];
		I->GetFloat(material->MaterialSpecular, 4);

		// float           emissive[4];
		I->GetFloat(material->MaterialEmissive, 4);

		// float           shininess;
		I->GetFloat(&material->MaterialShininess);

		// float           transparency;
		I->GetFloat(&material->MaterialTransparency);

		// char            mode;
		I->GetCharacter(&material->MaterialMode);

		// char            texture[128];
		I->GetCharacter(material->MaterialTexture, 128);

		// char            alphamap[128];
		I->GetCharacter(material->MaterialAlphamap, 128);

		materials->Add(material);
	}
}
	
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::GetJoints(CByteIterator* I, MS3DJointList* joints)
{
	word jointcount;
	word keyframesrotcount;
	word keyframesposcount;
	
	// word nNumJoints;
	I->GetWord(&jointcount);

	for (int i = 0; i < jointcount; i++)
	{
		CMS3DJoint* joint = new CMS3DJoint();
		// byte            flags;
		I->GetByte(&joint->JointFlags);

		// char            name[32];
		I->GetCharacter(joint->JointName, 32);

		// char            parentName[32];
		I->GetCharacter(joint->JointParentName, 32);

		// float           rotation[3];
		I->GetFloat(joint->JointRotation, 3);

		// float           position[3];
		I->GetFloat(joint->JointPosition, 3);

		// word            numKeyFramesRot;
		I->GetWord(&keyframesrotcount);

		// word            numKeyFramesTrans;
		I->GetWord(&keyframesposcount);

		// ms3d_keyframe_rot_t keyFramesRot[numKeyFramesRot];
		GetKeyFrameRot(I, &joint->KeyFrameRot, keyframesrotcount);

		// ms3d_keyframe_pos_t keyFramesTrans[numKeyFramesTrans];
		GetKeyFramePos(I, &joint->KeyFramePos, keyframesposcount);

		joints->Add(joint);
	}
}
	
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::GetKeyFrameRot(CByteIterator* I, MS3DKeyFrameRotList* keyframerot, int rotcount)
{
	for (int i = 0; i < rotcount; i++)
	{
		CMS3DKeyFrameRot* rot = new CMS3DKeyFrameRot();

		// float           time;
		I->GetFloat(&rot->RotTime);

    	// float           rotation[3];
		I->GetFloat(rot->RotRotation, 3);

		keyframerot->Add(rot);
	}
}
	
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::GetKeyFramePos(CByteIterator* I, MS3DKeyFramePosList* keyframepos, int poscount)
{
	for (int i = 0; i < poscount; i++)
	{
		CMS3DKeyFramePos* pos = new CMS3DKeyFramePos();

		// float           time;
		I->GetFloat(&pos->PosTime);

		// float           position[3];
		I->GetFloat(pos->PosPosition, 3);

		keyframepos->Add(pos);
	}
}
/*
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::PutVertices(CByteContainer* C, MS3DVertexList* vertices)
{
	C->AddWord((word)vertices->Length());

	for (int i = 0; i < (int)vertices->Length(); i++)
	{
		CMS3DVertex* vertex = (*vertices)[i];

		// byte    flags;
		C->AddByte(vertex->VertexFlags);

		// float   vertex[3];
		C->AddFloat(vertex->VertexVertex, 3);

		// char    boneId;
		C->AddCharacter(vertex->VertexBoneId);

		// byte    referenceCount;
		C->AddByte(vertex->VertexReferenceCount);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::PutTriangles(CByteContainer* C, MS3DTriangleList* triangles)
{
	C->AddWord((word)triangles->Length());

	for (int i = 0; i < (int)triangles->Length(); i++)
	{
		CMS3DTriangle* triangle = (*triangles)[i];

		// word    flags;
		C->AddWord(triangle->TriangleFlags);

		// word    vertexIndices[3];
		C->AddWord(triangle->TriangleVertexIndices, 3);

		// float   vertexNormals[3][3];
		C->AddFloat(triangle->TriangleVertexNormals[0], 3);
		C->AddFloat(triangle->TriangleVertexNormals[1], 3);
		C->AddFloat(triangle->TriangleVertexNormals[2], 3);

		// float   s[3];
		C->AddFloat(triangle->TriangleS, 3);

		// float   t[3];
		C->AddFloat(triangle->TriangleT, 3);

		// byte    smoothingGroup;
		C->AddByte(triangle->TriangleSmoothingGroup);

		// byte    groupIndex;
		C->AddByte(triangle->TriangleGroupIndex);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::PutIndices(CByteContainer* C, IndexList* indices)
{
	C->AddWord((word)indices->Length());

	for (int i = 0; i < (int)indices->Length(); i++)
	{
		C->AddWord((*indices)[i]);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::PutGroups(CByteContainer* C, MS3DGroupList* groups)
{
	C->AddWord((word)groups->Length());

	for (int i = 0; i < (int)groups->Length(); i++)
	{
		CMS3DGroup* group = (*groups)[i];

		// byte            flags;
		C->AddByte(group->GroupFlags);

		// char            name[32];
		C->AddCharacter(group->GroupName, 32);

		// word            numtriangles;
		C->AddWord((word)group->GroupTriangleIndices.Length());

		// word            triangleIndices[numtriangles];
		PutIndices(C, &group->GroupTriangleIndices);

		// char            materialIndex;
		C->AddCharacter(group->GroupMaterialIndex);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::PutMaterials(CByteContainer* C, MS3DMaterialList* materials)
{
	C->AddWord((word)materials->Length());

	for (int i = 0; i < (int)materials->Length(); i++)
	{
		CMS3DMaterial* material = (*materials)[i];

		// char            name[32];
		C->AddCharacter(material->MaterialName, 4);

		// float           ambient[4];
		C->AddFloat(material->MaterialAmbient, 4);

		// float           diffuse[4];
		C->AddFloat(material->MaterialDiffuse, 4);

		// float           specular[4];
		C->AddFloat(material->MaterialSpecular, 4);

		// float           emissive[4];
		C->AddFloat(material->MaterialEmissive, 4);

		// float           shininess;
		C->AddFloat(material->MaterialShininess);

		// float           transparency;
		C->AddFloat(material->MaterialTransparency);

		// char            mode;
		C->AddCharacter(material->MaterialMode);

		// char            texture[128];
		C->AddCharacter(material->MaterialTexture, 128);

		// char            alphamap[128];
		C->AddCharacter(material->MaterialAlphamap, 128);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::PutJoints(CByteContainer* C, MS3DJointList* joints)
{
	C->AddWord((word)joints->Length());

	for (int i = 0; i < (int)joints->Length(); i++)
	{
		CMS3DJoint* joint = (*joints)[i];

		// byte            flags;
		C->AddByte(joint->JointFlags);

		// char            name[32];
		C->AddCharacter(joint->JointName, 32);

		// char            parentName[32];
		C->AddCharacter(joint->JointParentName, 32);

		// float           rotation[3];
		C->AddFloat(joint->JointRotation, 3);

		// float           position[3];
		C->AddFloat(joint->JointPosition, 3);

		// word            numKeyFramesRot;
		C->AddWord((word)joint->KeyFrameRot.Length());

		// word            numKeyFramesTrans;
		C->AddWord((word)joint->KeyFramePos.Length());

		// ms3d_keyframe_rot_t keyFramesRot[numKeyFramesRot];
		PutKeyFrameRot(C, &joint->KeyFrameRot);

		// ms3d_keyframe_pos_t keyFramesTrans[numKeyFramesTrans];
		PutKeyFramePos(C, &joint->KeyFramePos);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::PutKeyFrameRot(CByteContainer* C, MS3DKeyFrameRotList* keyframerot)
{
	for (int i = 0; i < (int)keyframerot->Length(); i++)
	{
		CMS3DKeyFrameRot* rot = (*keyframerot)[i];

		// float           time;
		C->AddFloat(rot->RotTime);

		// float           rotation[3];
		C->AddFloat(rot->RotRotation, 3);
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::PutKeyFramePos(CByteContainer* C, MS3DKeyFramePosList* keyframepos)
{
	for (int i = 0; i < (int)keyframepos->Length(); i++)
	{
		CMS3DKeyFramePos* pos = (*keyframepos)[i];

		// float           time;
		C->AddFloat(pos->PosTime);

		// float           position[3];
		C->AddFloat(pos->PosPosition, 3);
	}
}
*/
//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CMS3DFile::GetNumGroups()
{
	return this->FileGroups.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CMS3DFile::GetGroup(int index)
{
	char* res = 0;

	if (index < (int)this->FileGroups.Length())
		res = this->FileGroups[index]->GroupName;

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CMS3DFile::GetNumMaterials()
{
	return this->FileMaterials.Length();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CMS3DFile::GetMaterial(int index)
{
	char* res = 0;

	if (index < (int)this->FileMaterials.Length())
		res = this->FileMaterials[index]->MaterialName;

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMS3DFile::DrawGl()
{
	glPushMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_CULL_FACE);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	
	GLfloat LightAmbient[]= { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };

	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);
	glEnable(GL_LIGHT0);

	for (int i = 0; i < (int)this->FileGroups.Length(); i++)
	{
		CMS3DGroup* group = this->FileGroups[i];

		glColor3f(0.0f, 0.5f, 1.0f);

		for (int j = 0; j < (int)group->GroupTriangleIndices.Length(); j++)
		{
			CMS3DTriangle* triangle = this->FileTriangles[group->GroupTriangleIndices[j]];
			
			glBegin(GL_TRIANGLES);
			for (int k = 0; k < 3; k++)
			{
				CMS3DVertex* vertex = this->FileVertices[triangle->TriangleVertexIndices[k]];

				glNormal3fv(&triangle->TriangleVertexNormals[k][0]);
				glVertex3f(vertex->VertexVertex[0], vertex->VertexVertex[1],vertex->VertexVertex[2]);
			}
			glEnd();
		}
	}

	glPopMatrix();
}