#include "Cell.h"
#include <iostream>

Cell::Cell()
{
	parent = NULL;
	row = column = distanceToTarget = 0;
	opened = false;
	closed = false;
	symbol = ' ';
	isDoor = false;
	isKey = false;
}

Cell::Cell(int row, int column, char symbol)
{
	parent = NULL;
	distanceToTarget = 0;
	opened = false;
	closed = false;
	isDoor = false;
	isKey = false;
	this->row = row;
	this->column = column;
	this->symbol = symbol;
}

Cell* Cell::getParent() const
{
	return parent;
}

bool Cell::getClosed() const
{
	return closed;
}

bool Cell::getOpened() const
{
	return opened;
}

bool Cell::getIsDoor() const
{
	return isDoor;
}

bool Cell::getIsKey() const
{
	return isKey;
}

int Cell::getRow() const
{
	return row;
}

int Cell::getColumn() const
{
	return column;
}
	
int Cell::getDistanceToTarget() const
{
	return distanceToTarget;
}

char Cell::getSymbol() const
{
	return symbol;
}

void Cell::setParent(Cell* parent)
{
	this->parent = parent;
}

void Cell::setClosed(bool closed)
{
	this->closed = closed;
}

void Cell::setOpened(bool opened)
{
	this->opened = opened;
}

void Cell::setRow(int row)
{
	this->row = row;
}

void Cell::setColumn(int column)
{
	this->column = column;
}

void Cell::setIsDoor(bool isDoor)
{
	this->isDoor = isDoor;
}

void Cell::setIsKey(bool isKey)
{
	this->isKey = isKey;
}

void Cell::setDistanceToTarget(int f)
{
	this->distanceToTarget = f;
}

void Cell::setSymbol(char c)
{
	symbol = c;
}

int abs(int number)
{
	return number < 0 ? number*(-1) : number;
}

void Cell::computeDistanceToTarget(Cell* point)
{
	distanceToTarget = abs(point->row - row) + abs(point->column - column);
}