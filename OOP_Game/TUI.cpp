#include "TUI.h"
#include <conio.h>

void printMenu(Vector<String> options, int& selected)
{
	system("cls");
	std::cout << "			Smiley's adventure \n\n"; 
	for(int i = 0; i < options.getUsedSize(); i++)
	{
		if(selected == i)
			std::cout << "[" << options[i] << "]\n";
		else
			std::cout << options[i] << std::endl;
	}
	std::cout << "Use W and S to move up and down and press Space to select\n";
}

void printOptions(Vector<String> options, int& selected)
{
	while(true)
	{
		char input = _getch();
		if(input == 'w' || input == 'W')
		{
			if(selected == 0)
				selected = options.getUsedSize() - 1;
			else
				selected--;
		}
		else if(input == 's' || input == 'S')
		{
			if(selected == options.getUsedSize() - 1)
				selected = 0;
			else
				selected++;
		}
		else if(input == ' ')
		{
			break;
		}
		system("Cls");
		printMenu(options, selected);
	}
}

void printItems(linkedList<Item> items, int& selected)
{
	int i = 0;
	std::cout << "\nBackpack:\n";
	for(linkedList<Item>::listIterator iter = items.begin(); iter != items.end(); ++iter)
	{
		if(i == selected)
			std::cout << "[" << (*iter) << "]\n" ;
		else
			std::cout  << (*iter) << std::endl;
		i++;
	}
	std::cout << "\nUse W and S to move up and down and press Space to equip selected item([item])\n"
				  << "Press i to go back to game\n";
}

int TUI::printOptionsMenu()
{
	int selected = 0;
	Vector<String> options;
	options.resize(3);
	options[0] = "Save Game";
	options[1] = "Load Game";
	options[2] = "Exit Game";
	printMenu(options, selected);
	printOptions(options, selected);
	
	return selected;
}

bool TUI::printMainMenu(bool& gameOver)
{
	int selected = 0;
	Vector<String> options;
	options.resize(3);
	options[0] = "New Game";
	options[1] = "Load Game";
	options[2] = "Exit";
	printMenu(options, selected);
	printOptions(options, selected);
	if(selected == 2)
		gameOver = true;

	return selected;
}


void TUI::printHeroInventory()
{
	system("cls");
	std::cout << "			Inventory \n\n" 
	    << "Your equipment is:\n\n"
		<< "Headpiece: "<< this->smiley.getHeadItem() << std::endl 
		<< "Chestplate: " << this->smiley.getChestItem() << std::endl 
		<< "Primary weapon: " << this->smiley.getPrimaryWeapon() << std::endl
		<< "Secondary weapon: " << this->smiley.getSecondaryWeapon() << std::endl
		<< "Leggings: " << this->smiley.getLegsItem() << std::endl
		<< "Boots: " << this->smiley.getFeetItem() << std::endl;
	int selected = 0;
	linkedList<Item> items = smiley.getInventory();
	int rows = items.getSize();
	if(rows)
	{
		printItems(items, selected);
	
		while(true)
		{
			char input = _getch();
			if(input == 'w' || input == 'W')
			{
				if(selected == 0)
					selected = rows - 1;
				else
					selected--;
			}
			else if(input == 's' || input == 'S')
			{
				if(selected == rows - 1)
					selected = 0;
				else
					selected++;
			}
			else if(input == ' ')
			{
				int i = 0;
				Item toEquip;
				for(linkedList<Item>::listIterator iter = items.begin(); iter != items.end(); ++iter)
				{
					if(i == selected)
						toEquip = (*iter);
					i++;
				}
				this->smiley.equipItem(toEquip);
				printHeroInventory();				
			}
			else if(input == 'i' || input == 'I')
			{
				printMap();
				break;
			}
			system("Cls");
			std::cout << "			Inventory \n\n" 
					<< "Your equipment is:\n\n"
					<< "Headpiece: "<< this->smiley.getHeadItem() << std::endl 
					<< "Chestplate: " << this->smiley.getChestItem() << std::endl 
					<< "Primary weapon: " << this->smiley.getPrimaryWeapon() << std::endl
					<< "Secondary weapon: " << this->smiley.getSecondaryWeapon() << std::endl
					<< "Leggings: " << this->smiley.getLegsItem() << std::endl
					<< "Boots: " << this->smiley.getFeetItem() << std::endl;
			printItems(items, selected);
		}
	}
	else
	{
		std::cout << "\nYour backpack is Empty!\nPress i to go back to game\n"; 
		while(true)
		{
			char input = _getch();
			if(input == 'i' || input == 'I')
			{
				printMap();
				break;
			}
		}
	}
}

