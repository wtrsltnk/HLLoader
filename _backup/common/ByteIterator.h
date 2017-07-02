// ByteIterator.h: interface for the CByteIterator class.
//
//////////////////////////////////////////////////////////////////////

#ifndef BYTEITERATOR_H
#define BYTEITERATOR_H

typedef unsigned char byte;
typedef unsigned short word;

enum
{
	Byte = 1,
	Float = 4,
	Integer = 4
};

class CByteIterator  
{
private:
	char* ByteData;
	int ByteLength;
	int BytePosition;
public:
	CByteIterator(char* data, int length);
	virtual ~CByteIterator();

	bool Next(int size, int count);
	bool Next(int size);

	void GetFloat(float* in);
	void GetFloat(float* in, int count);
	void GetInteger(int* in);
	void GetInteger(int* in, int count);
	void GetByte(byte* in);
	void GetByte(byte* in, int count);
	void GetWord(word* in);
	void GetWord(word* in, int count);
	void GetCharacter(char* in);
	void GetCharacter(char* in, int count);
	void GetBoolean(bool* in);
	void GetBoolean(bool* in, int count);

};

#endif
