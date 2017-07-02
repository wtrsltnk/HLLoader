// MAPParser.h: interface for the CMAPParser class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <stdio.h>

enum
{
	eNull = 0,
	eStartBracket,
	eEndBracket,
	eString,
	ePlane,
	eCoord,
	eTexture,
	eComment,
	eEnd
};

class CMAPParser  
{
private:
	char* ParseBuf;
	int ParseSize;
	int ParsePos;
	char ParseData[1024];
	int ParseType;
public:
	CMAPParser();
	virtual ~CMAPParser();

	bool SetMAPFile(const char* filename);
	bool SetMAPBuffer(char* buffer);
	void Finisch();
	bool GoToNextToken();

	char* GetToken();
	int GetType();
};

#endif
