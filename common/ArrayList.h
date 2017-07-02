/* CArrayList Template
   written by Jared Bruni
   www.LostSideDead.com

  "Open Source, Open Mind"
*/

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <string.h>

template <class type>
class CArrayList
{
public:
	CArrayList();
	CArrayList(unsigned int size);
	~CArrayList();
	type operator[](unsigned int pos);
	bool Resize(unsigned int size);
	bool Remove(unsigned int pos);
	void Add(type t);
	void Asn(unsigned int pos, type t);
 	type Get(unsigned int pos);
	unsigned long Length();
private:
	type* array;
	unsigned long size;
	unsigned long i;
};

template<class type>
CArrayList<type>::CArrayList()
{
	array = 0;
	size = 0;
}

template <class type>
CArrayList<type>::CArrayList(unsigned int sizex)
{
	size = sizex;
	array = new type[ size ];
}

template <class type>
CArrayList<type>::~CArrayList()
{
	if( array != 0 )
	{
		delete [] array;
		array = 0;
	}
}

template <class type>
type CArrayList<type>::operator [](unsigned int pos)
{
	if( pos > size || pos < 0 && array != 0 ) { return 0; }
	return array[pos];
}

template <class type>
bool CArrayList<type>::Resize(unsigned int sizex)
{
	type* temp = new type[ size ];
	for(i = 0; i < size; i++)
	{
		temp[i] = array[i];
	}
	
	if(array != 0)
	{

		delete [] array;

		array = 0;

	}

	array = new type [ sizex ];
	for(i = 0; i < size; i++)
	{
		if(i < sizex) 
		{
			array[i] = temp[i];
		}
	}

	delete [] temp;
	temp = 0;
	size = sizex;

	return true;
}

template <class type>
bool CArrayList<type>::Remove(unsigned int pos)
{
	type* temp = new type[ size ];
	memset(temp, 0, sizeof(temp));

	int j = 0;
	unsigned int newsize = size;
	for(i = 0; i < size; i++)
	{
		if (i != pos)
		{
			temp[j] = array[i];
			j++;
		}
		else
		{
			newsize--;
		}
	}

	if (newsize == size)
		return false;
	
	if(array != 0)
	{

		delete [] array;

		array = 0;

	}
	
	size = newsize;
	array = new type [ size ];
	i = 0;
	for (i = 0; i < size; i++)
	{
		array[i] = temp[i];
	}

	delete [] temp;
	temp = 0;

	return true;
}

template <class type>
void CArrayList<type>::Add(type t)
{
	int size2 = size + 1;
	Resize(size2);
	array[size2-1] = t;
}

template<class type>
unsigned long CArrayList<type>::Length()
{
	return size;
}

template<class type>
void CArrayList<type>::Asn(unsigned int pos, type t)
{
	if(pos < size && pos >= 0) 
	{
		delete array[pos];
		array[pos] = t;
	}
}

template<class type>
type CArrayList<type>::Get(unsigned int pos)
{
	return this[pos];
}

#endif