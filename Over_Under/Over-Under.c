#include <stdio.h>
#include <stdlib.h>

#define RANGE 27
#define TYPES 20

// The bin() function listed at the bottom, used to convert to binary was copied off of Geeks For Geeks here:
// 				https://www.geeksforgeeks.org/binary-representation-of-a-given-number/

// This program is only supposed to display a visual for over/under-flows for C-Language data types.
// Follow the prompted instructions and everything works. TONS of errors exist throughout. -Pete


void displayMenu(char dataType[8][TYPES], char dataSize[8][19], char dataLowRange[8][RANGE], char dataHighRange[8][RANGE]);
void bin(unsigned n);

int main(int argc, char* argv[])
{
	int userInput;
	int intCountStart;
	unsigned int uIntCountStart;
	char O_U;
	char dataType[8][TYPES] = {"Character", "Unsigned Char.", "Integer", "Unsigned Int.", "Short", "Unsigned Short", "Long", "Unsigned Long"};
	char dataSize[8][19] = {"1-byte / 8-bits", "1-byte / 8-bits", "4-bytes / 32-bits", "4-bytes / 32-bits", "2-bytes / 16-bits", "2-bytes / 16-bits", "8-bytes / 64-bits", "8-bytes / 64-bits",};
	char dataLowRange[8][RANGE] = {"-128", "0", "-2,147,483,648", "0", "-32,768", "0", "-9,223,372,036,854,775,808", "0"};
	char dataHighRange[8][RANGE] = {"127", "255", "2,147,483,647", "4,294,967,295", "32,767", "65,535", "9,223,372,036,854,775,807", "18,446,744,073,709,551,615"};
	char charCountStart;
	unsigned char uCharCountStart;
	short shortCountStart;
	unsigned short uShortCountStart;
	long longCountStart;
	unsigned long uLongCountStart;


	while(userInput != -1)
	{
		userInput = 0;
		displayMenu(dataType, dataSize, dataLowRange, dataHighRange);
		printf("Selection: ");
		scanf("%d", &userInput);
		printf("%s selected!\n", dataType[userInput - 1]);
		printf("This program will print 10 numbers at an edge of your choice.\n");
		printf("Please enter \"O\" for an Overflow, or \"U\" for an Underflow of %s: ", dataType[userInput - 1]);
		scanf("\n%c", &O_U);
		if(userInput == 1)
		{
			if(O_U == 'O' || O_U == 'o' )
			{
				printf("Starting position is: 123\n");
				charCountStart = 123;
				for(int i = 0; i < 10; ++i)
				{
					if(charCountStart >= 0)
					{
						printf(" %20d | ", charCountStart);
						bin(charCountStart);
						charCountStart++;
					}
					else
					{
						printf("%21d | ", charCountStart);
						bin(charCountStart);
						charCountStart++;
					}
				}
			}
			else
			{
				printf("Starting position is: -124\n");
				charCountStart = -124;
				for(int i = 0; i < 10; ++i)
				{
					if(charCountStart >= 0)
					{
						printf(" %20d | ", charCountStart);
						bin(charCountStart);
						charCountStart--;
					}
					else
					{
						printf("%21d | ", charCountStart);
						bin(charCountStart);
						charCountStart--;
					}
				}
			}
		}
		else if(userInput == 2)
		{
			if(O_U == 'O' || O_U == 'o' )
			{
				printf("Starting position is: 251\n");
				uCharCountStart = 251;
				for(int i = 0; i < 10; ++i)
				{
					if(uCharCountStart >= 0)
					{
						printf(" %20d | ", uCharCountStart);
						bin(uCharCountStart);
						uCharCountStart++;
					}
					else
					{
						printf("%21d | ", uCharCountStart);
						bin(uCharCountStart);
						uCharCountStart++;
					}
				}
			}
			else
			{
				printf("Starting position is: 4\n");
				uCharCountStart = 4;
				for(int i = 0; i < 10; ++i)
				{
					if(uCharCountStart >= 0)
					{
						printf(" %20d | ", uCharCountStart);
						bin(uCharCountStart);
						uCharCountStart--;
					}
					else
					{
						printf("%21d | ", uCharCountStart);
						bin(uCharCountStart);
						uCharCountStart--;
					}
				}
			}
		}
		else if(userInput == 3)
		{
			if(O_U == 'O' || O_U == 'o' )
			{
				printf("Starting position is: 2,147,483,643\n");
				intCountStart = 2147483643;
				for(int i = 0; i < 10; ++i)
				{
					if(intCountStart >= 0)
					{
						printf(" %20d | ", intCountStart);
						bin(intCountStart);
						intCountStart++;
					}
					else
					{
						printf("%21d | ", intCountStart);
						bin(intCountStart);
						intCountStart++;
					}
				}
			}
			else
			{
				printf("Starting position is: -2,147,483,644\n");
				intCountStart = -2147483644;
				for(int i = 0; i < 10; ++i)
				{
					if(intCountStart >= 0)
					{
						printf(" %20d | ", intCountStart);
						bin(intCountStart);
						intCountStart--;
					}
					else
					{
						printf("%21d | ", intCountStart);
						bin(intCountStart);
						intCountStart--;
					}
				}
			}
		}
		else if(userInput == 4)
		{
			if(O_U == 'O' || O_U == 'o' )
			{
				printf("Starting position is: 4,294,967,291\n");
				uIntCountStart = 4294967291;
				for(int i = 0; i < 10; ++i)
				{
					if(uIntCountStart >= 0)
					{
						printf(" %20u | ", uIntCountStart);
						bin(uIntCountStart);
						uIntCountStart++;
					}
					else
					{
						printf("%21u | ", uIntCountStart);
						bin(uIntCountStart);
						uIntCountStart++;
					}
				}
			}
			else
			{
				printf("Starting position is: 4\n");
				uIntCountStart = 4;
				for(int i = 0; i < 10; ++i)
				{
					if(uIntCountStart >= 0)
					{
						printf(" %20u | ", uIntCountStart);
						bin(uIntCountStart);
						uIntCountStart--;
					}
					else
					{
						printf("%21u | ", uIntCountStart);
						bin(uIntCountStart);
						uIntCountStart--;
					}
				}
			}
		}
		else if(userInput == 5)
		{
			if(O_U == 'O' || O_U == 'o' )
			{
				printf("Starting position is: 32,763\n");
				shortCountStart = 32763;
				for(int i = 0; i < 10; ++i)
				{
					if(shortCountStart >= 0)
					{
						printf(" %20hd | ", shortCountStart);
						bin(shortCountStart);
						shortCountStart++;
					}
					else
					{
						printf("%21hd | ", shortCountStart);
						bin(shortCountStart);
						shortCountStart++;
					}
				}
			}
			else
			{
				printf("Starting position is: -32,764\n");
				shortCountStart = -32764;
				for(int i = 0; i < 10; ++i)
				{
					if(shortCountStart >= 0)
					{
						printf(" %20hd | ", shortCountStart);
						bin(shortCountStart);
						shortCountStart--;
					}
					else
					{
						printf("%21hd | ", shortCountStart);
						bin(shortCountStart);
						shortCountStart--;
					}
				}
			}
		}
		else if(userInput == 6)
		{
			if(O_U == 'O' || O_U == 'o' )
			{
				printf("Starting position is: 65,531\n");
				uShortCountStart = 65531;
				for(int i = 0; i < 10; ++i)
				{
					if(uShortCountStart >= 0)
					{
						printf(" %20hu | ", uShortCountStart);
						bin(uShortCountStart);
						uShortCountStart++;
					}
					else
					{
						printf("%21hu | ", uShortCountStart);
						bin(uShortCountStart);
						uShortCountStart++;
					}
				}
			}
			else
			{
				printf("Starting position is: 4\n");
				uShortCountStart = 4;
				for(int i = 0; i < 10; ++i)
				{
					if(uShortCountStart >= 0)
					{
						printf(" %20hu | ", uShortCountStart);
						bin(uShortCountStart);
						uShortCountStart--;
					}
					else
					{
						printf("%21hu | ", uShortCountStart);
						bin(uShortCountStart);
						uShortCountStart--;
					}
				}
			}
		}
		else if(userInput == 7)
		{
			if(O_U == 'O' || O_U == 'o' )
			{
				printf("Starting position is: 9,223,372,036,854,775,803\n");
				longCountStart = 9223372036854775803;
				for(int i = 0; i < 10; ++i)
				{
					if(longCountStart >= 0)
					{
						printf(" %20ld | ", longCountStart);
						bin(longCountStart);
						longCountStart++;
					}
					else
					{
						printf("%21ld | ", longCountStart);
						bin(longCountStart);
						longCountStart++;
					}
				}
			}
			else
			{
				printf("Starting position is: -9,223,372,036,854,775,804\n");
				longCountStart = -9223372036854775804;
				for(int i = 0; i < 10; ++i)
				{
					if(longCountStart >= 0)
					{
						printf(" %20ld | ", longCountStart);
						bin(longCountStart);
						longCountStart--;
					}
					else
					{
						printf("%21ld | ", longCountStart);
						bin(longCountStart);
						longCountStart--;
					}
				}
			}
		}
		else if(userInput == 8)
		{
			if(O_U == 'O' || O_U == 'o' )
			{
				printf("Starting position is: 18,446,744,073,709,551,611\n");
				uLongCountStart = 18446744073709551611;
				for(int i = 0; i < 10; ++i)
				{
					if(uLongCountStart >= 0)
					{
						printf(" %20lu | ", uLongCountStart);
						bin(uLongCountStart);
						uLongCountStart++;
					}
					else
					{
						printf("%21lu | ", uLongCountStart);
						bin(uLongCountStart);
						uLongCountStart++;
					}
				}
			}
			else
			{
				printf("Starting position is: 4\n");
				uLongCountStart = 4;
				for(int i = 0; i < 10; ++i)
				{
					if(uLongCountStart >= 0)
					{
						printf(" %20lu | ", uLongCountStart);
						bin(uLongCountStart);
						uLongCountStart--;
					}
					else
					{
						printf("%21lu | ", uLongCountStart);
						bin(uLongCountStart);
						uLongCountStart--;
					}
				}
			}
		}
		printf("Enter \"-1\" to exit, or any number to continue: ");
		scanf("%d", &userInput);
		system("clear");

	}

	return 0;
}

void displayMenu(char dataType[8][TYPES], char dataSize[8][19], char dataLowRange[8][RANGE], char dataHighRange[8][RANGE])
{

	printf("================================================================================================\n");
	printf("%14s%5s%12s%8s%32s%26s\n", "Data Type", "|", "Size", "|", "Range", "|");
	printf("================================================================================================\n");
	for(int i = 0; i < 8; i++)
	{
		printf("%d) %14s%2s%18s%2s%27s%2s %-26s%2s\n", (i + 1), dataType[i], "|", dataSize[i], "|", dataLowRange[i], "-", dataHighRange[i], "|");
	}
	printf("================================================================================================\n");
	printf("%65s%32s\n", "Please choose, or enter \"-1\" to exit.", "|");
	printf("================================================================================================\n");
}

// Taken from GeeksForGeeks.org: https://www.geeksforgeeks.org/binary-representation-of-a-given-number/
// Only adding the bottom printf() myself
void bin(unsigned n)
{
    unsigned i;

    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
    printf("\n"); // ONLY LINE ADDED BY ME. It's garbage, couldn't you tell?
}