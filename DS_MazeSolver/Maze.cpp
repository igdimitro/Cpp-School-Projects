#include "Maze.h"
#include <fstream>

Maze::Maze()
{
	start = end = NULL;
}

void Maze::allocateMap(int rows, int cols)
{
	map.resize(rows);
	for(size_t i = 0; i < rows; i++)
		map[i].resize(cols);

	rowsCount = rows;
	columnsCount = cols;
}

void Maze::getMapSizeFromFile(std::ifstream& input, int& rowsCount, int& colsCount)
{
	input.clear();
	input.seekg(0, std::ios::beg);//position get pointer at the beginning of our file

	int rows = 0; // number of rows in the board
	int cols = 0; // number of columns in the board

	char c = 0;
	int counter = 0;
		
	// Find the number of columns in the maze by counting the characters of the first line(except the '\n' character)
	while (input.get(c) && c != '\n')
		cols++;

	bool flag = true;
	char* currentLine = new char[cols +1];
	// Find the number of rows in the maze and also
	// verify that all rows have the same length
	if (cols > 0)
	{
		rows++; // at least one row was read from the file(when we counted the columns)

		while(flag)
		{
			input.getline(currentLine, cols + 1, '\n');
			if(strlen(currentLine) == cols)
			{
				//// the number of columns on each line must be the same
				//if (cols != counter)
				//	throw "Error: One of the rows does not match the length of the others!\n";

				rows++;
			}
			else
			{
				flag = false;
			}
		}
	}
	else 
		throw "Error: Invalid or empty input file!\n";
	rowsCount = rows;
	colsCount = cols;
}

void Maze::readMapFromFile(std::ifstream& input)
{
	input.clear();
	input.seekg(0, std::ios::beg);
	char c;
	linkedList<Cell*> specialCells;// we will push pointers to the cells that are either a key or a door...
	size_t i = 0, j = 0;
	for(; i < rowsCount; i++) //first read the matrix of characters..
	{
		for(; j <= columnsCount; j++)
		{
			input.get(c);
			if(c == '\n')
			{
				j = 0;
				break;
			}
			if(!input)
				throw "Error when reading characters from file!\n";

			map[i][j] = Cell(i, j, c);

			if(c != ' ' && c != '#' && c != 'S' && c != 'E')//then it must be either a key or a door
			{
				specialCells.pushBack(&map[i][j]);
			}

			if(c == 'S')
			{
				if(start)
					throw "Invalid input data, more than one start point!";
				else
					start = &map[i][j];
			}
			else if(c == 'E')
			{
				if(end)
					throw "Invalid input data, more than one end point!";
				else
					end = &map[i][j];
			}
		}
		j = 0;

	}
	// TO DO: read keys and doors:	
	char key, door;
	while(input.good())//continue reading until the end of input file
	{
		input.get(c);//it should be a '\n'

		input.get(door);
		input.get(key);
		if(!input)
			break;
		if(door != ' ' && door != '#' && door != 'S' && door != 'E' && key != ' ' && key != '#' && key != 'S' && key != 'E')
		{
			addCellsToKeysAndDoors(door, key, specialCells);		
		}
		else
			throw "Error: Invalid symbols used for door and key describtion!\n";
	}	
}

void Maze::addCellsToKeysAndDoors(char door, char key, linkedList<Cell*>& keysAndDoors)
{
	Cell* doorCell = NULL;
	Cell* keyCell = NULL;
	for(linkedList<Cell*>::listIterator iter = keysAndDoors.begin(); iter != keysAndDoors.end(); ++iter)
	{
		if((*iter)->getSymbol() == door)
			doorCell = (*iter);
		if((*iter)->getSymbol() == key)
			keyCell = (*iter);
	}

	if(doorCell && keyCell)
	{
		doorCell->setIsDoor(true);
		keyCell->setIsKey(true);
		this->keysAndDoors.pushBack(makePair<Cell*, Cell*>(doorCell, keyCell));
	}		
}

void Maze::readMapFromFile(const char* fullFileName)
{
	std::ifstream input;
	input.open(fullFileName, std::ios::in);
	if(!input)
		throw "Error: Unable to open .txt file!\n";

	int rows = 0;
	int cols = 0;

	getMapSizeFromFile(input, rows, cols);
	allocateMap(rows, cols);
	readMapFromFile(input);
	rowsCount = rows;
	columnsCount = cols;
	//tuka trqbva da ima input.close(), no za da ne schupq neshto...
}

