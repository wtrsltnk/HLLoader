// Keys.cpp: implementation of the CKeys class.
//
//////////////////////////////////////////////////////////////////////

#include "keys.h"

//////////////////////////////////////////////////////////////////////
// Statics
//////////////////////////////////////////////////////////////////////
CKeys* CKeys::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKeys::CKeys(void)
{
	for (int i = 0; i < 255; i++)
		m_Keys[i] = false;
    for (int i = 0; i < 16; i++)
		m_Buttons[i] = false;
}

CKeys::~CKeys(void)
{
}

CKeys* CKeys::GetInstance()
{
	if (m_pInstance == NULL)
		m_pInstance = new CKeys();

	return m_pInstance;
}

void CKeys::KeyDown(int key)
{
	m_Keys[key] = true;
}

void CKeys::KeyUp(int key)
{
	m_Keys[key] = false;
}

bool CKeys::IsKey(int key)
{
	return m_Keys[key];
}

void CKeys::ButtonDown(int button)
{
	m_Buttons[button] = true;
}

void CKeys::ButtonUp(int button)
{
	m_Buttons[button] = false;
}

bool CKeys::IsButton(int button)
{
	return m_Buttons[button];
}
