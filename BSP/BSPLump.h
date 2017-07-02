// BSPLump.h: interface for the CBSPLump class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BSPLUMP_H
#define BSPLUMP_H

#include <stdio.h>
#include "bsptypes.h"

typedef struct
{
	int		fileofs, filelen;
} tBspLump;

class CBSPLump  
{
private:	
	int LumpLength;
	int LumpType;
	int TypeSize;
	char* LumpData;
	
public:
	CBSPLump();
	virtual ~CBSPLump();

	bool InitData(char* data, int len, int type, int size);

	int GetData(char** data);

	int GetItemCount();
	int GetTypeSize();
	char* GetItem(int index);
};

#endif
