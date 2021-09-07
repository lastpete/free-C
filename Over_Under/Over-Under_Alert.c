#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>


int main()
{
	//FGETS() string length capture and comparison to STRTOL() converted type UNSIGNED INT===========================
	char dump1[500]; // dump for user input
	char dump2[500]; // dump to capture itoa()
	char *ptr; // strtol() /dev/null
	int beforeLength; // for str length
	int afterLength; // to capture itoa() length
	int characterCount = 0; // to count the total number of characters
	int testDump1; // FINAL CHECK CHAR TO INT, CHAR BY CHAR
	int testDump2; // FINAL CHECK CHAR TO INT, CHAR BY CHAR
	unsigned int ui; // 0 - 4294967295 <--- 10 digits/characters MAX

	printf("Please enter digits [0 - 4294967295]: ");
	fgets(dump1, sizeof(dump1), stdin);
	printf("Entered: ");
	for(int i = 0; dump1[i] != '\0' && dump1[i] != '\n'; ++i)
	{
		printf("%c", dump1[i]);
		characterCount++;
	}
	beforeLength = characterCount;
	characterCount = 0;
	printf("\nLength of input counted: %d\n", beforeLength);
	ui = strtol(dump1, &ptr, 10);
	printf("UNSIGNED INT: %u\n", ui);
	sprintf(dump2, "%u", ui);
	printf("Entered: ");
	for(int i = 0; dump2[i] != '\0' && dump2[i] != '\n'; ++i)
	{
		printf("%c", dump2[i]);
		characterCount++;
	}
	afterLength = characterCount;
	printf("\nLENGTH OF UNSIGNED INT: %d\n", afterLength);
	if(afterLength < beforeLength || afterLength == beforeLength)
	{
		for(int j = 0; dump1[j] != '\0' && dump1[j] != '\n'; ++j)
		{
			for(int k = 0; dump2[k] != '\0' && dump2[k] != '\n'; ++k)
			{
				if(dump1[j] > dump2[k])
				{
					printf("CHAR by CHAR\n");
					printf("1: %c ||2: %c\n", dump1[j], dump2[k]);
					printf("POSSIBLE OVERFLOW!\n");
					exit(1);
				}
				printf("SKIP! 1: %c ||2: %c\n", dump1[j], dump2[k]);
				break;
			}
		}
	}
	//FGETS() string length capture and comparison to STRTOL() converted type UNSIGNED INT===========================
}