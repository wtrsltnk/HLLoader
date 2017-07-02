#ifndef CAPPLICATION_H
#define CAPPLICATION_H

#include "CWin.h"
#include "_msvc/resource.h"
#include "FileLoader.h"

#define ID_MOPENBSP		2305
#define ID_MOPENMAP		2315
#define ID_MOPENRMF		2325
#define ID_MOPENWAD		2335
#define ID_MOPENMS3D	2345
#define ID_MCLOSEBSP	2355
#define ID_MCLOSEMAP	2365
#define ID_MCLOSERMF	2375
#define ID_MCLOSEWAD	2385
#define ID_MCLOSEMS3D	2395
#define ID_MSAVEBSPTEX	2405
#define ID_MSAVEBSPENT  2415
#define ID_MSAVEMAP		2425
#define ID_MSAVEWADTEX	2435
#define ID_MSAVEMS3D	2445
#define ID_MSHOWRMF		2455
#define ID_MSHOWMS3D	2466

class CApplication : public CWin
{
private:
	HMENU m_hRightClickMenu;
	CFileLoader* pFileLoader;

	void DrawLine(HDC hdc, int x, int y);
public:
	CApplication();
	~CApplication();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
};

#endif
