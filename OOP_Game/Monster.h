#pragma once
#include "Thing.h"

class Monster: public Thing
{
public:
	Monster();
	Monster(String, int, int, int, int, int, int);
	virtual char getRepresentingCharacter();
	void setHealth(int);
	int getHealth() const;
	bool operator==(const Monster&);
private:
	int health;
};