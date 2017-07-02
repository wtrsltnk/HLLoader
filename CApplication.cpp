#include "CApplication.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CApplication::CApplication()
{
	this->m_hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_HL));
	this->m_strWindowTitle = "Half-Life Loader : BSP, WAD";

	this->pFileLoader = NULL;

	m_hRightClickMenu = CreatePopupMenu();
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MOPENBSP, "Open BSP");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MOPENMAP, "Open MAP");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MOPENRMF, "Open RMF");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MOPENWAD, "Open WAD");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MOPENMS3D, "Open MS3D");
	AppendMenu(m_hRightClickMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MCLOSEBSP, "Close BSP");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MCLOSEMAP, "Close MAP");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MCLOSERMF, "Close RMF");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MCLOSEWAD, "Close WAD");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MCLOSEMS3D, "Close MS3D");
	AppendMenu(m_hRightClickMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MSAVEBSPTEX, "Save BSP textures");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MSAVEBSPENT, "Save BSP entities");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MSAVEMAP, "Save MAP file");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MSAVEWADTEX, "Save WAD textures");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MSAVEMS3D, "Save MS3D file");
	AppendMenu(m_hRightClickMenu, MF_SEPARATOR, 0, 0);
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MSHOWRMF, "Show RMF 3D");
	AppendMenu(m_hRightClickMenu, MF_STRING, ID_MSHOWMS3D, "Show MS3D 3D");
}


