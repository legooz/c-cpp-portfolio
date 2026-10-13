#pragma once

#include <string>

using namespace std;
class ArrayOutOfRange
{
public:
	int index;
	int getIndex() { return index; }
	ArrayOutOfRange(int index) { this->index = index; };
	
};



template<class T>
class CheckedArray
{
public:
	CheckedArray();
	CheckedArray(int size);
	~CheckedArray();
	T& operator[](int index) throw (ArrayOutOfRange);
	int length();
private:
	T* p;
	int size;
};

template<class T>
CheckedArray<T>::CheckedArray() : size(10)
{
	p = new T[size];
}

template<class T>
CheckedArray<T>::CheckedArray(int size) : size(size)
{
	p = new T[size];
}

template<class T>
CheckedArray<T>::~CheckedArray()
{
	delete[] p;
}

template<class T>
T& CheckedArray<T>::operator[](int index) throw(ArrayOutOfRange)
{
	if (index < 0 || index >= size)
	{
		throw ArrayOutOfRange(index);	
	}
	return p[index];
}

template<class T>
int CheckedArray<T>::length()
{
	return size;
}


