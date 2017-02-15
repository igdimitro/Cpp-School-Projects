#pragma once
#include "Thing.h"
#include "List.h"
#include "Item.h"

class Hero: public Thing
{
private:
	int health;
	linkedList<Item> inventory;
	Item head;
	Item chest;
	Item primaryWeapon;
	Item secondaryWeapon;
	Item legs;
	Item feet;
	void equipBasicItems();

public:
	Hero();
	void setHealth(int);
	void setInventory(linkedList<Item>);
	void setHeadItem(Item);
	void setChestItem(Item);
	void setPrimaryWeapon(Item);
	void setSecondaryWeapon(Item);
	void setLegsItem(Item);
	void setFeetItem(Item);
	linkedList<Item> getInventory() const;
	int getHealth() const;
	Item getHeadItem() const;
	Item getChestItem() const;
	Item getPrimaryWeapon() const;
	Item getSecondaryWeapon() const;
	Item getLegsItem() const;
	Item getFeetItem() const;
	bool equipItem(Item&);
	void pickUPItem(Item&);
	virtual char getRepresentingCharacter();

};