// MAPParser.cpp: implementation of the CMAPParser class.
//
//////////////////////////////////////////////////////////////////////

#include "MAPParser.h"
#include <string.h>
#include <sys/stat.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMAPParser::CMAPParser()
{
	this->ParseBuf = 0;
	this->ParseSize = 0;
	this->ParsePos = 0;
	this->ParseType = eNull;
}

CMAPParser::~CMAPParser()
{
	Finisch();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPParser::SetMAPFile(const char* filename)
{
	bool res = true;
	FILE *file;
	size_t numread;
	struct _stat status;

	if (_stat(filename, &status) == 0)
	{
		this->ParseSize = (int)status.st_size + 1;

		if (this->ParseBuf)
			delete this->ParseBuf;

		this->ParseBuf = new char[this->ParseSize];

		if (this->ParseBuf)
		{
			file = fopen(filename, "rt");
			if (file)
			{
				numread = fread(this->ParseBuf, sizeof(char), this->ParseSize, file);
				this->ParseBuf[numread] = '\0';

				fclose(file);
			}
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPParser::SetMAPBuffer(char* buffer)
{
	this->ParseSize = strlen(buffer);
	try
	{
		this->ParseBuf = new char[this->ParseSize];
	}
	catch(...)
	{
		return false;
	}
	strncpy(this->ParseBuf, buffer, this->ParseSize);
	return true;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CMAPParser::Finisch()
{
	if (this->ParseBuf)
	{
		delete [] this->ParseBuf;
	}
	this->ParseBuf = 0;
	this->ParseSize = 0;
	this->ParsePos = 0;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CMAPParser::GoToNextToken()
{
	bool res = false;

	while (this->ParsePos < this->ParseSize)
	{
		if (this->ParseBuf[this->ParsePos] != ' ' && this->ParseBuf[this->ParsePos] != '\n' && this->ParseBuf[this->ParsePos] != '\t')
			break;
		this->ParsePos++;
	}

	if (this->ParsePos <= this->ParseSize)
	{
		int len = 0;
		memset(this->ParseData, 0, sizeof(this->ParseData));

		switch (this->ParseBuf[this->ParsePos])
		{
		case '}':
			{
				this->ParseData[0] = this->ParseBuf[this->ParsePos];
				len = 1;
				this->ParseType = eEndBracket;
				break;
			}

		case '{':
			{
				this->ParseData[0] = this->ParseBuf[this->ParsePos];
				len = 1;
				this->ParseType = eStartBracket;
				break;
			}

		case '\"':
			{
				this->ParsePos++;
				do
				{
					this->ParseData[len] = this->ParseBuf[this->ParsePos+len];
					len++;
				} while (this->ParseBuf[this->ParsePos+len] != '\"');
				this->ParseType = eString;
				break;
			}

		case '(':
			{
				
				do
				{
					this->ParseData[len] = this->ParseBuf[this->ParsePos+len];
					len++;
				} while (this->ParseBuf[this->ParsePos+len] != '\n');
				this->ParseType = ePlane;
				break;
			}

		case '\0':
			{
				this->ParseType = eEnd;
				break;
			}

		default:
			{
				do
				{
					this->ParseData[len] = this->ParseBuf[this->ParsePos+len];
					len++;
				} while ((this->ParseBuf[this->ParsePos+len] != '\n') && this->ParseBuf[this->ParsePos+len] != '\0');
				this->ParseType = eComment;
			}
		}
		this->ParseData[len] = '\0';
		this->ParsePos += len;
		this->ParsePos++;
		res = true;
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CMAPParser::GetToken()
{
	return this->ParseData;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CMAPParser::GetType()
{
	return this->ParseType;
}
