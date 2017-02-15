#pragma once

class Cell
{
	Cell* parent;
	bool closed;
	bool opened;
	int row;
	int column;
	size_t distanceToTarget; 
	char symbol;
	bool isDoor;
	bool isKey;

public:
	Cell();
	Cell(int, int, char);
	Cell* getParent() const;
	bool getClosed() const;
	bool getOpened() const;
	bool getIsDoor() const;
	bool getIsKey() const;
	int getRow() const;
	int getColumn() const;
	int getDistanceToTarget() const;
	void computeDistanceToTarget(Cell*);
	char getSymbol() const;
	void setParent(Cell*);
	void setClosed(bool);
	void setOpened(bool);
	void setRow(int);
	void setSymbol(char);
	void setColumn(int);
	void setDistanceToTarget(int);
	void setIsDoor(bool);
	void setIsKey(bool);
	bool walkableWithoudWalls() const;
	bool walkableWithoutDoors() const; 
};