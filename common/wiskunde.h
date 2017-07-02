#ifndef WISKUNDE_H
#define WISKUNDE_H

#include "math.h"

#pragma warning( disable : 4244 ) // conversion from 'double ' to 'float ', possible loss of data
#pragma warning( disable : 4305 ) // truncation from 'const double ' to 'float '

class Matrix;
class Vector;

//********************************************************************************//
// Wiskunde functies
//********************************************************************************//
class __declspec(dllexport) Wiskunde
{
public:
	static float PI();
	static float RAD2DEG(float radiant);
	static float DEG2RAD(float degrees);
	static Vector GetNormal(Vector V1, Vector V2, Vector V3);
	static Vector Cross(Vector V1, Vector V2);
	static float Dot(Vector V1, Vector V2);
	static Vector Normalize(Vector V);
};

//********************************************************************************//
// Vector class met functies
//********************************************************************************//
class __declspec(dllexport) Vector
{
public:
	float X;
	float Y;
	float Z;
public:
	Vector();
	Vector(float X, float Y, float Z);

	void Fill(float X, float Y, float Z);
	Vector Vectorize(Vector V);
	void Normalize();
	float Magnitude();

	void operator*=(Vector V);
	Vector operator*(Vector V);
	Vector operator*(float F);
	void operator/=(Vector V);
	Vector operator/(Vector V);
	Vector operator/(float F);
	void operator+=(Vector V);
	Vector operator+(Vector V);
	Vector operator+(float F);
	void operator-=(Vector V);
	Vector operator-(Vector V);
	Vector operator-(float F);
	void operator=(Vector V);

	bool Equals(Vector V);
};

//********************************************************************************//
// Matrix class met functies
//********************************************************************************//
class __declspec(dllexport) Matrix
{
private:
	float M[4][4];
public:
	Matrix();
	Matrix(float N[4][4]);
	const float At(int i, int j);

	void FillIndentity();
	void FillZero();
	void Fill(float N[][4]);
	void Get(float N[][4]);
	void TransPose();
	void MatrixTranslate(Vector V);
	void MatrixTranslateInv(Vector V);
	void MatrixScale(Vector V);
	void MatrixRotateXDeg(float X);
	void MatrixRotateYDeg(float Y);
	void MatrixRotateZDeg(float Z);

	Matrix operator*(Matrix M);
	Matrix operator/(Matrix M);
	Matrix operator+(Matrix M);
	Matrix operator-(Matrix M);
	float *operator[](int i);
	
	bool Equals(Matrix M);
};

//********************************************************************************//
// Plane class met functies
//********************************************************************************//
class __declspec(dllexport) Plane
{
protected:
	Vector normal;
	float distance;
public:
	Plane();
	Plane(Vector n, float d);
	Plane(Vector v1, Vector v2, Vector v3);

	void Init(Vector v1, Vector v2, Vector v3);

	Vector GetNormal();
	float GetDistance();
};

#include <windows.h>
//********************************************************************************//
// Color class met functies
//********************************************************************************//
class __declspec(dllexport) Color
{
protected:
	float R;
	float G;
	float B;
	float A;
public:
	Color();
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);

	void Set(float r, float g, float b);
	void Set(float r, float g, float b, float a);
	void Set(COLORREF color);
	void Set(float color[]);
	float GetR();
	float GetG();
	float GetB();
	float GetA();
	COLORREF Get();
	void Get(float color[]);
	float* GetP();
};

#endif