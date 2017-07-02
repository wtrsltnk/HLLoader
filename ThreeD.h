// ThreeD.h: interface for the CThreeD class.
//
//////////////////////////////////////////////////////////////////////

#ifndef THREED_H
#define THREED_H

#define WIN32_MEAN_ADN_LEAN
#include <windows.h>
#include "_msvc/resource.h"

#include "RMF/RMFFile.h"
#include "MS3D/MS3DFile.h"
#include "WtrEngine.h"
#include "Keys.h"

class CThreeD  
{
protected:
	HWND m_hDlg;
	HWND m_hParent;
	HINSTANCE m_hInstance;
	DWORD m_dwResourceDlg;

	CRMFFile* rmf;
	CMS3DFile* ms3d;
	CWtrEngine* engine;
public:
	CThreeD();
	virtual ~CThreeD();

	int ShowModal(HINSTANCE hInst, HWND hParent);
	int ShowModalless(HINSTANCE hInst, HWND hParent);
	void SetHandle(HWND hWnd);
	void SetRMF(CRMFFile* rmf);
	void SeMS3D(CMS3DFile* ms3d);

	static LRESULT BaseProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
