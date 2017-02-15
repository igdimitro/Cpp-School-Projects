#include <iostream>
#include "String.h"

void String::free()
{
	delete [] this->data;
	this->data = NULL;
	this->length = 0;
	this->capacity = 0;
}

void String::copyFrom(const String& other)
{
	try
	{
		if(other.capacity == other.length)
			this->data = new char[other.capacity + 1]; //for '\0'
		else
			this->data = new char[other.length + 1];
		this->length = other.length;
		this->capacity = other.capacity;
		for(size_t i = 0; i < other.length; i++)
			this->data[i] = other.data[i];
		this->data[length] = '\0';
		//strcpy_s(this->data, other.length + 1, other.data); // undefined behaviour if this->data and other->data overlap?!?!
	}
	catch(std::bad_alloc e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void String::cstringInit(const char* text)
{
	try
	{
		int textLenght = strlen(text);
		this->data = new char[textLenght + 1]; // + 1 for null terminator
		this->length = textLenght;
		this->capacity = textLenght;
		for(size_t i = 0; i < textLenght; i++)
			this->data[i] = text[i];
		this->data[textLenght] = '\0';		
	//	strcpy_s(this->data, textLenght + 1, text);
	}
	catch(std::bad_alloc e)
	{
		std::cerr << e.what() << std::endl;
	}
}

String::String()
{
	this->data = NULL;
	this->length = 0;
	this->capacity = 0;
}

String::String(const String& other)
{
	copyFrom(other);
}

String& String::operator=(const String& other)
{
	if(this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

String::~String()
{
	free();
}

String& String::operator=(const char* text)
{
	int textLength = strlen(text);
	if(textLength > this->capacity) //new string cannot fit => reallocate, copy, blah blah
	{
		if(this->data)
			free();
		cstringInit(text);
	}
	else if(textLength > this->length) //text is longer, but can fit
	{
		if(textLength <= this->capacity)
		{
			for(size_t i = 0; i < textLength; i++)
				this->data[i] = text[i];
			this->data[textLength] = '\0';
		//	strcpy_s(this->data, textLength + 1, text);//is this going to work??
			this->length = textLength;
		}
	}
	else // textLength < this->len
	{
		for(size_t i = 0; i < textLength; i++)
			this->data[i] = text[i];
		this->data[textLength] = '\0';
	//	strcpy_s(this->data, textLength + 1, text);
		this->length = textLength;
	}


	return *this;
}

String::String(const char* text)
{
	cstringInit(text);
}

int String::len() const
{
	return this->length;
}

char* String::getData() const
{
	return this->data;
}

bool String::operator==(const String& right)
{
	return !strcmp(this->data, right.data);
}

bool String::operator!=(const String& right)
{
	return !(*this == right);
}

bool String::operator==(const char* text)
{
	return !strcmp(this->data, text);
}

bool String::operator!=(const char* text)
{
	return !(*this == text);
}

char& String::operator[](int index)
{
	if(index < this->length)
		return this->data[index];
	else //not permanent
		throw std::out_of_range("you are an idiot!!");
}

const char& String::operator[](int index) const
{
	if(index < this->length)
		return this->data[index];
	else //not permanent
		throw std::out_of_range("you are an idiot!!");
}

String String::operator+(const String& rhs)
{
	try
	{
		char* temp = new char[this->length + rhs.length + 1];
		for(int i = 0; i < this->length; i++)
			temp[i] = data[i];
		temp[this->length] = '\0';
//		strcpy_s(temp, this->length + 1, this->data);
		for(int i = 0; i < rhs.length; i++)
			temp[this->length + i] = rhs.data[i];
		temp[this->length + rhs.length] = '\0';
	//	strcat_s(temp, this->length + rhs.length + 1, rhs.data);
		String res(temp);
		delete [] temp;
		return res;
	}
	catch(std::bad_alloc e)
	{
		std::cerr << e.what() << std::endl;
	}
}

String& String::operator+=(const String& rhs)
{
	*this = *this + rhs;
	return *this;
} 

std::ostream& operator<<(std::ostream& out, const String& str)
{
	out << str.data;
	return out;
}
