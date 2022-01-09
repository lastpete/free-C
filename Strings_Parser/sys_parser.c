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
		printf("%s", "SYNTAX ERROR: sys_parser.exe {strings | floss} <ABSOLUTE PATH TO INPUT FILE> <SEARCH PREFIX>");
		exit(1);
	}

	/* Declare variables */
	char *search_term = (char *)malloc(sizeof(argv[3]));
	char cmd[100];
	char dump[50];
	
	FILE *cmd_ptr;

	/* Construct command */
	strncpy(cmd, argv[1], strlen(argv[1]) + 1);
	strcat(cmd, " \"");
	strcat(cmd, argv[2]);
	strcat(cmd, "\"");

	cmd_ptr = popen(cmd, "r");

	/* Check for successful command execution */
	if (cmd_ptr == NULL)
	{
		printf("%s\n", "Error: Command failed to run.");
		exit(1);
	}


	/* Parse output */
	if (!strcmp(argv[3], "-api"))
	{
		// Iterate over each line in output
		while (fgets(dump, sizeof(dump), cmd_ptr) != 0)
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

		/* Close sys connection */
		pclose(cmd_ptr);
	}
	else
	{
		/* Declare variables */
		int slice_size = strlen(argv[3]);		// determine length of CMD-line search-term
		char sliced_string[slice_size + 1];		// sliced 'fgets' string dump
		
		// Iterate over each line in input file
		while (fgets(dump, sizeof(dump), cmd_ptr) != 0)
		{
			// Removes '\n' if exists
			if(dump[strlen(dump) - 1] == '\n')
			{
				dump[strlen(dump) - 1] = '\0';
			}
			
			// Copy user input search term from each
			strncpy(sliced_string, dump, slice_size);
			search_term = strstr(sliced_string, argv[3]);
			
			// Print, if match
			if (search_term != NULL)
			{
				printf("%s\n", dump);
			}
		}

		/* Close sys connection */
		pclose(cmd_ptr);
	}

	return 0;
}