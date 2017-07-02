// DirectoryFile.h: interface for the CDirectoryFile class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DIRECTORYFILE_H
#define DIRECTORYFILE_H

#include "DirectoryNode.h"

class CDirectoryFile : public CDirectoryNode
{
protected:
public:
	CDirectoryFile(char* name, int id = 0, CDirectoryNode* parent = 0);
	virtual ~CDirectoryFile();

};

#endif
