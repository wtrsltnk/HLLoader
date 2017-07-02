// DirectoryFolder.h: interface for the CDirectoryFolder class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DIRECTORYFOLDER_H
#define DIRECTORYFOLDER_H

#include "DirectoryNode.h"

class CDirectoryFolder : public CDirectoryNode
{
protected:
	CDirectoryNode* FirstChildNode;
public:
	CDirectoryFolder(char* name, int id = 0, CDirectoryNode* parent = 0);
	virtual ~CDirectoryFolder();

	void AddNode(CDirectoryNode* childNode);
};

#endif
