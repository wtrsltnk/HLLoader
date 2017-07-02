// FileLoader.h: interface for the CFileLoader class.
//
//////////////////////////////////////////////////////////////////////

#ifndef FILELOADER_H
#define FILELOADER_H

#include "windows.h"
#include "BSP/BSPFile.h"
#include "MAP/MAPFile.h"
#include "RMF/RMFFile.h"
#include "WAD/WADFile.h"
#include "MS3D/MS3DFile.h"
#include "ThreeD.h"

class CFileLoader  
{
private:
	HWND hParent;
	CBSPFile* bsp;
	CMAPFile* map;
	CRMFFile* rmf;
	CWADFile* wad;
	CMS3DFile* ms3d;

	bool OpenFile(HWND hOwner, char* result, char *szFilter, char *szDefExt);
	bool Directory(HWND hOwner, char* result);
	bool SaveFile(HWND hOwner, char* result, char *szFilter, char *szDefExt);
public:
	CFileLoader(HWND hParent);
	virtual ~CFileLoader();

	bool LoadBSP() throw();
	bool LoadMAP() throw();
	bool LoadRMF() throw();
	bool LoadWAD() throw();
	bool LoadMS3D() throw();

	int SaveBSPTextures();
	int SaveBSPEntities();
	int SaveMAPFile();
	int SaveWADTextures();
	bool SaveMS3D();
	int ShowRMF3D();
	int ShowMS3D3D();

	void CloseBSP();
	void CloseMAP();
	void CloseRMF();
	void CloseWAD();
	void CloseMS3D();

	int DrawBSP(HDC hdc, int x, int y);
	int DrawMAP(HDC hdc, int x, int y);
	int DrawRMF(HDC hdc, int x, int y);
	int DrawWAD(HDC hdc, int x, int y);
	int DrawMS3D(HDC hdc, int x, int y);

	CWADMiptex* GetBSPTetxure(int index);
	CWADMiptex* GetWADTetxure(int index);
};

#endif
