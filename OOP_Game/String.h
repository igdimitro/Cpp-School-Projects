#pragma once
#include <iostream>

class String
{
private:
	char* data;
	int length;
	int capacity;

	void free();
	void copyFrom(const String& other);//Does not free previously allocated memory!!! Only call after free() or in copy Constructor!!!
	void cstringInit(const char* text);
public:

	String();
	String(const char* text);
	String(const String& other);
	String& operator=(const String& other);
	~String();
	int len() const;
	String& operator=(const char* text);
	char* getData() const;
	bool operator==(const String& right);
	bool operator!=(const String& right);
	bool operator==(const char* text);
	bool operator!=(const char* text);
	char& operator[](int); // char& zashtoto moje i da promenim tova koeto stoi na tazi poziciq
	const char& operator[](int) const; //izvlichame inf samo za chetene
	String operator+(const String& rhs);
	String& operator+=(const String& rhs);
	friend std::ostream& operator<<(std::ostream&, const String&);
	friend std::istream& operator>>(std::istream&, String&); // cant do...
};