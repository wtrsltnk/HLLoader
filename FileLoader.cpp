// FileLoader.cpp: implementation of the CFileLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "FileLoader.h"
#include <commctrl.h>
#include <commdlg.h>
#include <shlobj.h>
#include <direct.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileLoader::CFileLoader(HWND hParent)
{
	this->hParent = hParent;
	this->bsp = NULL;
	this->map = NULL;
	this->rmf = NULL;
	this->wad = NULL;
	this->ms3d = NULL;
}

CFileLoader::~CFileLoader()
{
	CloseBSP();
	CloseMAP();
	CloseRMF();
	CloseWAD();
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CFileLoader::LoadBSP()
{
	bool res = true;
	char file[256];

	if (OpenFile(hParent, file, "BSP Files(*.bsp)\0*.bsp", "*.bsp"))
	{
		CloseBSP();

		this->bsp = new CBSPFile();

		HICON hIcon = SetCursor(LoadCursor(NULL, IDC_WAIT));
		if (!this->bsp->LoadBSPFile(file))
		{
			CloseBSP();
			res = false;
		}
		SetCursor(hIcon);

		InvalidateRect(hParent, NULL, TRUE);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CFileLoader::LoadMAP() throw()
{
	bool res = true;
	char file[256];

	if (OpenFile(hParent, file, "MAP Files(*.map)\0*.map", "*.map"))
	{
		CloseMAP();

		this->map= new CMAPFile();

		HICON hIcon = SetCursor(LoadCursor(NULL, IDC_WAIT));
		try
		{
			this->map->LoadMAPFile(file);
		}
		catch(char* err)
		{
			CloseMAP();
			SetCursor(hIcon);
			throw(err);
		}
		SetCursor(hIcon);

		InvalidateRect(hParent, NULL, TRUE);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CFileLoader::LoadRMF() throw()
{
	bool res = true;
	char file[256];

	if (OpenFile(hParent, file, "RMF Files(*.rmf)\0*.rmf", "*.rmf"))
	{
		CloseRMF();

		this->rmf = new CRMFFile();

		HICON hIcon = SetCursor(LoadCursor(NULL, IDC_WAIT));
		try
		{
			this->rmf->LoadRMFFile(file);
		}
		catch(char* err)
		{
			CloseRMF();
			SetCursor(hIcon);
			throw(err);
		}
		SetCursor(hIcon);

		InvalidateRect(hParent, NULL, TRUE);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CFileLoader::LoadWAD()
{
	bool res = true;
	char file[256];

	if (OpenFile(hParent, file, "WAD Files(*.wad)\0*.wad", "*.wad"))
	{
		CloseWAD();

		this->wad = new CWADFile();

		HICON hIcon = SetCursor(LoadCursor(NULL, IDC_WAIT));
		if (!this->wad->LoadWADFile(file))
		{
			CloseWAD();
			res = false;
		}
		SetCursor(hIcon);

		InvalidateRect(hParent, NULL, TRUE);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CFileLoader::LoadMS3D()
{
	bool res = true;
	char file[256];

	if (OpenFile(hParent, file, "MS3D Files(*.ms3d)\0*.ms3d", "*.ms3d"))
	{
		CloseMS3D();

		this->ms3d = new CMS3DFile();

		HICON hIcon = SetCursor(LoadCursor(NULL, IDC_WAIT));
		try
		{
			this->ms3d->LoadMS3DFile(file);
		}
		catch (...)
		{
			CloseMS3D();
			res = false;
		}
		SetCursor(hIcon);

		InvalidateRect(hParent, NULL, TRUE);
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::SaveBSPTextures()
{
	int count = 0;
	if (this->bsp)
	{
		char res[256];
		if (Directory(hParent, res))
		{
			for (int j = 0; j < this->bsp->GetNumTextures(); j++)
			{
				if (this->bsp->WriteBMP(res, j))
					count++;
			}

			if (count > 0)
				ShellExecute(hParent, "explore", res, 0, 0, SW_SHOW);
		}
	}
	return count;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::SaveBSPEntities()
{
	int res = 0;
	if (this->bsp)
	{
		char file[256];
		if (SaveFile(hParent, file, "ENT Files(*.ent)\0*.ent", "*.ent"))
		{
			if (this->bsp->WriteEntities(file))
				res = true;

			if (res)
				ShellExecute(hParent, "open", file, 0, 0, SW_SHOW);
		}
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::SaveMAPFile()
{
	int res = -1;

	if (this->map)
	{
		char file[256];
		if (SaveFile(hParent, file, "MAP Files(*.map)\0*.map", "*.map"))
		{
			if (this->map->SaveMAPFile(file))
				res = 1;
			else
				res = 0;

			if (res)
				ShellExecute(hParent, "open", file, 0, 0, SW_SHOW);
		}
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::SaveWADTextures()
{
	int count = 0;

	if (this->wad)
	{
		char res[256];
		if (Directory(hParent, res))
		{
			char* newdir = new char[256];
			sprintf(newdir, "%s\\%s", res, this->wad->GetFileName());
			
			_mkdir(newdir);
			for (int j = 0; j < this->wad->GetNumTextures(); j++)
			{
				if (this->wad->WriteBMP(newdir, j))
					count++;
			}

			if (count > 0)
				ShellExecute(hParent, "explore", newdir, 0, 0, SW_SHOW);
		}
	}
	return count;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CFileLoader::SaveMS3D()
{
	bool res = true;

	if (this->ms3d)
	{
		try
		{
			char file[256];
			if (SaveFile(hParent, file, "MS3D Files(*.ms3d)\0*.ms3d", "*.ms3d"))
			{
				//this->ms3d->SaveMS3DFile(file);
			}
		}
		catch (char* err)
		{
			::MessageBox(this->hParent, err, "ERROR :", MB_OK);
			res = false;
		}
	}
	else
		res = false;

	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::ShowRMF3D()
{
	CThreeD thr;

	thr.SetRMF(rmf);

	return thr.ShowModal(GetModuleHandle(NULL), this->hParent);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::ShowMS3D3D()
{
	CThreeD thr;

	thr.SeMS3D(ms3d);

	return thr.ShowModal(GetModuleHandle(NULL), this->hParent);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CFileLoader::CloseBSP()
{
	if (this->bsp)
	{
		this->bsp->Clear();
		delete this->bsp;
		this->bsp = NULL;
	}
	InvalidateRect(hParent, NULL, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CFileLoader::CloseMAP()
{
	if (this->map)
	{
		this->map->Clear();
		delete this->map;
		this->map = NULL;
	}
	InvalidateRect(hParent, NULL, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CFileLoader::CloseRMF()
{
	if (this->rmf)
	{
		this->rmf->Clear();
		delete this->rmf;
		this->rmf = NULL;
	}
	InvalidateRect(hParent, NULL, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CFileLoader::CloseWAD()
{
	if (this->wad)
	{
		this->wad->Clear();
		delete this->wad;
		this->wad = NULL;
	}
	InvalidateRect(hParent, NULL, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CFileLoader::CloseMS3D()
{
	if (this->ms3d)
	{
		this->ms3d->Clear();
		delete this->ms3d;
		this->ms3d = NULL;
	}
	InvalidateRect(hParent, NULL, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::DrawBSP(HDC hdc, int x, int y)
{
	char* tex;
	char str[256];
	int h = 0;

	if (this->bsp)
	{
		COLORREF old = SetTextColor(hdc, 0xff8800);

		strcpy(str, this->bsp->GetFileName());
		TextOut(hdc, x, y + h, str, strlen(str));
		h+=20;
		
		SetTextColor(hdc, 0x3399dd);

		for (int i = 0; i < this->bsp->GetNumWadfiles(); i++)
		{
			tex = this->bsp->GetWadfilePath(i);
			TextOut(hdc, x + 10, y + h, tex, strlen(tex));
			h+=20;
		}
		
		SetTextColor(hdc, 0x009977);

		for (int j = 0; j < this->bsp->GetNumTextures(); j++)
		{
			tex = this->bsp->GetTextureName(j);
			TextOut(hdc, x + 10, y + h, tex, strlen(tex));
			h+=20;
		}
		
		SetTextColor(hdc, 0x888888);

		for (int k = 0; k < this->bsp->GetNumEntities(); k++)
		{
			tex = this->bsp->GetEntity(k)->ToString();
			TextOut(hdc, x + 10, y + h, tex, strlen(tex));
			h+=20;
		}

		SetTextColor(hdc, old);
	}
	return h;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::DrawMAP(HDC hdc, int x, int y)
{
	char* tex;
	char str[256];
	int h = 0;

	if (this->map)
	{
		COLORREF old = SetTextColor(hdc, 0xff8800);

		strcpy(str, this->map->GetFileName());
		TextOut(hdc, x, y + h, str, strlen(str));
		h+=20;
		
		SetTextColor(hdc, 0x3399dd);

		for (int i = 0; i < this->map->GetNumWadfiles(); i++)
		{
			tex = this->map->GetWadfilePath(i);
			TextOut(hdc, x + 10, y + h, tex, strlen(tex));
			h+=20;
		}
		
		SetTextColor(hdc, 0x009977);

		for (int j = 0; j < this->map->GetNumTextures(); j++)
		{
			tex = this->map->GetTexture(j);
			TextOut(hdc, x + 10, y + h, tex, strlen(tex));
			h+=20;
		}
		
		SetTextColor(hdc, 0x888888);

		for (int k = 0; k < this->map->GetNumEntities(); k++)
		{
			tex = this->map->GetEntity(k)->ToString();
			TextOut(hdc, x + 10, y + h, tex, strlen(tex));
			h+=20;
		}

		SetTextColor(hdc, old);
	}
	return h;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::DrawRMF(HDC hdc, int x, int y)
{
	char* tex;
	char str[256];
	int h = 0;

	if (this->rmf)
	{
		COLORREF old = SetTextColor(hdc, 0xff8800);

		strcpy(str, this->rmf->GetFileName());
		TextOut(hdc, x, y + h, str, strlen(str));
		h+=20;
		
		SetTextColor(hdc, 0x3399dd);

		for (int i = 0; i < this->rmf->GetNumVisGroups(); i++)
		{
			tex = this->rmf->GetVisGroupName(i);
			TextOut(hdc, x + 10, y + h, tex, strlen(tex));
			h+=20;
		}

		CRMFEntity* worldspawn = this->rmf->GetWorldSpawn();
		CRMFKey* wads = worldspawn->GetKey("wad");
		if (wads)
		{
			tex = wads->GetValue();
			TextOut(hdc, x + 10, y + h, tex, strlen(tex));
			h+=20;
		}

		SetTextColor(hdc, old);
	}
	return h;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::DrawWAD(HDC hdc, int x, int y)
{
	char str[256];
	int h = 0;

	if (this->wad)
	{
		COLORREF old = SetTextColor(hdc, 0x0088ff);

		strcpy(str, this->wad->GetFileName());
		TextOut(hdc, x, y + h, str, strlen(str));
		h+=20;
		
		SetTextColor(hdc, 0x009977);

		for (int i = 0; i < this->wad->GetNumTextures(); i++)
		{
			char* res = this->wad->GetTextureName(i);
			TextOut(hdc, x + 10, y + h, res, strlen(res));
			h+=20;
		}

		SetTextColor(hdc, old);
	}
	return h;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CFileLoader::DrawMS3D(HDC hdc, int x, int y)
{
	char str[256];
	int h = 0;

	if (this->ms3d)
	{
		COLORREF old = SetTextColor(hdc, 0x0088ff);

		strcpy(str, this->ms3d->GetFileName());
		TextOut(hdc, x, y + h, str, strlen(str));
		h+=20;
		
		SetTextColor(hdc, 0x009977);

		for (int i = 0; i < this->ms3d->GetNumGroups(); i++)
		{
			char* res = this->ms3d->GetGroup(i);
			TextOut(hdc, x + 10, y + h, res, strlen(res));
			h+=20;
		}
		
		SetTextColor(hdc, 0x3399dd);

		for (int j = 0; j < this->ms3d->GetNumMaterials(); j++)
		{
			char* res = this->ms3d->GetMaterial(j);
			TextOut(hdc, x + 10, y + h, res, strlen(res));
			h+=20;
		}

		SetTextColor(hdc, old);
	}
	return h;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CWADMiptex* CFileLoader::GetBSPTetxure(int index)
{
	if (this->bsp)
	{
		if (this->bsp->GetNumTextures() > index)
		{
			return this->bsp->GetMiptex(index);
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
CWADMiptex* CFileLoader::GetWADTetxure(int index)
{
	if (this->wad)
	{
		if (this->wad->GetNumTextures() > index)
		{
			return this->wad->GetMiptex(index);
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CFileLoader::OpenFile(HWND hOwner, char* result, char *szFilter, char *szDefExt)
{
	OPENFILENAME ofn = {0};
	char szFile[MAX_PATH+1] =	{0};
	
	ofn.Flags             = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
	ofn.hwndOwner         = hOwner;
	ofn.lpstrCustomFilter = 0;
	ofn.lpstrFile         = szFile;
	ofn.lpstrFileTitle    = 0;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrDefExt		  = szDefExt;
	ofn.lpstrInitialDir   = 0;
	ofn.lpstrTitle        = "Open a file...";
	ofn.lStructSize       = sizeof( OPENFILENAME );
	ofn.nMaxFile          = MAX_PATH;


	if( GetOpenFileName( &ofn ) != 0 )
	{
		for ( int i = 0; i < (int)strlen( ofn.lpstrFile ); i++ )
		{
			result[i] = ofn.lpstrFile[i];
			if ( ofn.lpstrFile[i] == '\\' )
				result[i] = '/';
		}
		result[i]='\0';
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
bool CFileLoader::SaveFile(HWND hOwner, char* result, char *szFilter, char *szDefExt)
{
	OPENFILENAME ofn = {0};
	char szFile[MAX_PATH+1] =	{0};
	
	ofn.Flags             = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
	ofn.hwndOwner         = hOwner;
	ofn.lpstrCustomFilter = 0;
	ofn.lpstrFile         = szFile;
	ofn.lpstrFileTitle    = 0;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrDefExt		  = szDefExt;
	ofn.lpstrInitialDir   = 0;
	ofn.lpstrTitle        = "Save a file...";
	ofn.lStructSize       = sizeof( OPENFILENAME );
	ofn.nMaxFile          = MAX_PATH;


	if( GetSaveFileName( &ofn ) != 0 )
	{
		for ( int i = 0; i < (int)strlen( ofn.lpstrFile ); i++ )
		{
			result[i] = ofn.lpstrFile[i];
			if ( ofn.lpstrFile[i] == '\\' )
				result[i] = '/';
		}
		result[i]='\0';
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CFileLoader::Directory(HWND hOwner, char* result)
{
	BROWSEINFO bi;
    ITEMIDLIST *pidl;
    char mydir[MAX_PATH];

    bi.hwndOwner = hOwner;
    bi.pidlRoot = 0;
    bi.pszDisplayName = mydir;
    bi.lpszTitle = "Find a directory...";
    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
    bi.lpfn = 0;
    bi.lParam = 0;

    pidl=SHBrowseForFolder(&bi);

    if ( SHGetPathFromIDList(pidl, mydir) )
	{
		for ( int i = 0; i < (int)strlen( mydir ); i++ )
		{
			result[i] = mydir[i];
			if ( mydir[i] == '\\' )
				result[i] = '/';
		}
		result[i]='\0';
		return true;
	}
	return false;
}