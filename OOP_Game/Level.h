#pragma once
#include "Vector.h"
#include "List.h"
#include "String.h"
#include "Item.h"
#include "Monster.h"

class Level
{
private:
	Vector<String> map;
	String fileName;
	linkedList<Item> items;
	linkedList<Monster> monsters;
public:
	void setMap(Vector<String>);
	void setItems(linkedList<Item>);
	void setMonsters(linkedList<Monster>);
	void setFileName(String);
	Vector<String> getMap() const;
	linkedList<Item> getItems() const;
	linkedList<Monster> getMonsters() const;
	String getFileName() const;
	Item getItemAt(int, int);
	Monster getMonsterAt(int, int);
	void removeItem(Item&);
	void removeMonster(Monster&);
};