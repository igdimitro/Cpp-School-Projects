#pragma once
#include "Game.h"

//TUI stands for Text User Interface
class TUI: public Game
{
private:
	bool printMainMenu(bool&);
	int printOptionsMenu();
	void printMap() const;
	void printBattleStats(Monster& );
	void fightMonster(Monster&);
	void printHeroInventory();

public:

	void playGame();
};