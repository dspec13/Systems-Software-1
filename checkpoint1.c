/*
	CSE 109: Spring 2018
	Dylan Spector
	drs320
	Takes in lines & commands from user. Outputs an edited line.
	Program #1
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void reverseWord(char* line, size_t length);    // Satisfies -r
void reverseLine(char* line, size_t length);    // Satisfies -e
void toggle(char* line, size_t length);         // Satisfies -t
size_t removeDigits(char* line, size_t length); // Satisfies -n  (returns length of resulting line.)

void reverseWord(char* line, size_t length)
{
	int wordStart = -1;
	int wordStop = -1;
	int tempChar = -1;

	for(int i = 0; i < length; i++)    // Loop through every char
	{
		if(isspace(line[i]))           // If a space is found.
		{
			if(wordStart == -1)        // If wordStart hasn't been found.
			{
				wordStart = i+1;       // set WordStart.
			}
			else                       // Else wordStop hasn't been found.
			{
				wordStop = i-1;        // set wordStop
				for(int j = wordStart; j <= wordStop+1; j++)
				{
					if(j >= wordStop)
					{
						wordStart = -1;
						wordStop = -1;
						i--;
					}
					else
					{
						tempChar = line[j];
						line[j] = line[wordStop];
						line[wordStop] = tempChar;
						wordStop--;
					}
				}
			}
		}
		else if(i == 0)         // if the 1st character is not a space
		{
			wordStart = i;
		}
		else if(i == length-1)  // if the last character is not a space
		{
			wordStop = i;
			for(int j = wordStart; j <= wordStop; j++)
			{
				if(wordStart >= wordStop)
				{
					wordStart = -1;
					wordStop  = -1;
					break;
				}
				else
				{
					tempChar = line[j];
					line[j] = line[wordStop];
					line[wordStop] = tempChar;
					wordStop--;
				}
			}
		}
	}
}

void reverseLine(char* line, size_t length)
{
	int stop = length - 1;
	int temp = -1;

	for(int start = 0; start < stop; start++)
	{
		temp = line[start];
		line[start] = line[stop];
		line[stop] = temp;
		stop--;
	}
}

void toggle(char* line, size_t length)
{
	for(int i = 0; i < length; i++)
	{
		if(isascii(line[i]))
		{
			if(islower(line[i]))
			{
				line[i] = toupper(line[i]);
			}
			else
			{
				line[i] = tolower(line[i]);
			}
		}
	}
}

size_t removeDigits(char* line, size_t length)
{
	int tempChar = -1;
	int digitPos = -1;
	for(int i = 0; i < length; i++)
	{
		if(line[i] >= 0x30 && line[i] <= 0x39) // If char is '0'-'9'
		{
			line[i] = 0x00;                    // Replace digit w/ [NULL]
			digitPos = i;
			for(int j = digitPos+1; j < length; j++)
			{
				if(line[j] == 0x00) // if the next char is [NULL], you are at the end of line.
				{
					break;
				}
				else
				{
					tempChar = line[j];
					line[j] = line[digitPos];
					line[digitPos] = tempChar;
					digitPos++;
				}
			}
			i--; // Check to see if the last char was a digit.
		}
	}

	return strlen(line); // Will return the length of the resulting line.
}
