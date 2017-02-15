#include "Thing.h"

void Thing::setName(String name) {	this->name = name; }

void Thing::setAttack(int attack) {	this->attack = attack; }

void Thing::setDefence(int defence) {	this->defence = defence; }

void Thing::setAgility(int agility) { 	this->agility = agility; }

void Thing::setPosition(int x, int y)
{
	this->pos.setX(x);
	this->pos.setY(y);
}

void  Thing::setPositionX(int x) {	this->pos.setX(x); }

void Thing::setPositionY(int y) {	this->pos.setY(y); }

void Thing::setPosition(Point a) {	pos = a; }

String Thing::getName() const {	return this->name; }

int Thing::getAttack() const {	return this->attack; }

int Thing::getDefence() const {	return this->defence; }

int Thing::getAgility() const { return this->agility; }

Point Thing::getPosition() const {	return pos; }

int Thing::getPositionX() const { 	return pos.getX(); }

int Thing::getPositionY() const {	return pos.getY(); }
