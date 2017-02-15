#include "Point.h"

void Point::setX(int x) {	this->x = x; }

void Point::setY(int y) {	this->y = y; }

int Point::getX() const { 	return this->x; }

int Point::getY() const { 	return this->y; }

bool Point::operator==(const Point& B) const {	return this->x == B.x && this->y == B.y; }