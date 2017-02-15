#include "Hero.h"

void Hero::equipBasicItems()
{
	this->head = Item("hat", "head", 0, 0, 0, 0, 0);
	this->chest = Item("T-shirt", "chest", 0, 0, 0, 0, 0);
	this->primaryWeapon = Item("stick", "primaryWeapon", 0, 0, 0, 0, 0);
	this->secondaryWeapon = Item("a Snickers bar", "secondaryWeapon", 0, 0, 0, 0, 0);
	this->legs = Item("Jeans", "legs", 0, 0, 0, 0, 0);
	this->feet = Item("Trainers", "feet", 0, 0, 0, 0, 0);
}

Hero::Hero()
{	
	setHealth(100);
	setAttack(5); //fists :D
	setDefence(0);
	setAgility(0);
	equipBasicItems();
}

int Hero::getHealth() const {	return this->health; }

linkedList<Item> Hero::getInventory() const {	return this->inventory; }

void Hero::setInventory(linkedList<Item> items) {	this->inventory = items; }

void Hero::setHealth(int health)
{
	if(health <= 0)
		this->health = 0;
	else
		this->health = health;
}

void Hero::setHeadItem(Item i) { this->head = i; }

void Hero::setChestItem(Item i) {this->chest = i; }

void Hero::setPrimaryWeapon(Item i) {this->primaryWeapon = i; }

void Hero::setSecondaryWeapon(Item i) {this->secondaryWeapon = i; }

void Hero::setLegsItem(Item i) {this->legs = i; }

void Hero::setFeetItem(Item i) {this->feet = i; }

char Hero::getRepresentingCharacter() {	return (char)1; }

void Hero::pickUPItem(Item& item) { this->inventory.pushBack(item); }

Item Hero::getHeadItem() const { return this->head; }

Item Hero::getChestItem() const { return this->chest; }

Item Hero::getPrimaryWeapon() const { return this->primaryWeapon; }

Item Hero::getSecondaryWeapon() const { return this->secondaryWeapon; }

Item Hero::getLegsItem() const { return this->legs; }

Item Hero::getFeetItem() const { return this->feet; }

bool Hero::equipItem(Item& item) //find a better way to do this...
{
	if(item.getType() == "head")
	{
		this->attack -= this->head.getAttack();
		this->defence -= this->head.getDefence();
		this->agility -= this->head.getAgility();
		this->inventory.pushBack(this->head);
		this->head = item;
		this->attack += item.getAttack();
		this->defence += item.getDefence();
		this->agility += item.getAgility();
		this->inventory.removeElement(item);
		return true;
	}
	else if(item.getType() == "chest")
	{
		this->attack -= this->chest.getAttack();
		this->defence -= this->chest.getDefence();
		this->agility -= this->chest.getAgility();
		this->inventory.pushBack(this->chest);
		this->chest = item;
		this->attack += item.getAttack();
		this->defence += item.getDefence();
		this->agility += item.getAgility();
		this->inventory.removeElement(item);
		return true;
	}
	else if(item.getType() == "primaryWeapon")
	{
		this->attack -= this->primaryWeapon.getAttack();
		this->defence -= this->primaryWeapon.getDefence();
		this->agility -= this->primaryWeapon.getAgility();
		this->inventory.pushBack(this->primaryWeapon);
		this->primaryWeapon = item;
		this->attack += item.getAttack();
		this->defence += item.getDefence();
		this->agility += item.getAgility();
		this->inventory.removeElement(item);
		return true;
	}
	else if(item.getType() == "secondaryWeapon")
	{
		this->attack -= this->secondaryWeapon.getAttack();
		this->defence -= this->secondaryWeapon.getDefence();
		this->agility -= this->secondaryWeapon.getAgility();
		this->inventory.pushBack(this->secondaryWeapon);
		this->secondaryWeapon = item;
		this->attack += item.getAttack();
		this->defence += item.getDefence();
		this->agility += item.getAgility();
		this->inventory.removeElement(item);
		return true;
	}
	else if(item.getType() == "legs")
	{
		this->attack -= this->legs.getAttack();
		this->defence -= this->legs.getDefence();
		this->agility -= this->legs.getAgility();
		this->inventory.pushBack(this->legs);
		this->legs = item;
		this->attack += item.getAttack();
		this->defence += item.getDefence();
		this->agility += item.getAgility();
		this->inventory.removeElement(item);
		return true;
	}
	else if(item.getType() == "feet")
	{
		this->attack -= this->feet.getAttack();
		this->defence -= this->feet.getDefence();
		this->agility -= this->feet.getAgility();
		this->inventory.pushBack(this->feet);
		this->feet = item;
		this->attack += item.getAttack();
		this->defence += item.getDefence();
		this->agility += item.getAgility();
		this->inventory.removeElement(item);
		return true;
	}
	else
		return false;
}