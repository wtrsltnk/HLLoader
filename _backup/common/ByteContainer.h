// ByteContainer.h: interface for the CByteContainer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BYTECONTAINER_H
#define BYTECONTAINER_H

typedef unsigned char byte;
typedef unsigned short word;

class CByteContainer  
{
private:
	char* ByteData;
	int ByteLength;
	int BytePosition;

	bool DoubleBuffer();
public:
	CByteContainer();
	virtual ~CByteContainer();

	int GetData(char** data);

	void AddFloat(float in);
	void AddFloat(float in[], int count);
	void AddInteger(int in);
	void AddInteger(int in[], int count);
	void AddByte(byte in);
	void AddByte(byte in[], int count);
	void AddWord(word in);
	void AddWord(word in[], int count);
	void AddCharacter(char in);
	void AddCharacter(char in[], int count);
	void AddBoolean(bool in);
	void AddBoolean(bool in[], int count);

};

#endif
