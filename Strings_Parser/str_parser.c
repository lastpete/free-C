#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api.h"

int main(int argc, char *argv[])
{
	/*
		The whole point of this program is to sharpen my C chops and to make string
		more automated based on user controlled input.
	*/

	/* Check for parameters */
	if (argc < 3)
	{
		printf("%s", "SYNTAX ERROR: str_parser.exe <ABSOLUTE PATH TO INPUT FILE>.<EXT> <SEARCH PREFIX>");
		exit(1);
	}

	/* Open file */
	FILE *input_file;

	input_file = fopen(argv[1], "r");

	if (input_file == NULL)
	{
		printf("%s", "ERROR: File failed to open correctly.");
		exit(1);
	}

	/* Declare variables */
	char dump[50];							// 'fgets' dump
	char *search_term;						// pointer to the 'argv[2]' prefix-search
	

	/* Read file */
	if (!strcmp(argv[2], "-api"))
	{
		// Iterate over each line in input file		
		while (fgets(dump, sizeof(dump), input_file) != 0)
		{
			// Removes '\n' if exists
			if(dump[strlen(dump) - 1] == '\n')
			{
				dump[strlen(dump) - 1] = '\0';
			}

			// Cycles over API list from 'api.h'
			for (int i = 0; i < 364; i++)
			{
				if (!strcmp(dump, api_list[i]))
				{
					printf("%s\n", dump);
				}
			}
		}

		/* Close file */
		fclose(input_file);
	}
	else
	{
		/* Declare variables */
		int slice_size = strlen(argv[2]);		// determine length of CMD-line search-term
		char sliced_string[slice_size + 1];		// sliced 'fgets' string dump
		
		// Iterate over each line in input file
		while (fgets(dump, sizeof(dump), input_file) != 0)
		{
			// Removes '\n' if exists
			if(dump[strlen(dump) - 1] == '\n')
			{
				dump[strlen(dump) - 1] = '\0';
			}
			
			// Copy user input search term from each
			strncpy(sliced_string, dump, slice_size);
			search_term = strstr(sliced_string, argv[2]);
			
			// Print, if match
			if (search_term != NULL)
			{
				printf("%s\n", dump);
			}
		}

		/* Close file */
		fclose(input_file);
	}


	return 0;
}