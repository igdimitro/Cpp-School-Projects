#pragma once
#include "Cell.h"
#include "List.h"
#include "Vector.h"
#include "myUtilities.h"
#include "Stack.h"
#include "Queue.h"

class Maze
{
	int rowsCount;
	int columnsCount;
	Vector<Vector<Cell>> map;
	Cell* start;
	Cell* end;
	linkedList<myPair<Cell*, Cell*>> keysAndDoors;
	linkedList<Cell*> ownedKeys;

	void getMapSizeFromFile(std::ifstream&, int&, int&);
	void readMapFromFile(std::ifstream&);
	void allocateMap(int, int);
	void addCellsToKeysAndDoors(char, char, linkedList<Cell*>&);

	bool isWalkableCellAt(int, int);
	bool walkableWithoutWalls(Cell*);

	linkedList<Cell*> findPath(Cell* , Cell*);
	void addChildIfSuitable(Cell*, Cell*, linkedList<Cell*>& , Cell*);

	Cell* getLeftNeighbourOf(Cell*);
	Cell* getRightNeighbourOf(Cell*);
	Cell* getUpperNeighbourOf(Cell*);
	Cell* getLowerNeighbourOf(Cell*);


	bool isKeyElement(Cell*);
	Cell* getKeyForDoor(Cell*);
	bool keyIsNotOwned(Cell*);

	queue<Cell*> findMandatoryDoors();
	void buildDoorStack(Cell*&, Cell* ,Stack<Cell*>&);
	char* convertPathToInstructions(linkedList<Cell*>);
	linkedList<Cell*> getPathToDoor(Stack<Cell*>&, Cell*&);
	linkedList<Cell*> findMazeSolution();
	void printPath(linkedList<Cell*>);
	char* compressInstructions(char*);
public:
	Maze();
	void printMap() const;
	void printDoorsAndKeys();
	char* solveMaze();
	void readMapFromFile(const char*);
};