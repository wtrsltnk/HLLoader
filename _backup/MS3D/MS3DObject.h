// MS3DObject.h: interface for the CMS3DObject class.
//
//////////////////////////////////////////////////////////////////////

#ifndef MS3DOBJECT_H
#define MS3DOBJECT_H

class CMS3DObject  
{
public:
	enum MS3DObjectType
	{
		Object = 0,
		Vertex = 1,
		Triangle = 2,
		Material = 3,
		Group = 4,
		Joint = 5
	};

public:
	CMS3DObject();
	virtual ~CMS3DObject();

	virtual MS3DObjectType GetType();
	virtual void Clear() = 0;
	virtual void DrawGl() = 0;

};

#endif
