#include "Maze.h"
#include "List.h"
#include "StringCompressor.h"


int main(int argc, char* argv[])
{
	try		
	{
		if(argc < 2)
		{
			std::cout << "Error: exprecting at least 2 arguments!\n";
		}
		linkedList<char*> allCompressedStrings;
		for(int i = 1; i < argc; i++)
		{
			Maze test;
			test.readMapFromFile(argv[i]);
			test.printMap();
			char* instructions = test.solveMaze();	
			std::cout << "Regular instructions: " << instructions << std::endl;
			char* compressedString = StringCompressor::compressString(instructions);
			std::cout <<  "compressed Instructions: " << compressedString << std::endl;
			delete [] instructions;
			delete [] compressedString;
		}
	}
	catch(const char* msg)
	{
		std::cout << msg << std::endl; 
	}
	catch(...)
	{
		
	}

	return 0;
}