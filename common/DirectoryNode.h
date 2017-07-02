// DirectoryNode.h: interface for the CDirectoryNode class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DIRECTORYNODE_H
#define DIRECTORYNODE_H

class CDirectoryNode  
{
	friend class CDirectoryFolder;
	friend class CDirectoryFile;
protected:
	CDirectoryNode* Parent;
	CDirectoryNode* NextSibling;

	char* Name;
	int ID;
public:
	CDirectoryNode(char* name, int id = 0, CDirectoryNode* parent = 0);
	virtual ~CDirectoryNode();

	void SetParentNode(CDirectoryNode* parent);
	void SetNextSibling(CDirectoryNode* nextSibling);
};

#endif
