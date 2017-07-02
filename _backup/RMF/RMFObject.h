// RMFObject.h: interface for the CRMFObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef RMFOBJECT_H
#define RMFOBJECT_H

class CRMFObject  
{
public:
	enum ObjectType
	{
		Object = 0,
		Solid = 1,
		Entity = 2,
		Group = 3,
		Face = 4,
		Path = 5
	};

	CRMFObject();
	virtual ~CRMFObject();
public:

	virtual ObjectType GetType();
	virtual void Clear() = 0;
	virtual void DrawGl() = 0;
};

#endif
