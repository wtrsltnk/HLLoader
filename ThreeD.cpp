// ThreeD.cpp: implementation of the CThreeD class.
//
//////////////////////////////////////////////////////////////////////

#include "ThreeD.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThreeD::CThreeD()
{
	this->m_hInstance			 = NULL;
	this->m_hParent				 = NULL;
	this->m_hDlg				 = NULL;
	this->m_dwResourceDlg		 = IDD_3D;

	this->rmf = NULL;
	this->ms3d = NULL;
	this->engine = NULL;
}

CThreeD::~CThreeD()
{
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
LRESULT CThreeD::BaseProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CThreeD *pDlg = 0;

	// Is it the first message?
	if (uMsg == WM_INITDIALOG)
	{
		// Get the object from the creation param
		pDlg = reinterpret_cast<CThreeD *>(lParam);
		pDlg->SetHandle(hDlg);

		// Set it in the Window param
		::SetWindowLong(hDlg, GWL_USERDATA, reinterpret_cast<long>(pDlg));
	}
	else
	{
		// Get the object from the window param
		pDlg = reinterpret_cast<CThreeD *>(::GetWindowLong(hDlg, GWL_USERDATA)); 
	}

	if (pDlg)
		pDlg->DlgProc(uMsg, wParam, lParam);

	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CThreeD::ShowModal(HINSTANCE hInst, HWND hParent)
{
	this->m_hInstance = hInst;
	this->m_hParent = hParent;

	return DialogBoxParam(hInst, MAKEINTRESOURCE(m_dwResourceDlg), hParent, (DLGPROC)BaseProc, (LPARAM)this);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CThreeD::ShowModalless(HINSTANCE hInst, HWND hParent)
{
	this->m_hInstance = hInst;
	this->m_hParent = hParent;

	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(m_dwResourceDlg), hParent, (DLGPROC)BaseProc, (LPARAM)this);
	ShowWindow(m_hDlg, SW_SHOW);
	
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Purpose : Set the handle of the created dialogwindow in this 
//           instance. Used in the wndproc of the clientwindowclass
// Input   : Handle of the dialogwindow created by this instance
// Output  : 
//////////////////////////////////////////////////////////////////////
void CThreeD::SetHandle(HWND hWnd)
{
	this->m_hDlg = hWnd;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CThreeD::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		{
			DEVMODE pDevmode;
			EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &pDevmode);
			engine = new CWtrEngine();
			if (engine)
			{
				engine->InitEngine(this->m_hDlg, &pDevmode, false, NULL);
				engine->GetCamera()->MoveForward(-20.0f);

				SetTimer(this->m_hDlg, 2, 10, NULL);
			}
			SetFocus(this->m_hDlg);
			break;
		}

	case WM_TIMER:
		{
			if (engine)
			{
				engine->PreRender();

				if (this->rmf)
				{
					this->rmf->DrawGl();
				}
				if (this->ms3d)
				{
					this->ms3d->DrawGl();
				}

				engine->PostRender();
			}
			break;
		}

	case WM_COMMAND:
		{
			switch (wParam)
			{
			case IDCANCEL:
			case IDOK:
				{
					EndDialog(m_hDlg, IDOK);
					break;
				}
			}
			break;
		}

	case WM_SIZE:
		{
			engine->Resize(LOWORD(lParam), HIWORD(lParam));
			break;
		}

	case 0x020A:
			engine->GetCamera()->MoveForward( ((short) HIWORD(wParam)) / 100);
	case WM_LBUTTONDOWN:
			CKeys::GetInstance()->ButtonDown(Left); break;
	case WM_LBUTTONUP:
			CKeys::GetInstance()->ButtonUp(Left); break;
	case WM_RBUTTONDOWN:
			CKeys::GetInstance()->ButtonDown(Right); break;
	case WM_RBUTTONUP:
			CKeys::GetInstance()->ButtonUp(Right); break;
	case WM_MBUTTONDOWN:
			CKeys::GetInstance()->ButtonDown(Middle); break;
	case WM_MBUTTONUP:
			CKeys::GetInstance()->ButtonUp(Middle); break;
	case WM_KEYUP:
			CKeys::GetInstance()->KeyUp(wParam); break;
	case WM_KEYDOWN:
		{
			if (wParam == 'Z')
			{
				engine->ToggleCaptureCursor();
			}
			CKeys::GetInstance()->KeyDown(wParam);
			break;
		}

	case WM_PAINT:
		{
			break;
		}

	case WM_CLOSE:
		{
			engine->Shutdown();
			EndDialog(m_hDlg, IDOK);
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CThreeD::SetRMF(CRMFFile* rmf)
{
	this->rmf = rmf;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CThreeD::SeMS3D(CMS3DFile* ms3d)
{
	this->ms3d = ms3d;
}
