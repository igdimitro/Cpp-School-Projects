#include "Item.h"

Item::Item(){}

Item::Item(String name, String type, int x, int y, int attack, int defence, int agility)
{
	setName(name);
	setType(type);
	setPositionX(x);
	setPositionY(y);
	setAttack(attack);
	setDefence(defence);
	setAgility(agility);
}


void Item::setType(String type) {	this->type = type; }

String Item::getType() const { 	return this->type; }

char Item::getRepresentingCharacter() {	return 'I'; }

std::ostream& operator<<(std::ostream& out, Item& item)
 {
	 out << item.getName() << " " << "Atk: "
		 << item.getAttack() << ", Def: " << item.getDefence() 
		 << ", Agi: " << item.getAgility(); 

	return out;
 }

bool Item::operator==(const Item& rhs)
{
	return (this->name == rhs.name && this->type == rhs.type &&
		this->attack == rhs.attack && this->defence == rhs.defence &&
		this->agility == rhs.agility && this->pos == rhs.pos);
}