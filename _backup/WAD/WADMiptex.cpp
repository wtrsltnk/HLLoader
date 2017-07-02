// WADMiptex.cpp: implementation of the CWADMiptex class.
//
//////////////////////////////////////////////////////////////////////

#include "WADMiptex.h"
#include <stdio.h>

int WriteBMPfile (char *szFile, byte *pbBits, int width, int height, byte *pbPalette);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWADMiptex::CWADMiptex()
{
	memset(this->TextureName, 0, sizeof(this->TextureName));
	this->TextureData = 0;
	this->TextureWidth = 0;
	this->TextureHeight = 0;
	this->TextureBits = 0;
	this->TexturePalette = 0;
}

CWADMiptex::CWADMiptex(char* texname)
{
	strcpy(this->TextureName, texname);
	this->TextureData = 0;
	this->TextureWidth = 0;
	this->TextureHeight = 0;
	this->TextureBits = 0;
	this->TexturePalette = 0;
}

CWADMiptex::~CWADMiptex()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWADMiptex::InitName(char* name)
{
	strcpy(this->TextureName, name);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWADMiptex::InitData(char* name, char* data)
{
	strcpy(this->TextureName, name);
	this->TextureData = data;
	tMiptex* tex = (tMiptex*)this->TextureData;

	this->TextureWidth = tex->width;
	this->TextureHeight = tex->height;
	this->TextureBits = ((byte*)this->TextureData) + tex->offsets[0];
	this->TexturePalette = ((byte*)this->TextureData) + tex->offsets[3] + this->TextureWidth * this->TextureHeight / 64 + 2;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CWADMiptex::HasData()
{
	bool res = false;

	if (this->TextureData != 0)
		res = true;

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CWADMiptex::GetName()
{
	return this->TextureName;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CWADMiptex::WriteBMP(char* path)
{
	bool res = false;
	char filename[256];

	sprintf(filename, "%s/%s.bmp", path, this->TextureName);
	int rc = WriteBMPfile(filename, this->TextureBits, this->TextureWidth, this->TextureHeight, this->TexturePalette);

	if (rc == 0)
		res = true;

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CWADMiptex::GetWidth()
{
	return this->TextureWidth;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CWADMiptex::GetHeight()
{
	return this->TextureHeight;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
char* CWADMiptex::GetData()
{
	return this->TextureData;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
byte* CWADMiptex::GetPalette()
{
	return this->TexturePalette;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int WriteBMPfile (char *szFile, byte *pbBits, int width, int height, byte *pbPalette)
{
	int i, rc = 0;
	FILE *pfile = NULL;
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	RGBQUAD rgrgbPalette[256];
	ULONG cbBmpBits;
	BYTE* pbBmpBits;
	byte  *pb, *pbPal = NULL;
	ULONG cbPalBytes;
	ULONG biTrueWidth;

	// Bogus parameter check
	if (!(pbPalette != NULL && pbBits != NULL))
		{ rc = -1000; goto GetOut; }

	// File exists?
	if ((pfile = fopen(szFile, "wb")) == NULL)
		{ rc = -1; goto GetOut; }

	biTrueWidth = ((width + 3) & ~3);
	cbBmpBits = biTrueWidth * height;
	cbPalBytes = 256 * sizeof( RGBQUAD );

	// Bogus file header check
	bmfh.bfType = MAKEWORD( 'B', 'M' );
	bmfh.bfSize = sizeof bmfh + sizeof bmih + cbBmpBits + cbPalBytes;
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof bmfh + sizeof bmih + cbPalBytes;

	// Write file header
	if (fwrite(&bmfh, sizeof bmfh, 1/*count*/, pfile) != 1)
		{ rc = -2; goto GetOut; }

	// Size of structure
	bmih.biSize = sizeof bmih;
	// Width
	bmih.biWidth = biTrueWidth;
	// Height
	bmih.biHeight = height;
	// Only 1 plane 
	bmih.biPlanes = 1;
	// Only 8-bit supported.
	bmih.biBitCount = 8;
	// Only non-compressed supported.
	bmih.biCompression = BI_RGB;
	bmih.biSizeImage = 0;

	// huh?
	bmih.biXPelsPerMeter = 0;
	bmih.biYPelsPerMeter = 0;

	// Always full palette
	bmih.biClrUsed = 256;
	bmih.biClrImportant = 0;
	
	// Write info header
	if (fwrite(&bmih, sizeof bmih, 1/*count*/, pfile) != 1)
		{ rc = -3; goto GetOut; }
	

	// convert to expanded palette
	pb = pbPalette;

	// Copy over used entries
	for (i = 0; i < (int)bmih.biClrUsed; i++)
	{
		rgrgbPalette[i].rgbRed   = *pb++;
		rgrgbPalette[i].rgbGreen = *pb++;
		rgrgbPalette[i].rgbBlue  = *pb++;
        rgrgbPalette[i].rgbReserved = 0;
	}

	// Write palette (bmih.biClrUsed entries)
	cbPalBytes = bmih.biClrUsed * sizeof( RGBQUAD );
	if (fwrite(rgrgbPalette, cbPalBytes, 1/*count*/, pfile) != 1)
		{ rc = -6; goto GetOut; }


	pbBmpBits = (unsigned char*)malloc(cbBmpBits);

	pb = pbBits;
	// reverse the order of the data.
	pb += (height - 1) * width;
	for(i = 0; i < bmih.biHeight; i++)
	{
		memmove(&pbBmpBits[biTrueWidth * i], pb, width);
		pb -= width;
	}

	// Write bitmap bits (remainder of file)
	if (fwrite(pbBmpBits, cbBmpBits, 1/*count*/, pfile) != 1)
		{ rc = -7; goto GetOut; }

	free(pbBmpBits);

GetOut:
	if (pfile) 
		fclose(pfile);

	return rc;
}
