#pragma once
#include "Point.h"
#include "String.h"

class Thing
{
protected:

	String name;
	Point pos;
	int attack;
	int defence;
	int agility;
	char representedBy;

public:

	void setName(String);
	void setAttack(int);
	void setDefence(int);
	void setAgility(int);
	void setPosition(int, int);
	void setPosition(Point);
	void setPositionX(int);
	void setPositionY(int);
	String getName() const;
	int getAttack() const;
	int getDefence() const;
	int getAgility() const;
	Point getPosition() const;
	int getPositionX() const;
	int getPositionY() const;

protected:

	virtual char getRepresentingCharacter() = 0;

};