#include "Monster.h"

Monster::Monster(){}

Monster::Monster(String name,  int x, int y, int attack, int defence, int agility, int health)
{
	setName(name);
	setPositionX(x);
	setPositionY(y);
	setAttack(attack);
	setDefence(defence);
	setAgility(agility);
	setHealth(health);
}

char Monster::getRepresentingCharacter() {	return 'M'; }

int Monster::getHealth() const {   return health; }

void Monster::setHealth(int health)
{
	if(health <= 0)
		this->health = 0;
	else
		this->health = health;
}

bool Monster::operator==(const Monster& rhs)
{
	return (this->name == rhs.name && this->health == rhs.health &&
		this->attack == rhs.attack && this->defence == rhs.defence &&
		this->agility == rhs.agility && this->pos == rhs.pos);	
}