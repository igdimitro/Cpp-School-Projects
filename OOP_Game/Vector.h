#pragma once
#include <iostream>

template<typename T>
class Vector
{
private:
	T* data;
	int allocatedSize;
	int usedSize;

	void free();
	void copyFrom(const Vector<T>&);
	void reallocate(int);
public:

	Vector();
	Vector(const Vector<T>&);
	Vector<T>& operator=(const Vector<T>&);
	~Vector();

public:
	void resize(int);
	int getUsedSize() const;
	void pushBack(T);
	T& operator[](int index);
	const T& operator[](int index) const;
};

template<typename T>
void Vector<T>::free()
{
	delete [] data;
	data = NULL;
	allocatedSize = 0;
	usedSize = 0;
}

template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	try
	{
		data = new T[other.allocatedSize];
		for(size_t i = 0; i < other.usedSize; i++)
			data[i] = other.data[i];

		allocatedSize = other.allocatedSize;
		usedSize = other.usedSize;
	}
	catch(std::bad_alloc e)
	{
		std::cout << e.what();
	}
	
}

template<typename T>
void Vector<T>::resize(int newSize)
{
	reallocate(newSize);
	usedSize = newSize;
}

template<typename T>
void Vector<T>::reallocate(int newSize)
{
	if(newSize < allocatedSize) //is this ever going to happen?!?
	{
		//do something
	}
	try
	{
		T* temp = new T[newSize];
		for(size_t i = 0; i < usedSize; i++)
			temp[i] = data[i];

		delete [] data;
		data = temp;
		allocatedSize = newSize;
	}
	catch(std::bad_alloc e)
	{
		std::cout << e.what() << std::endl;
	}
	

}

template<typename T>
Vector<T>::Vector()
{
	data = NULL;
	allocatedSize = 0;
	usedSize = 0;
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if(this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	free();
}

template<typename T>
T& Vector<T>::operator[](int index)
{
	if(index < 0 || index > usedSize)
		throw "Index out of range!\n";

	return data[index];
}

template<typename T>
const T& Vector<T>::operator[](int index) const
{
	if(index < 0 || index > usedSize)
		throw "Index out of range!\n";

	return data[index];
}

template<typename T>
int Vector<T>::getUsedSize() const
{
	return usedSize;
}

template<typename T>
void Vector<T>::pushBack(T elem)
{
	if(usedSize >= allocatedSize)
	{
		int newSize = (allocatedSize == 0 ? 2 : allocatedSize*2);
		reallocate(newSize);
	}
	data[usedSize] = elem;
	usedSize++;
}