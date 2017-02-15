#include "Level.h"

void Level::setMap(Vector<String> m) {	this->map = m; }

void Level::setFileName(String file) {	this->fileName = file; }

void Level::setItems(linkedList<Item> items) {	this->items = items; }

void Level::setMonsters(linkedList<Monster> monsters) {	this->monsters = monsters; }

String Level::getFileName() const {	return this->fileName; }

linkedList<Item> Level::getItems() const {	return this->items; }

linkedList<Monster> Level::getMonsters() const {	return this->monsters; }

Vector<String> Level::getMap() const {	return this->map; }

Item Level::getItemAt(int x, int y)
{
	linkedList<Item> items = this->items; //this is needed for a complicated reason, need to resolve it later
	for(linkedList<Item>::listIterator iter = items.begin();
									   iter != items.end(); ++iter)
	{
		if((*iter).getPositionX() == x && (*iter).getPositionY() == y)
			return (*iter);
	}
}

Monster Level::getMonsterAt(int x, int y)
{
	linkedList<Monster> monsters = this->monsters;
	for(linkedList<Monster>::listIterator iter = monsters.begin();
										  iter != monsters.end(); ++iter)
	{
		if((*iter).getPositionX() == x && (*iter).getPositionY() == y)
			return (*iter);
	}
}

void Level::removeItem(Item& item) {	this->items.removeElement(item); }

void Level::removeMonster(Monster& monster) { this->monsters.removeElement(monster); }