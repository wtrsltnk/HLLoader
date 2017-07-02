// WtrEngine.cpp: implementation of the CWtrEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "WtrEngine.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWtrEngine::CWtrEngine()
{
	m_hWnd = NULL;
	m_hDC = NULL;
    m_hRC = NULL;
	m_pDevmode = NULL;
	m_hFont = NULL;
}

CWtrEngine::~CWtrEngine()
{
	Shutdown();
}

int CWtrEngine::InitEngine(HWND hWnd, DEVMODE* pDevmode, bool fullscreen, HFONT hFont)
{
	if (hWnd == NULL)
		return ERR;

	if (pDevmode == NULL)
		return ERR;

	m_hWnd = hWnd;
	m_iWidth = pDevmode->dmPelsWidth;
	m_iHeight = pDevmode->dmPelsHeight;
	m_pDevmode = pDevmode;
	m_hFont = hFont;

	bool res = true;
	if (fullscreen)
		res = GotoFullscreen();

	if (!res)
		return ERR;

    m_hDC = GetDC(hWnd);

	InitPixelformat();

    m_hRC = wglCreateContext(m_hDC);
    wglMakeCurrent(m_hDC, m_hRC);

	InitTiming();
	InitFont();

	return OK;
}

int CWtrEngine::InitFont()
{
	m_iFont = glGenLists(FONT_RANGE);
    SelectObject(m_hDC, m_hFont);
    return wglUseFontBitmaps(m_hDC, 1, FONT_RANGE, m_iFont);
}

int CWtrEngine::InitPixelformat()
{
	PIXELFORMATDESCRIPTOR pfd;
    int format;

    ZeroMemory( &pfd, sizeof( pfd ) );
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    format = ChoosePixelFormat(m_hDC, &pfd);
    SetPixelFormat(m_hDC, format, &pfd);
	return OK;
}

int CWtrEngine::PreRender()
{
	float f[4][4];

	wglMakeCurrent(m_hDC, m_hRC);

	InitView();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	Goto3D();

	m_Camera.Update();

	m_Camera.GetViewmatrix(f);
	glLoadMatrixf(&f[0][0]);

	glScalef(0.1f, 0.1f, 0.1f);
	return OK;
}

int CWtrEngine::PostRender()
{
	Leave3D();
	SwapBuffers(m_hDC);
	
	FrameCount();

	return OK;
}

void CWtrEngine::Resize(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;

	InitView();

	POINT pt = {width / 2, height / 2};
	ClientToScreen(m_hWnd, &pt);
	m_Camera.SetCenter(pt.x, pt.y);
}

void CWtrEngine::InitView()
{
	wglMakeCurrent(m_hDC, m_hRC);

	glViewport(0, 0, m_iWidth, m_iHeight);
}

void CWtrEngine::Shutdown()
{
	wglMakeCurrent(NULL, NULL);

	if (m_hRC)
		wglDeleteContext(m_hRC);
	m_hRC = NULL;

    if (m_hWnd && m_hDC)
		ReleaseDC(m_hWnd, m_hDC);
	m_hWnd = NULL;
	m_hDC = NULL;

	LeaveFullscreen();
}

bool CWtrEngine::GotoFullscreen()
{
	int res = ChangeDisplaySettings(m_pDevmode, CDS_FULLSCREEN);

	if (res != DISP_CHANGE_SUCCESSFUL)
	{
		::MessageBox(m_hWnd, "Changing display resolution failed.", "ERROR:", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

void CWtrEngine::LeaveFullscreen()
{
	ChangeDisplaySettings(NULL,0);
}

void CWtrEngine::ToggleCaptureCursor()
{
	m_Camera.SetCaptureCursor(!m_Camera.GetCaptureCursor());
}

void CWtrEngine::Goto2D()
{
	Leave3D();

    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
    glPushMatrix();

    gluOrtho2D( 0.0, (GLdouble) m_iWidth, 0.0, (GLdouble) m_iHeight );

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void CWtrEngine::Leave2D()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glPopMatrix();

	Goto3D();
}

void CWtrEngine::Draw2DRect(RECT* rc, float fColor[4])
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(fColor[0], fColor[1], fColor[2], fColor[3]);
	glLineWidth(1.5f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRecti(rc->left, m_iHeight - rc->top, rc->right, m_iHeight - rc->bottom);
}

void CWtrEngine::Draw2DText(int x, int y, float color[4], char* text, ...)
{
    va_list argp;
    char result[256];

    va_start( argp, text );
    vsprintf( result, text, argp );
    va_end( argp );

	for (unsigned int i = 0; i < strlen(result); i++ )
		result[i] -= 1;
	
    glColor4f(color[0], color[1], color[2], color[3]);
    glRasterPos2i(x, m_iHeight-y-10);
    glListBase(m_iFont);
    glCallLists(strlen(result), GL_BYTE, result);
}

void CWtrEngine::Goto3D()
{
    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
    glPushMatrix();

	gluPerspective(45.0f,(GLfloat)m_iWidth/(GLfloat)m_iHeight,0.01f,300.0f);

	glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDisable(GL_BLEND);
	glLineWidth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
}

void CWtrEngine::Leave3D()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glPopMatrix();
}

int CWtrEngine::Init2DFont(HFONT hFont)
{
	int font = glGenLists(FONT_RANGE);
    SelectObject(m_hDC, hFont);
    if (wglUseFontBitmaps(m_hDC, 1, FONT_RANGE, m_iFont))
		return font;

	return 0;
}

void CWtrEngine::GetScreenrect(RECT* rc)
{
	if (!rc)
		return;

	rc->left = 0;
	rc->right = m_iWidth;
	rc->top = 0;
	rc->bottom = m_iHeight;
}

char* CWtrEngine::GetFPS()
{
	char* fps = new char[64];

	sprintf(fps, " fps : %d", m_nFrameRate);

	return fps;
}

void CWtrEngine::FrameCount()
{
	INT64 NewCount = 0;
	static INT64 LastCount = 0;
	INT64 Difference = 0;

	QueryPerformanceCounter( (LARGE_INTEGER*)&NewCount );
	
	m_nFrameCount++;
	
	Difference = NewCount - LastCount;
	
	if( Difference >= m_nFrequency )
	{
		m_nFrameRate = m_nFrameCount;
		m_nFrameCount = 0;

		LastCount = NewCount;
	}

	m_fFrameDeviance = (float)m_nFrameRate / 25.0f;

}

int CWtrEngine::InitTiming()
{
	QueryPerformanceFrequency( (LARGE_INTEGER*)&m_nFrequency );

	if( m_nFrequency == 0 )
	{
		return ERR;
	}
	return OK;
}