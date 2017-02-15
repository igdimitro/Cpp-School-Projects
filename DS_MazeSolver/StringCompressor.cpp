#include "StringCompressor.h"
#include <String.h>
#include <cmath>

void numberToString(int& number, char* numberString, int numberOfDigits)
{	

	int pos = numberOfDigits - 1;
	numberString[numberOfDigits] = '\0';
	while(number)
	{
		numberString[pos] = '0' + (char)(number % 10);
		number /= 10;
		numberOfDigits--;
		pos--;
	}

}

char* StringCompressor::compressString(char* string)
{

	int stringLength = strlen(string);
	char* compressedString = new char[stringLength + 1];
	memset(compressedString, '\0', stringLength);
	int currentPos = 0;
	while(*string)
	{
		int currentCharCount = 0;
		char currentChar = *string;
		while(currentChar == *string)
		{
			currentCharCount++;
			string++;
		}
		if(currentCharCount > 1 && currentCharCount >= 10)
		{
			int numberOfDigits = log10(currentCharCount) + 1;
			char* charCountString = new char[numberOfDigits + 1];
			numberToString(currentCharCount, charCountString, numberOfDigits);
			int pos = 0;
			while(pos != numberOfDigits)
			{
				compressedString[currentPos] = charCountString[pos];
				currentPos++;
				pos++;
			}
			delete [] charCountString;
		}
		else if(currentCharCount > 1 && currentCharCount < 10)
		{
			compressedString[currentPos] = '0' + (char)currentCharCount;
			currentPos++;
		}
		compressedString[currentPos] = currentChar;
		currentPos++;
	}
	return compressedString;

}





