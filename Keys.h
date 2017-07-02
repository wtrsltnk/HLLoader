// Keys.h: interface for the CKeys class.
//
//////////////////////////////////////////////////////////////////////

#ifndef KEYS_H
#define KEYS_H

#include <windows.h>

enum
{
	Left = 0,
	Right,
	Middle,
	Mouse1,
	Mouse2,
	Mouse3
};

class __declspec(dllexport) CKeys
{
private:
	bool m_Keys[255];
	bool m_Buttons[16];

	static CKeys* m_pInstance;
public:
	CKeys(void);
	virtual ~CKeys(void);

	static CKeys* GetInstance();

	void KeyDown(int key);
	void KeyUp(int key);
	bool IsKey(int key);

	void ButtonDown(int button);
	void ButtonUp(int button);
	bool IsButton(int button);
};

#endif