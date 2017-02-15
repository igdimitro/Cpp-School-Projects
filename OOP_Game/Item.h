#pragma once
#include "Thing.h"
#include <iostream>

class Item:public Thing
{
private:
	String type;

public:
	Item();
	Item(String, String, int, int, int, int , int);
	virtual char getRepresentingCharacter();
	void setType(String);
	String getType() const;
	bool operator==(const Item&);
	friend std::ostream& operator<<(std::ostream&, Item&);
};