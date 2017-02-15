#include "Game.h"
#include <fstream>

void Game::setPlayerName(String name){	this->playerName = name; }

String Game::getPlayerName() const { return this->playerName; }

void Game::getMapSizeFromFile(std::ifstream& input, int& rowsCount, int& colsCount)
{
	input.clear();
	input.seekg(0, std::ios::beg);//position get pointer at the beginning of our file

	int rows = 0; 
	int cols = 0; 

	char c = 0;
	int counter = 0;
		
	// Find the number of columns of the map matrix by counting the characters of the first line(except the '\n' character)
	while (input.get(c) && c != '\n')
		cols++;

	bool flag = true;
	char* currentLine = new char[cols +1];
	// Find the number of rows of the map matrix and also
	// verify that all rows have the same length
	if (cols > 0)
	{
		rows++; // at least one row was read from the file(when we counted the columns)

		while(flag)
		{
			input.getline(currentLine, cols + 1, '\n');
			if(strlen(currentLine) == cols)
			{
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

Item Game::readSingleItem(std::ifstream& input, bool readPos)
{
	String name, type;
		int nameLen, typeLen;
		int attack = 0, defence = 0, agility = 0, posX = 0, posY = 0;
		input >> nameLen;
		nameLen++; // for '\0'
		char* itemName = NULL;
		try
		{
			itemName = new char[nameLen];
		}
		catch(std::bad_alloc e)
		{
			std::cerr << e.what() << std::endl;
		}
		input.get(itemName, nameLen);
		if(!input.good())
		{
			std::cerr << "Error reading character!";
		}
		input >> typeLen;
		typeLen++;
		char* itemType = NULL;
		try
		{
			itemType = new char[typeLen];
		}
		catch(std::bad_alloc e)
		{
			std::cerr << e.what() << std::endl;
		}
		input.get(itemType, typeLen);
		if(!input.good())
		{
			std::cerr << "Error reading character!";
		}
		if(readPos)
			input >> posX >> posY >> attack >> defence >> agility;
		else
			input >> attack >> defence >> agility;
		Item item = Item(String(itemName), String(itemType), posX, posY, attack, defence, agility);
		delete [] itemName;
		delete [] itemType;
		return item;
}

linkedList<Item> Game::readItems(std::ifstream& input)
{
	linkedList<Item> itemsBuffer;
	int itemsCount = 0;	
	input >> itemsCount;
	for(int i = 0; i < itemsCount; i++)
	{		
		itemsBuffer.pushBack(readSingleItem(input, true));		
	}
	return itemsBuffer;
}

void Game::readMonsters(std::ifstream& input)
{
	int monstersCount = 0;	
	input >> monstersCount;
	linkedList<Monster> monstersBuffer;
	for(int i = 0; i < monstersCount; i++)
	{
		int nameLen = 0, attack = 0, defence = 0, agility = 0, posX = 0, posY = 0, health = 0;
		input >> nameLen;
		nameLen++; // for '\0'	
		char* monsterName = NULL;
		try
		{
			monsterName = new char[nameLen];
		}
		catch(std::bad_alloc e)
		{
			std::cerr << e.what() << std::endl;
		}
		input.get(monsterName, nameLen);
		if(!input.good())
		{
			std::cerr << "Error reading character!";
		}
		input >> posX >> posY >> attack >> defence >> agility >> health;
		Monster m = Monster(String(monsterName), posX, posY, attack, defence, agility, health);
		monstersBuffer.pushBack(m);
		delete [] monsterName;
	}
	this->currentLevel.setMonsters(monstersBuffer);
}

void Game::loaderHelper(std::ifstream& input, const char* fileName)
{
	input.open(fileName, std::ios::in);
	if(!input)
		throw "Error: Unable to open .txt file!\n";
	
	int rows, cols = 0;
	getMapSizeFromFile(input, rows, cols);
	//allocateMap:
	Vector<String> map;
	map.resize(rows);
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
			map[i] += "4";
	}
	//now start reading
	input.clear();
	input.seekg(0, std::ios::beg);
	char c;
	int i = 0, j = 0;
	for(; i < rows; i++) //read the matrix of characters
	{
		for(; j < cols; j++)
		{
			input.get(c);
			if(c == '\n')
			{
				j = 0;
				i--;
				break;
			}
			if(!input)
				throw "Error when reading characters from file!\n";
			
			map[i][j] = c;
			if(c == '@')
			{
				smiley.setPositionX(i);
				smiley.setPositionY(j);
				map[i][j] = (char)1;
			}
			if(c == '#')
				map[i][j] = (char)219;
		}
		j = 0;
	}

	currentLevel.setMap(map);
	//now read items
	this->currentLevel.setItems(readItems(input));
	//read monsters
	readMonsters(input);
}

bool Game::loadLevel(const char* fileName) //throws messages
{
	std::ifstream input;
	
	loaderHelper(input, fileName);

	input.close();
	return true;
}

bool Game::loadNextLevel()
{
	if(this->levelCount < 3)
	{
		String s = "Level1.txt";
		s[5] = '1' + this->levelCount;
		this->levelCount++;
		loadLevel(s.getData());	
		return true;
	}
	else
		return false;
}

bool Game::loadGame(const char* fileName)
{
	std::ifstream input;

	loaderHelper(input, fileName);

	if(!input.is_open())
	{
		std::cout << "Could not open saveFile, loading aborted!\n";
		return false;
	}
	//so far we have the map matrix, items and monsters(if any)
	//now read hero data:
	this->smiley.setInventory(readItems(input));
	int x = 0, y = 0, heroHP = 0;
	input >> x >> y >> heroHP;
	this->smiley.setPositionX(x);
	this->smiley.setPositionY(y);
	this->smiley.setHealth(heroHP);
	this->smiley.setHeadItem(readSingleItem(input, false));
	this->smiley.setChestItem(readSingleItem(input, false));
	this->smiley.setPrimaryWeapon(readSingleItem(input, false));
	this->smiley.setSecondaryWeapon(readSingleItem(input, false));
	this->smiley.setLegsItem(readSingleItem(input, false));
	this->smiley.setFeetItem(readSingleItem(input, false));
	input >> this->levelCount;
	input.close();
	return true;
}

void Game::saveGame(const char* fileName)
{
	std::ofstream output;
	output.open(fileName, std::ios::out, std::ios::trunc); // open file and truncate it
	if(!output.is_open())
	{
		std::cout << "Could not open save file, saving aborted!/n";
		return;
	}
	if(output.good())
	{
		// write map matrix...
		int rows = this->currentLevel.getMap().getUsedSize();
		int cols = this->currentLevel.getMap()[0].len();
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				if(this->currentLevel.getMap()[i][j] == (char)219)
					output << '#';
				else if(this->currentLevel.getMap()[i][j] == (char)1)
					output << '@';
				else
					output << this->currentLevel.getMap()[i][j];
			}
			output << '\n';
		}
		//write items leftover on map...
		output << this->currentLevel.getItems().getSize() << "\n";
		linkedList<Item> itemsOnMap = this->currentLevel.getItems();
		for(linkedList<Item>::listIterator iter = itemsOnMap.begin(); iter != itemsOnMap.end(); ++iter)
		{
			output << (*iter).getName().len() << (*iter).getName() << " " << 
				(*iter).getType().len() << (*iter).getType() << " " <<
				(*iter).getPositionX() << " " << (*iter).getPositionY() << " " <<
				(*iter).getAttack() << " " << (*iter).getDefence() << " " << (*iter).getAgility() << "\n";
		}
		//write monsters on map...
		output << this->currentLevel.getMonsters().getSize() << "\n";
		linkedList<Monster> monsters = this->currentLevel.getMonsters();
		for(linkedList<Monster>::listIterator iter = monsters.begin(); iter != monsters.end(); ++iter)
		{
			output << (*iter).getName().len() << (*iter).getName() << " " << 
				(*iter).getPositionX() << " " << (*iter).getPositionY() << " " <<
				(*iter).getAttack() << " " << (*iter).getDefence() << " " << 
				(*iter).getAgility() << " " << (*iter).getHealth() <<  "\n";
		}
		// write inventory(backpack) data, hero data
		output << this->smiley.getInventory().getSize() << "\n";
		linkedList<Item> heroInventory= this->smiley.getInventory();
		for(linkedList<Item>::listIterator iter = heroInventory.begin(); iter != heroInventory.end(); ++iter)
		{
			output << (*iter).getName().len() << (*iter).getName() << " " << 
				(*iter).getType().len() << (*iter).getType() << " " <<
				//dont need pos of inv. items, bit I need it to reuse readItems()...
				(*iter).getPositionX() << " " << (*iter).getPositionY() << " " <<
				(*iter).getAttack() << " " << (*iter).getDefence() << " " << (*iter).getAgility() << "\n";

		}
		//UGLIEST code ever, fix it someday...
		output << this->smiley.getPositionX() << " " << this->smiley.getPositionY() << " " << this->smiley.getHealth() << '\n';
		output << this->smiley.getHeadItem().getName().len() << this->smiley.getHeadItem().getName() << " "
			<< this->smiley.getHeadItem().getType().len() << this->smiley.getHeadItem().getType() << " "
			<< this->smiley.getHeadItem().getAttack() << " " << this->smiley.getHeadItem().getDefence() << " "
			<< this->smiley.getHeadItem().getAgility() << "\n";
		output << this->smiley.getChestItem().getName().len() << this->smiley.getChestItem().getName() << " "
			<< this->smiley.getChestItem().getType().len() << this->smiley.getChestItem().getType() << " "
			<< this->smiley.getChestItem().getAttack() << " " << this->smiley.getChestItem().getDefence() << " "
			<< this->smiley.getChestItem().getAgility() << "\n";
		output << this->smiley.getPrimaryWeapon().getName().len() << this->smiley.getPrimaryWeapon().getName() << " "
			<< this->smiley.getPrimaryWeapon().getType().len() << this->smiley.getPrimaryWeapon().getType() << " "
			<< this->smiley.getPrimaryWeapon().getAttack() << " " << this->smiley.getPrimaryWeapon().getDefence() << " "
			<< this->smiley.getPrimaryWeapon().getAgility() << "\n";
		output << this->smiley.getSecondaryWeapon().getName().len() << this->smiley.getSecondaryWeapon().getName() << " "
			<< this->smiley.getSecondaryWeapon().getType().len() << this->smiley.getSecondaryWeapon().getType() << " "
			<< this->smiley.getSecondaryWeapon().getAttack() << " " << this->smiley.getSecondaryWeapon().getDefence() << " "
			<< this->smiley.getSecondaryWeapon().getAgility() << "\n";
		output << this->smiley.getLegsItem().getName().len() << this->smiley.getLegsItem().getName() << " "
			<< this->smiley.getLegsItem().getType().len() << this->smiley.getLegsItem().getType() << " "
			<< this->smiley.getLegsItem().getAttack() << " " << this->smiley.getLegsItem().getDefence() << " "
			<< this->smiley.getLegsItem().getAgility() << "\n";
		output << this->smiley.getFeetItem().getName().len() << this->smiley.getFeetItem().getName() << " "
			<< this->smiley.getFeetItem().getType().len() << this->smiley.getFeetItem().getType() << " "
			<< this->smiley.getFeetItem().getAttack() << " " << this->smiley.getFeetItem().getDefence() << " "
			<< this->smiley.getFeetItem().getAgility() << "\n";
		output << levelCount;
	}
	else
	{
		std::cout << "Save failed!\n";
		return;
	}
	output.close();
	std::cout << "Save successful!\n";
}

void Game::test()
{
	for(int i = 0; i < this->currentLevel.getMap().getUsedSize(); i++)
	{
		for(int j = 0; j < this->currentLevel.getMap()[i].len(); j++)
			std::cout << this->currentLevel.getMap()[i][j];
		std::cout << std::endl;
	}
	linkedList<Item> itemsCopy = this->currentLevel.getItems();
	for(linkedList<Item>::listIterator iter = itemsCopy.begin();
									   iter != itemsCopy.end(); ++iter)
	{
		std::cout << (*iter).getName() << " " << (*iter).getType() << " " << (*iter).getAttack() << " " <<
			(*iter).getDefence() << " " << (*iter).getAgility() << std::endl;
	}
	linkedList<Monster> monstersCopy = this->currentLevel.getMonsters();
	for(linkedList<Monster>::listIterator iter = monstersCopy.begin();
										  iter != monstersCopy.end(); ++iter)
	{
		std::cout << (*iter).getName() << " " << (*iter).getHealth() << " " << (*iter).getAttack() << " " <<
			(*iter).getDefence() << " " << (*iter).getAgility() << std::endl;
	}
}

void Game::moveHero(Vector<String>& mapCopy, int x, int y, char& todo)
{
	this->smiley.setPosition(x, y);
			todo = mapCopy[x][y]; 
			mapCopy[x][y] = smiley.getRepresentingCharacter();
			this->currentLevel.setMap(mapCopy);
}

bool Game::handleMovement(char direction, char& todo) //we expect only the following: w, a, s, d, W, A, S, D
{
	Vector<String> mapCopy = this->currentLevel.getMap();
	int x = this->smiley.getPositionX();
	int y = this->smiley.getPositionY();
	if(direction == 'a' || direction == 'A')//move left
	{
		if(y - 1 < 0 || mapCopy[x][y - 1] == char(219))
			return false; 
		else
		{
			mapCopy[x][y] = ' ';
			moveHero(mapCopy, x, y - 1, todo);
			return true;
		}
	}
	else if(direction == 'd' || direction == 'D') //move right
	{
		if(y + 1 >= mapCopy[x].len() || mapCopy[x][y + 1] == (char)219)
			return false;
		else
		{
			mapCopy[x][y] = ' ';
			moveHero(mapCopy, x, y + 1, todo);
			return true;
		}
	}
	else if(direction == 'w' || direction == 'W') //move up
	{
		if(x - 1 < 0 || mapCopy[x - 1][y] == (char)219)
			return false;
		else
		{
			mapCopy[x][y] = ' ';
			moveHero(mapCopy, x - 1, y, todo);
			return true;
		}
	}
	else if(direction == 's' || direction == 'S') //move down
	{
		if(x + 1 >= mapCopy.getUsedSize() || mapCopy[x + 1][y] == (char)219)
			return false;
		else
		{
			mapCopy[x][y] = ' ';
			moveHero(mapCopy, x + 1, y, todo);
			return true;
		}
	}	
	return false;
}
