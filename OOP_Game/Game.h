#pragma once
#include "Level.h"
#include "Hero.h"

class Game
{
private:
	void getMapSizeFromFile(std::ifstream&, int&, int&);
	linkedList<Item> readItems(std::ifstream&);
	Item readSingleItem(std::ifstream&, bool);
	void readMonsters(std::ifstream&);
	void moveHero(Vector<String>&, int, int, char&);
	void loaderHelper(std::ifstream&, const char*);

protected:
	Level currentLevel;
	Hero smiley;
	String playerName;
	int levelCount;
	bool complete;

public:
	bool loadLevel(const char* file);
	bool loadGame(const char* file);
	void saveGame(const char* file);
	bool loadNextLevel();
	bool handleMovement(char, char&);
	void test();
	void setPlayerName(String);
	String getPlayerName() const;
};