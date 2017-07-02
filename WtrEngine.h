// WtrEngine.h: interface for the CWtrEngine class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WTRENGINE_H
#define WTRENGINE_H

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "common/wiskunde.h"
#include "WtrCamera.h"

#define OK 1
#define ERR 0
#define FONT_RANGE 255

class __declspec(dllexport) CWtrEngine  
{
private:
	HWND m_hWnd;
	HDC m_hDC;
    HGLRC m_hRC;

	int m_iFont;
	HFONT m_hFont;

	int m_iWidth;
	int m_iHeight;
	DEVMODE* m_pDevmode;

	int	m_nFrequency; 
	int m_nFrameCount;
	int m_nFrameRate; 
	float m_fFrameDeviance;

	CWtrCamera m_Camera;

	int InitPixelformat();
	float GetNumTicksPerMs();
	void FrameCount();
	int InitTiming();
	int InitFont();
public:
	CWtrEngine();
	virtual ~CWtrEngine();

	int InitEngine(HWND hWnd, DEVMODE* pDevmode, bool fullscreen, HFONT hFont);
	int PreRender();
	int PostRender();

	void Resize(int width, int height);
	void InitView();
	void Shutdown();

	bool GotoFullscreen();
	void LeaveFullscreen();
	
	void ToggleCaptureCursor();

	char* GetFPS();
	CWtrCamera* GetCamera() { return &m_Camera; };

	void GetScreenrect(RECT* rc);

//////////////////////////////////////////////////////////////////////
// 3D stuff
//////////////////////////////////////////////////////////////////////
	void Goto3D();
	void Leave3D();

//////////////////////////////////////////////////////////////////////
// 2D stuff
//////////////////////////////////////////////////////////////////////
	void Goto2D();
	void Leave2D();
	int Init2DFont(HFONT hFont);

	void Draw2DRect(RECT* rc, float fColor[4]);
	void Draw2DText(int x, int y, float color[4], char* text, ...);
};

#endif
