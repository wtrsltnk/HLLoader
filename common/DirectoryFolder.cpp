// DirectoryFolder.cpp: implementation of the CDirectoryFolder class.
//
//////////////////////////////////////////////////////////////////////

#include "DirectoryFolder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectoryFolder::CDirectoryFolder(char* name, int id, CDirectoryNode* parent) : CDirectoryNode(name, id, parent)
{
}

CDirectoryFolder::~CDirectoryFolder()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CDirectoryFolder::AddNode(CDirectoryNode* childNode)
{
	if (this->FirstChildNode == 0)
	{
		this->FirstChildNode = childNode;
	}
	else
	{
		CDirectoryNode* tmp =  this->FirstChildNode;
		while (tmp->NextSibling != 0)
		{
			tmp = tmp->NextSibling;
		}
		tmp->NextSibling = childNode;
	}
}
