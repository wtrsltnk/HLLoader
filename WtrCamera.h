// WtrCamera.h: interface for the CWtrCamera class.
//
//////////////////////////////////////////////////////////////////////

#ifndef WTRCAMERA_H
#define WTRCAMERA_H

#include "common/wiskunde.h"
#include "Keys.h"

#define SPEED 1.0f
#define SPEED_REDUCE 0.5f

class __declspec(dllexport) CWtrCamera  
{
private:
	Matrix m_Viewmatrix;
	Vector m_Position;

	float m_fPitch;
	float m_fRoll;
	float m_fYaw;

	float m_fVelocityX;
	float m_fVelocityY;
	float m_fVelocityZ;

	float m_fFrameInterval;

	int m_iCenterX, m_iCenterY;
	bool m_bCaptureCursor;

	void Reset();
	void BuildViewmatrix();
	void CalculateMovement(); 
	void CalculateRotation();
	void CalculateFrameInterval();
public:
	CWtrCamera();
	virtual ~CWtrCamera();

	void MoveForward(float units);
	void MoveRight(float units);
	void MoveUp(float units);

	void MoveX(float units);
	void MoveY(float units);
	void MoveZ(float units);

	void Pitch(float degrees);
	void Roll(float degrees);
	void Yaw(float degrees);

	void GetViewmatrix(float viewmatrix[4][4]);
	void Update();
	void SetCenter(int x, int y);
	void SetCaptureCursor(bool value);
	bool GetCaptureCursor();
};

#endif