bool isDigit(char character) 
{
	return (character >= '0' && character <= '9');
}

bool correctInput(char c)
{
	if( isDigit(c) || c == 'w' || c == 'a' || c == 's' || c == 'd'
		           || c == 'W' || c == 'A' || c == 'S' || c == 'D'
				   || c == 'i' || c == 'm' || c == 'l' || c == 'o'
				   || c == 'I' || c == 'M' || c == 'L' || c == 'O'
				   || c == 'p' || c == 'P')
	{
		return true;
	}
	else
		return false;
}

void TUI::printMap() const
{
	Vector<String> map = this->currentLevel.getMap();
	int rows = map.getUsedSize();
	int cols = map[0].len();
	system("cls");
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < cols; j++)
			std::cout << map[i][j];
		std::cout << std::endl;
	}
	std::cout << "Health: " << this->smiley.getHealth()
			  << ", Attack: " << this->smiley.getAttack()
			  << ", Defence: " << this->smiley.getDefence()
			  << ", Agility: " << this->smiley.getAgility()
			  << std::endl;
}

void TUI::printBattleStats(Monster& enemy)
{
	std::cout << "Smiley           Versus          " << enemy.getName() << std::endl;
	std::cout << "Health: " << this->smiley.getHealth() << "                      Health: " << enemy.getHealth() << std::endl
		      << "Attack: " << this->smiley.getAttack() << "                       Attack: " << enemy.getAttack() << std::endl
			  << "Defence: " << this->smiley.getDefence() << "                      Defence: " << enemy.getDefence() << std::endl
			  << "Agility: " << this->smiley.getAgility() << "                      Agility: " << enemy.getDefence() << std::endl;			  
}

void TUI::fightMonster(Monster& m)
{
	system("cls");
	std::cout << "You have encountered an enemy!\nPrepare for battle with a " << m.getName() << "!\n\n";
	_sleep(1000);
	printBattleStats(m);
	_sleep(1000);
	// the first hit in a battle is determined by the agility of the opponents
	int firstAttackDamage = 0;
	if(this->smiley.getAgility() >= m.getAgility())
	{
		firstAttackDamage = this->smiley.getAttack() - m.getDefence();
		if(firstAttackDamage > 0)
			m.setHealth(m.getHealth() - firstAttackDamage);
	}
	else
	{
		firstAttackDamage = m.getAttack() - this->smiley.getDefence();
		if(firstAttackDamage > 0)
			this->smiley.setHealth(this->smiley.getHealth() - firstAttackDamage);
	}
	system("cls");
	printBattleStats(m);
	_sleep(1000);
	while(this->smiley.getHealth() > 0 && m.getHealth() > 0 )
	{
		int currentAttackDamage = this->smiley.getAttack() - m.getDefence();
		if(currentAttackDamage > 0)
		{
			m.setHealth(m.getHealth() - currentAttackDamage);
			system("cls");
			printBattleStats(m);
			_sleep(1000);
		}
		if(m.getHealth() <= 0)
		{
			std::cout << "The " << m.getName() << " has died! You win this battle!\n";
			if (m.getName() == "Darth Vader")
				complete = true;
			_sleep(1000);
			break;
		}
		currentAttackDamage = m.getAttack() - this->smiley.getDefence();
		if(currentAttackDamage > 0)
		{
			this->smiley.setHealth(this->smiley.getHealth() - currentAttackDamage);
			system("cls");
			printBattleStats(m);
			_sleep(1000);
		}
		if(currentAttackDamage == 0) // if the enemy cannot kill you, something has to happen
		{
			std::cout << "You engage the enemy in a brtual battle, but it appears that you are both equally matched!\n"
				      << "Luckily, the odds are in your favour - a divine power intervenes in your battle and strikes the enemy down!\n ";
			m.setHealth(0);	
			_sleep(5000);
		}		
	}
}


