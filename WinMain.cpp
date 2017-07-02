// WinClass.cpp : Defines the entry point for the application.
//
#include "CApplication.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	CApplication app;

	if (!app.Create())
		return 0;
	
	return app.Run();
}