void Maze::printMap() const
{
	for(int i = 0; i < rowsCount; i++)
	{
		for(int j = 0; j < columnsCount; j++)
		{
			std::cout << map[i][j].getSymbol();
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;		
}

void Maze::printDoorsAndKeys()
{
	for(linkedList<myPair<Cell*, Cell*>>::listIterator i = keysAndDoors.begin(); i != keysAndDoors.end(); ++i)
	{
		std::cout << (*i).first->getSymbol() << " -> " << (*i).second->getSymbol() << std::endl;
	}
}

bool Maze::isWalkableCellAt(int x, int y)
{
	return map[x][y].getSymbol() == ' ';
}

Cell* Maze::getLeftNeighbourOf(Cell* cell)
{
	if(cell->getColumn() == 0)
		return NULL;
	return &map[cell->getRow()][cell->getColumn() - 1];
}

Cell* Maze::getRightNeighbourOf(Cell* cell)
{
	if(cell->getColumn() == map[0].getUsedSize() - 1)
		return NULL;
	return &map[cell->getRow()][cell->getColumn() + 1];	
}

Cell* Maze::getUpperNeighbourOf(Cell* cell)
{
	if(cell->getRow() == 0)
		return NULL;
	return &map[cell->getRow() - 1][cell->getColumn()];
}

Cell* Maze::getLowerNeighbourOf(Cell* cell)
{
	if(cell->getRow() == map.getUsedSize() - 1)
		return NULL;
	return &map[cell->getRow() + 1][cell->getColumn()];
}

linkedList<Cell*> Maze::findPath(Cell* from, Cell* to)
{
	linkedList<Cell*> path;
	if(!from || !to)
		return path;

	bool pathFound = false;

	Cell* currentCell = from;

	// Define the open and the close list.
	linkedList<Cell*> openList;
	linkedList<Cell*> closedList;
	linkedList<Cell*>::listIterator i = openList.begin();

	// Add the start point to the open list.
	openList.pushBack(from);
	from->setOpened(true);

	while(currentCell != to)
	{
		if (openList.isEmpty())
		{
			pathFound = false;
			break;
		}
		// Look for the shortest distance to target in the openList and make it currentCell.
		for(i = openList.begin(); i != openList.end(); ++i)
		{
			if (i == openList.begin() || (*i)->getDistanceToTarget() <= currentCell->getDistanceToTarget())
			{
				currentCell = (*i);
			}
		}

		// Stop if we reached the end.
		if(currentCell == to)
		{
			pathFound = true;
			break;
		}

		// Remove currentCell from the openList.
		openList.removeElement(currentCell);
		currentCell->setOpened(false);

		// Add currentCell to the closedList.
		closedList.pushBack(currentCell);
		currentCell->setClosed(true);

		// Four function calls for the four neighbours
		addChildIfSuitable(currentCell, getLeftNeighbourOf(currentCell), openList, to);
		addChildIfSuitable(currentCell, getRightNeighbourOf(currentCell), openList, to);
		addChildIfSuitable(currentCell, getUpperNeighbourOf(currentCell), openList, to);		
		addChildIfSuitable(currentCell, getLowerNeighbourOf(currentCell), openList, to);
	}

	// Reset cells in both lists
	for(i = openList.begin(); i != openList.end(); ++i)
	{
		(*i)->setOpened(false);
	}
	for(i = closedList.begin(); i != closedList.end(); ++i)
	{
		(*i)->setClosed(false);
	}

	if(!pathFound)
		return path;

	// Resolve the path starting from the end point
	while(currentCell && currentCell->getParent() && currentCell != from)
	{
		path.pushFront(currentCell);
		currentCell = currentCell->getParent();
	}
	return path;
}

void Maze::addChildIfSuitable(Cell* current, Cell* child, linkedList<Cell*>& openList, Cell* endCell)
{
	// TO DO: what if child is a NULL pointer ?!?
	// If it's closed or not walkable then pass
	if(!child || child->getClosed() || !walkableWithoutWalls(child))
	{
		return;
	}

	if(!child->getOpened())
	{
		// Add it to the openList with current point as parent
		openList.pushBack(child);
		child->setOpened(true);

		// Compute it's distance to target
		child->setParent(current);
		child->computeDistanceToTarget(endCell);
	}
}

bool Maze::walkableWithoutWalls(Cell* cell) 
{
	return cell->getSymbol() != '#';
}

bool Maze::isKeyElement(Cell* cell)
{
	for(linkedList<myPair<Cell*, Cell*>>::listIterator iter = keysAndDoors.begin(); iter != keysAndDoors.end(); ++iter)
	{
		if( cell == (*iter).first || (*iter).second) //cell is door or key 
			return true;
	}
	return (cell == start ||  cell == end ); 

}

Cell* Maze::getKeyForDoor(Cell* door)
{
	for(linkedList<myPair<Cell*, Cell*>>::listIterator iter = keysAndDoors.begin(); iter != keysAndDoors.end(); ++iter)
	{
		if((*iter).first == door)
			return (*iter).second;
	}
}

bool Maze::keyIsNotOwned(Cell* key)
{
	if(!key->getIsKey())
		return false;
	for(linkedList<Cell*>::listIterator i = ownedKeys.begin(); i < ownedKeys.end(); ++i)
	{
		if((*i) == key)
			return false;
	}
	return true;
}

//Search for a path from start to end cells, and enqueue all encountered doors
queue<Cell*> Maze::findMandatoryDoors()
{
	queue<Cell*> doors;
	linkedList<Cell*> pathFromStartToEnd = findPath(start, end);
	if (pathFromStartToEnd.isEmpty())
	{
		throw  "Error 404: Path not found!\n" ;
	}

	for(linkedList<Cell*>::listIterator iter = pathFromStartToEnd.begin(); iter != pathFromStartToEnd.end(); ++iter)
	{
	
		if((*iter)->getIsDoor())
			doors.enqueue((*iter));
		if((*iter)->getIsKey())//if we happen to walk over a key when searching for exit, we might as well pick it up and use it later
		{
			ownedKeys.pushBack((*iter));
		}
	}
	return doors;
}

void Maze::buildDoorStack(Cell*& startFrom, Cell* currentDoor, Stack<Cell*>& doorStack)
{
	//look for a path to currentDoor's key..
	Cell* currentDoorKey = getKeyForDoor(currentDoor);
	linkedList<Cell*> pathToCurrentDoorKey = findPath(startFrom,currentDoorKey );
	if(pathToCurrentDoorKey.isEmpty())//if such path is not found - the so called doorStack is ready
	{
		return;
	}
	bool pathContainsADoor = false;
	doorStack.push(currentDoorKey);//push found key then continue...

	for(linkedList<Cell*>::listIterator i = pathToCurrentDoorKey.begin(); i != pathToCurrentDoorKey.end(); ++i)
	{
		if((*i)->getIsDoor())
		{
			pathContainsADoor = true;
			doorStack.push((*i));
			if(keyIsNotOwned(getKeyForDoor((*i)))) //if we do not own the key for this door, we go ahead and look for it...
			{
				buildDoorStack(startFrom ,(*i), doorStack);
			}
		}		
	}
	if(!pathContainsADoor)//also, if we don't come across any other doors when looking for currentDoor's key, the stack is ready
	{
		startFrom = currentDoor;
		return;
	}
}

linkedList<Cell*> Maze::findMazeSolution()
{
	linkedList<Cell*> finalPath;
	queue<Cell*> mandatoryDoors = findMandatoryDoors();
	Cell* currentStartingPoint = start;
	Cell* startingPointForPath = start;
	while(!mandatoryDoors.isEmpty()) //for every mandatory door build its own "doorStack" - a sequence of keys and other doors needed to "unlock" it
	{
		Stack<Cell*> doorStack;
		Cell* currentDoor = mandatoryDoors.peek();
		
		mandatoryDoors.dequeue();
		buildDoorStack(currentStartingPoint, currentDoor, doorStack);
		finalPath += getPathToDoor(doorStack, startingPointForPath);
	
	}
	if(finalPath.isEmpty())
	{
		finalPath += findPath(start, end);
	}
	else
	{
		Cell* lastVisitedKey = finalPath.peekBack();
		finalPath += findPath(lastVisitedKey, end);
	}
	
	return finalPath;
}

linkedList<Cell*> Maze::getPathToDoor(Stack<Cell*>& doorStack, Cell*& startingFrom)
{
	linkedList<Cell*> path;
	while(!doorStack.isEmpty())
	{
		Cell* currentObject = doorStack.peek();
		doorStack.pop();
		path += findPath(startingFrom, currentObject);
		startingFrom = path.peekBack();
	}
	return path;
}

char* Maze::convertPathToInstructions(linkedList<Cell*> path)
{
	int stringLength = path.getSize();
	char* pathString = new char[stringLength + 1];
	memset(pathString, '\0', stringLength);
	int pos = 0;
	while(!path.isEmpty())
	{
		if(pos == stringLength)
			break;
		Cell* current = path.peekFront();
		path.popFront();
		if(pos == stringLength - 1)
			break;
		Cell* next = path.peekFront();

		if(current->getRow() < next->getRow() && current->getColumn() == next->getColumn())
			pathString[pos] = 'D';
		else if(current->getRow() > next->getRow() && current->getColumn() == next->getColumn())
			pathString[pos] = 'U';
		if(current->getColumn() < next->getColumn() && current->getRow() == next->getRow())
			pathString[pos] = 'R';
		else if(current->getColumn() > next->getColumn() && current->getRow() == next->getRow())
			pathString[pos] = 'L';
		pos++;
	}
	pathString[pos] = '\0';
	return  pathString;
}

void Maze::printPath(linkedList<Cell*> path)
{
	for(linkedList<Cell*>::listIterator i = path.begin(); i != path.end(); ++i)
	{
		(*i)->setSymbol('+');
	}
	printMap();
}

char* Maze::solveMaze()
{
	linkedList<Cell*> path = findMazeSolution();
	if (path.isEmpty())
	{
		throw "There is no path for this maze!\n";
	}
	else
		printPath(path);

	char* instructions = convertPathToInstructions(path);

	return instructions;
}