void TUI::playGame()
{
	system("cls");
	bool gameOver = false;
	complete = false;
	char input;
	if(printMainMenu(gameOver))
	{
		if(gameOver) return;
		try
		{
			this->loadGame("Save.txt");
			printMap();
		}
		catch(...)
		{
			std::cout << "Error! No load file could be found!\n";
			return;
		}
	}
	else
	{
		if(gameOver) return;
		this->loadLevel("Level1.txt");
		this->levelCount = 1;
		printMap();
	}
	do
	{
		do
		{			
			input = _getch(); // or if you dont want to use <conio.h>, but you will have to press
			//Enter after each symbol you input, because of std::cin...
			/*std::cin.get(input);
			std::cin.clear();
			std::cin.ignore(100, '\n');*/

		}while(!correctInput(input));
		if(input == 'w'|| input == 'W' || input == 'A'|| input == 'a' || input == 's' ||input == 'S' || input == 'd' || input == 'D')
		{
			char todo;
			if(!handleMovement(input, todo))
			{
				std::cout << "Can't go that way!\n";
				continue;
			}
			else
				printMap();

			if(todo == 'I')// add item(it is "under" the hero :D) to hero inventory
			{
				Item item = this->currentLevel.getItemAt(smiley.getPositionX(), smiley.getPositionY());
				smiley.pickUPItem(item);
				this->currentLevel.removeItem(item);
			}
			if(todo == 'M') // fight monster
			{
				Monster m = this->currentLevel.getMonsterAt(this->smiley.getPositionX(), this->smiley.getPositionY());
				fightMonster(m);
				this->currentLevel.removeMonster(m);
				printMap();
			}
			if(todo == 'E') 
			{
				if(!loadNextLevel())
					gameOver = true;	
				printMap();
			}
		}
		else if(input == 'i' || input == 'I')
		{
			printHeroInventory();
		}
		else if(input == 'o' || input == 'O')
		{
			int selected = 0;
			selected = printOptionsMenu();
			if(selected == 0)
			{
				saveGame("Save.txt");
				_sleep(1000);
				printMap();
			}
			else if(selected == 1)
			{
				if(loadGame("Save.txt"))
				{
					std::cout << "Load successful!\n";
					_sleep(1000);
				}
				printMap();
			}
			else if(selected == 2)
			{
				std::cout << "\n Are you sure you want to quit?(y/n)\n";
				do
				{
					char YNinput = _getch();
					if(YNinput == 'y' || YNinput == 'Y')
					{
						std::cout << "\nSave before quitting?(y/n)\n";
						do
						{
							YNinput = _getch();
							if(YNinput == 'y' || YNinput == 'Y')
							{
								saveGame("Save.txt");
								gameOver = true;
								break;
							}
							if(YNinput == 'n' || YNinput == 'N')
							{
								gameOver = true;
								break;
							}
						}while(YNinput == 'y' || YNinput == 'Y' || YNinput == 'n' || YNinput == 'N');
					}
					if(input == 'n' || input == 'N' )
					{
						printMap();
						break;
					}
				
				}while(input == 'y' || input == 'Y' || input == 'n' || input == 'N');
			}
		}
		if(this->smiley.getHealth() == 0)
			gameOver = true;

	}while(!gameOver);
	if(this->smiley.getHealth() == 0)
	{
		std::cout << "Smiley is dead\n Game over!!!\n";
		_sleep(5000);
		playGame();
	}
	else if(complete)
	{
		std::cout << "Congratulations!!! You have completed \"Smiley's adventure !\" \n";
		_sleep(2000);
		playGame();
	}
}