CApplication::~CApplication()
{
	if (this->pFileLoader)
		delete this->pFileLoader;
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

LRESULT CApplication::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static int x = 10;
	static int y = 20;

	char str[256];

	switch (uMsg)
	{
	case WM_CREATE:
		{
			this->pFileLoader = new CFileLoader(hWnd);
			break;
		}

	case WM_LBUTTONDOWN:
		{
			break;
		}

	case WM_RBUTTONDOWN:
		{
			POINT pt;
			GetCursorPos(&pt);
			TrackPopupMenu(m_hRightClickMenu, TPM_LEFTALIGN | TPM_TOPALIGN, pt.x, pt.y, NULL, hWnd, NULL);
			break;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_MOPENBSP:
				{
					if (!this->pFileLoader->LoadBSP())
						::MessageBox(hWnd, "Kan de BSP file niet openen", "ERROR:", MB_OK);
					break;
				}
			case ID_MOPENMAP:
				{
					try
					{
						this->pFileLoader->LoadMAP();
					}
					catch(char* err)
					{
						::MessageBox(hWnd, err, "ERROR:", MB_OK);
					}
					break;
				}
			case ID_MOPENRMF:
				{
					try
					{
						this->pFileLoader->LoadRMF();
					}
					catch(char* err)
					{
						::MessageBox(hWnd, err, "ERROR:", MB_OK);
					}
					break;
				}
			case ID_MOPENWAD:
				{
					if (!this->pFileLoader->LoadWAD())
						::MessageBox(hWnd, "Kan de WAD file niet openen", "ERROR:", MB_OK);
					break;
				}
			case ID_MOPENMS3D:
				{
					if (!this->pFileLoader->LoadMS3D())
						::MessageBox(hWnd, "Kan de MS3D file niet openen", "ERROR:", MB_OK);
					break;
				}
			case ID_MCLOSEBSP:
				{
					this->pFileLoader->CloseBSP();
					break;
				}
			case ID_MCLOSEMAP:
				{
					this->pFileLoader->CloseMAP();
					break;
				}
			case ID_MCLOSERMF:
				{
					this->pFileLoader->CloseRMF();
					break;
				}
			case ID_MCLOSEWAD:
				{
					this->pFileLoader->CloseWAD();
					break;
				}
			case ID_MCLOSEMS3D:
				{
					this->pFileLoader->CloseMS3D();
					break;
				}
			case ID_MSAVEBSPTEX:
				{
					int num = this->pFileLoader->SaveBSPTextures();

					if (num == -1)
						::MessageBox(hWnd, "Er is geen BSP file geladen", "ERROR:", MB_OK|MB_ICONEXCLAMATION);
					else if (num == 0)
						::MessageBox(hWnd, "Er zitten geen textures in deze BSP file.", "Resultaat:", MB_OK);
					else
					{
						sprintf(str, "%i textures opgeslagen...", num);
						::MessageBox(hWnd, str, "Resultaat:", MB_OK);
					}
					break;
				}
			case ID_MSAVEBSPENT:
				{
					int num = this->pFileLoader->SaveBSPEntities();

					if (num == 0)
						::MessageBox(hWnd, "Het opslaan van de entities is niet gelukt.", "ERROR:", MB_OK|MB_ICONEXCLAMATION);
					else
						::MessageBox(hWnd, "Entities opgeslagen.", "Resultaat:", MB_OK);
					break;
				}
			case ID_MSAVEMAP:
				{
					int num = this->pFileLoader->SaveMAPFile();

					if (num == -1)
						::MessageBox(hWnd, "Er is geen MAP file geladen", "ERROR:", MB_OK|MB_ICONEXCLAMATION);
					else if (num == 0)
						::MessageBox(hWnd, "Het opslaan van de MAPfile is mislukt.", "ERROR:", MB_OK|MB_ICONEXCLAMATION);
					else
						::MessageBox(hWnd, "Mapfile opgeslagen.", "Resultaat:", MB_OK);
					break;
				}
			case ID_MSAVEWADTEX:
				{
					int num = this->pFileLoader->SaveWADTextures();

					if (num == -1)
						::MessageBox(hWnd, "Er is geen WAD file geladen", "ERROR:", MB_OK|MB_ICONEXCLAMATION);
					else if (num == 0)
						::MessageBox(hWnd, "Er zitten geen textures in deze WAD file.", "Resultaat:", MB_OK);
					else
					{
						sprintf(str, "%i textures opgeslagen...", num);
						::MessageBox(hWnd, str, "Resultaat:", MB_OK);
					}
					break;
				}

			case ID_MSAVEMS3D:
				{
					this->pFileLoader->SaveMS3D();
					break;
				}

			case ID_MSHOWRMF:
				{
					this->pFileLoader->ShowRMF3D();
					break;
				}

			case ID_MSHOWMS3D:
				{
					this->pFileLoader->ShowMS3D3D();
					break;
				}
			}
			break;
		}

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(hWnd, &ps);
				
				int add = 0;
				DrawLine(ps.hdc, x, y-10);

				int h = this->pFileLoader->DrawBSP(ps.hdc, x, y + add);
				add += h;
				if (h)
				{
					DrawLine(ps.hdc, x, y + add + 10);
					add += 20;
				}
				int w = this->pFileLoader->DrawWAD(ps.hdc, x, y + add);
				add += w;
				if (w)
				{
					DrawLine(ps.hdc, x, y + add + 10);
					add += 20;
				}
				int m = this->pFileLoader->DrawMAP(ps.hdc, x, y + add);
				add += m;
				if (m)
				{
					DrawLine(ps.hdc, x, y + add + 10);
					add += 20;
				}
				int r = this->pFileLoader->DrawRMF(ps.hdc, x, y + add);
				add += r;
				if (r)
				{
					DrawLine(ps.hdc, x, y + add + 10);
					add += 20;
				}
				int d = this->pFileLoader->DrawMS3D(ps.hdc, x, y + add);
				add += d;
				if (d)
				{
					DrawLine(ps.hdc, x, y + add + 10);
				}
			EndPaint(hWnd, &ps);
			break;
		}

	case 0x020A:
		{
			short zDelta = (short) HIWORD(wParam);    
			if (zDelta < 0)
				y-=20;
			else
				y+=20;

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

	case WM_KEYDOWN:
		{
			switch (LOWORD(wParam))
			{
			case VK_LEFT:
				{
					x+=20;
					break;
				}
			case VK_RIGHT:
				{
					x-=20;
					break;
				}
			case VK_UP:
				{
					y+=20;
					break;
				}
			case VK_DOWN:
				{
					y-=20;
					break;
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
	}
	return CWin::MsgProc(hWnd, uMsg, wParam, lParam);
}

void CApplication::DrawLine(HDC hdc, int x, int y)
{
	RECT rc;
	GetClientRect(m_hWnd, &rc);

	HPEN hLine = CreatePen(PS_SOLID, 3, 0x88000);
	HPEN hPen = (HPEN)SelectObject(hdc, hLine);
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x + rc.right - 20, y);
	SelectObject(hdc, hPen);
}