// WtrCamera.cpp: implementation of the CWtrCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "WtrCamera.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWtrCamera::CWtrCamera()
{
	Reset();
	m_iCenterX = 0;
	m_iCenterY = 0;
	m_bCaptureCursor = false;
}

CWtrCamera::~CWtrCamera()
{
}

void CWtrCamera::Reset()
{
	m_Viewmatrix.FillIndentity();
	m_Position.Fill(0.0f, 0.0f, -4.0f);

	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fYaw = 0.0f;

	m_fVelocityX = 0.0f;
	m_fVelocityY = 0.0f;
	m_fVelocityZ = 0.0f;
}

void CWtrCamera::BuildViewmatrix()
{
	Matrix pitch, roll, yaw, pos;

	pitch.MatrixRotateXDeg(m_fPitch);
	roll.MatrixRotateYDeg(m_fRoll);
	yaw.MatrixRotateZDeg(m_fYaw);

	pos.MatrixTranslateInv(m_Position);

	m_Viewmatrix = pitch * roll * yaw * pos;
}

void CWtrCamera::Update()
{
	CalculateFrameInterval();

	CalculateMovement();

	if (m_fVelocityZ != 0)
		MoveForward(m_fFrameInterval * m_fVelocityZ);
	if (m_fVelocityX != 0)
		MoveRight(m_fFrameInterval * m_fVelocityX);
	if (m_fVelocityY != 0)
		MoveUp(m_fFrameInterval * m_fVelocityY);
	
	BuildViewmatrix();

	if (m_bCaptureCursor) CalculateRotation();
}

void CWtrCamera::CalculateMovement()
{
//*
	if (m_fVelocityX < -SPEED_REDUCE) m_fVelocityX += SPEED_REDUCE;
	else if (m_fVelocityX > SPEED_REDUCE) m_fVelocityX -= SPEED_REDUCE;
	else m_fVelocityX = 0;

	if (m_fVelocityY < -SPEED_REDUCE) m_fVelocityY += SPEED_REDUCE;
	else if (m_fVelocityY > SPEED_REDUCE) m_fVelocityY -= SPEED_REDUCE;
	else m_fVelocityY = 0;

	if (m_fVelocityZ < -SPEED_REDUCE) m_fVelocityZ += SPEED_REDUCE;
	else if (m_fVelocityZ > SPEED_REDUCE) m_fVelocityZ -= SPEED_REDUCE;
	else m_fVelocityZ = 0;
//*/
	if (CKeys::GetInstance()->IsKey('W'))
		m_fVelocityZ = SPEED;

	if (CKeys::GetInstance()->IsKey('S'))
		m_fVelocityZ = -SPEED;

	if (CKeys::GetInstance()->IsKey('A'))
		m_fVelocityX = SPEED;

	if (CKeys::GetInstance()->IsKey('D'))
		m_fVelocityX = -SPEED;
}

void CWtrCamera::CalculateRotation()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	if( (mousePos.x == m_iCenterX) && (mousePos.y == m_iCenterY) ) return;
	SetCursorPos(m_iCenterX, m_iCenterY);

	Roll((m_iCenterX - mousePos.x) / 2);
	Pitch((m_iCenterY - mousePos.y) / 2);
}

void CWtrCamera::CalculateFrameInterval()
{
	static float frameTime = 0;
    float currentTime;

	currentTime = (float)timeGetTime() / 100;	

 	m_fFrameInterval = currentTime - frameTime;

	frameTime = currentTime;
}

void CWtrCamera::GetViewmatrix(float viewmatrix[4][4])
{
	BuildViewmatrix();
	
	m_Viewmatrix.TransPose();
	m_Viewmatrix.Get(viewmatrix);
}

void CWtrCamera::MoveForward(float units)
{
	if (units != 0)
	{
		m_Position.X -= m_Viewmatrix.At(0, 2) * units;
		m_Position.Y -= m_Viewmatrix.At(1, 2) * units;
		m_Position.Z -= m_Viewmatrix.At(2, 2) * units;
	}
}

void CWtrCamera::MoveRight(float units)
{
	if (units != 0)
	{
		m_Position.X -= m_Viewmatrix.At(0, 0) * units;
		m_Position.Y -= m_Viewmatrix.At(1, 0) * units;
		m_Position.Z -= m_Viewmatrix.At(2, 0) * units;
	}
}

void CWtrCamera::MoveUp(float units)
{
	if (units != 0)
	{
		m_Position.X -= m_Viewmatrix.At(0, 1) * units;
		m_Position.Y -= m_Viewmatrix.At(1, 1) * units;
		m_Position.Z -= m_Viewmatrix.At(2, 1) * units;
	}
}

void CWtrCamera::MoveX(float units)
{
	if (units != 0)
	{
		m_Position.X += units;
		BuildViewmatrix();
	}
}

void CWtrCamera::MoveY(float units)
{
	if (units != 0)
	{
		m_Position.Y += units;
		BuildViewmatrix();
	}
}

void CWtrCamera::MoveZ(float units)
{
	if (units != 0)
	{
		m_Position.Z += units;
		BuildViewmatrix();
	}
}

void CWtrCamera::Pitch(float degrees)
{
	if (degrees != 0)
	{
		m_fPitch += (degrees / 2);
		if (m_fPitch > 90)
			m_fPitch = 90;
		else if (m_fPitch < -90)
			m_fPitch = -90;
		BuildViewmatrix();
	}
}

void CWtrCamera::Roll(float degrees)
{
	if (degrees != 0)
	{
		m_fRoll += degrees;
		BuildViewmatrix();
	}
}

void CWtrCamera::Yaw(float degrees)
{
	if (degrees != 0)
	{
		m_fYaw += degrees;
		BuildViewmatrix();
	}
}

void CWtrCamera::SetCenter(int x, int y)
{
	m_iCenterX = x;
	m_iCenterY = y;
}

void CWtrCamera::SetCaptureCursor(bool value)
{
	m_bCaptureCursor = value;

	if (value == true)
	{
		m_fPitch = 0.0f;
		m_fRoll = 0.0f;
		m_fYaw = 0.0f;

//		ShowCursor(FALSE);
		SetCursorPos(m_iCenterX, m_iCenterY);
	}
//	else
//		ShowCursor(TRUE);
}

bool CWtrCamera::GetCaptureCursor()
{
	return m_bCaptureCursor;
}

