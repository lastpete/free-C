#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <unistd.h> //sleep() function

// List Structure
typedef struct node
{
	struct node *prev;
	int pos;
	char data;
	struct node *next;

} node;

/* TODO:
	- menu				[ ]
	- display_list		[x]
	- count_nodes		[x]
	- create_list		[x]
	- 1.add_node		[x]
	- 2.add_front		[x]
	- 3.add_end			[x]
	- 4.delete_node		[x]
	- 5.delete_front	[x]
	- 6.delete_end		[x]
	- 7.print_info		[x]
	- 8.quit			[x]
*/

void menu(node *LL);
void display_list(node *LL);
int count_nodes(node *LL);
node *create_list(char data);
node *add_node(node *LL, char data, int position);
node *add_front(node *LL, char data);
node *add_end(node *LL, char data);
node *delete_node(node *LL, int position);
node *delete_front(node *LL);
node *delete_end(node *LL);
void print_info(node *LL);

int main(int argc, char *argv[])
{
	// DECLARE VARIABLES
	node *dl = (node*)malloc(sizeof(node));
	char data;
	int user_choice;
	int index_pos;
	int node_count;
	int exit_flag = 1;

	system("cls");
	printf("\nPlease input a single element to start the first list node: ");
	scanf(" %1c", &data);

	dl->prev = NULL;
	dl->pos = 1;
	dl->data = data;
	dl->next = NULL;

	while(exit_flag != 0)
	{
		if(dl == NULL)
		{
			exit_flag = 0;
			printf(" Goodbye!\n");
			break;
		}
		system("cls");
		menu(dl);
		display_list(dl);
		printf(" Menu selection: ");
		scanf(" %i", &user_choice);

		switch (user_choice)
		{
			case 1:
				// ADD NODE
				node_count = count_nodes(dl);
				printf(" There are %i total nodes.\n", node_count);
				sleep(1);
				index_pos = 0;
				while(index_pos < 1 || index_pos > node_count + 1)
				{
					printf(" Please input the position you wish to insert data at [1 - %i]: ", node_count + 1);
					scanf(" %i", &index_pos);
				}
				getchar();

				printf(" Please input an element to replace it with: ");
				scanf(" %1c", &data);
				getchar();

				dl = add_node(dl, data, index_pos);
				break;
			case 2:
				// ADD FRONT

				printf(" Please input a single element: ");
				scanf(" %1c", &data);

				dl = add_front(dl, data);
				break;
			case 3:
				// ADD END

				printf(" Please input a single element: ");
				scanf(" %1c", &data);

				dl = add_end(dl, data);
				break;
			case 4:
				// DELETE NODE

				node_count = count_nodes(dl);
				printf(" There are %i total nodes.\n", node_count);
				sleep(1);
				index_pos = 0;
				
				while(index_pos < 1 || index_pos > node_count)
				{
					printf(" Please input the position you wish to delete [1 - %i]: ", node_count);
					scanf(" %i", &index_pos);
				}
				getchar();

				dl = delete_node(dl, index_pos);
				break;
			case 5:
				// DELETE FRONT

				dl = delete_front(dl);
				break;
			case 6:
				// DELETE END

				dl = delete_end(dl);
				break;
			case 7:
				// PRINT LIST
				printf(" ===================\n");

				print_info(dl);
				break;
			case 8:
				// QUIT

				exit_flag = 0;
				break;
			default:
				printf(" Please choose from the menu [1 - 9].");
				sleep(2);

				break;
		}
	}
	

	return 0;
}

void menu(node *LL)
{
	int node_count = count_nodes(LL);

	printf("\n%s\n%s%3s%s%8c\n%s%3s%s%7c\n%s%3s%s%9c\n%s%3s%s%5c\n%s%3s%s%4c\n%s%3s%s%6c\n%s%3s%s%6c\n%s%3s%s%12c\n", " ===================", "| ", "1. ", "Add Node", '|', "| ", "2. ", "Add Front", '|', "| ", "3. ", "Add End", '|', "| ", "4. ", "Delete Node", '|', "| ", "5. ", "Delete Front", '|', "| ", "6. ", "Delete End", '|', "| ", "7. ", "Print Info", '|', "| ", "8. ", "Quit", '|');
	printf("%s\n%c%17s%3c\n%c%16s%4c\n%c%19s%c\n%c%15s%i%s\n%s\n", " ===================", '|', "Please input the", '|', '|', "number relating", '|', '|', "to your selection.", '|', '|', "(List length [", node_count, "]) |", " ===================");
}

void display_list(node *LL)
{
	node *tmp = LL;
	int node_count = count_nodes(LL);

	printf("     ");
	for(int i = 1; i <= node_count; i++)
	{
		printf("     ===");
	}
	printf("\n");
	for(int i = 1; i <= node_count; i++)
	{
		if(node_count == 1)
		{
			printf("(NULL)<--|%2c |-->(NULL)", tmp->data);
		}
		else if(i == 1)
		{
			printf("(NULL)<--|%2c |", tmp->data);
		}
		else
		{
			printf("<->");
			if(node_count == i)
			{
				printf("|%2c |-->(NULL)", tmp->data);
			}
			else
			{
				printf("|%2c |", tmp->data);
			}
		}
		tmp = tmp->next;
	}
	printf("\n     ");
	for(int i = 1; i <= node_count; i++)
	{
		printf("     ===");
	}
	printf("\n ===================\n");
	free(tmp);
}

node *create_list(char data)
{
	node *New_Node = (node*)malloc(sizeof(node));

	New_Node->prev = NULL;
	New_Node->pos = 1;
	New_Node->data = data;
	New_Node->next = NULL;


	return New_Node;
}

node *add_node(node *LL, char data, int position)
{
	node *New_Node = (node*)malloc(sizeof(node));
	int node_count = count_nodes(LL);

	New_Node->data = data;

	if(position == 1)
	{
		New_Node->prev = NULL;
		New_Node->pos = 1;
		New_Node->next = LL;
		LL->prev = New_Node;
		while(LL != NULL)
		{
			LL->pos++;
			LL = LL->next;
		}


		return New_Node;
	}
	else
	{
		node *tmp = LL;

		if(position == node_count + 1)
		{
			while(tmp->next != NULL)
			{
				tmp = tmp->next;
			}
			tmp->next = New_Node;
			New_Node->prev = tmp;
			New_Node->pos = position;
			New_Node->next = NULL;
		}
		else
		{
			while(tmp->pos != position)
			{
				tmp = tmp->next;
			}
			tmp->prev->next = New_Node;
			New_Node->prev = tmp->prev;
			tmp->prev = New_Node;
			New_Node->pos = tmp->pos;
			New_Node->next = tmp;
			while(tmp != NULL)
			{
				tmp->pos++;
				tmp = tmp->next;
			}
		}


		return LL;
	}
}

node *add_front(node *LL, char data)
{
	node *New_Node = (node*)malloc(sizeof(node));

	New_Node->prev = NULL;
	New_Node->pos = 1;
	New_Node->data = data;
	New_Node->next = LL;
	LL->prev = New_Node;

	while(LL != NULL)
	{
		LL->pos++;
		LL = LL->next;
	}


	return New_Node;
}

node *add_end(node *LL, char data)
{
	node *New_Node = (node*)malloc(sizeof(node));

	New_Node->data = data;
	New_Node->next = NULL;
	if(LL->next == NULL)
	{
		New_Node->pos = LL->pos + 1;
		New_Node->prev = LL;
		LL->next = New_Node;
	}
	else
	{
		node *tmp = LL;
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		New_Node->pos = tmp->pos + 1;
		New_Node->prev = tmp;
		tmp->next = New_Node;
	}


	return LL;
}

node *delete_node(node *LL, int position)
{
	node *tmp = LL;
	int node_count = count_nodes(LL);

	if(position == 1)
	{
		if(node_count == 1)
		{
			free(tmp);


			return NULL;
		}
		else
		{
			LL = LL->next;
			LL->prev = NULL;
		}
	}
	else if(position == node_count)
	{
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->prev->next = NULL;
	}
	else
	{
		while(tmp->pos != position)
		{
			tmp = tmp->next;
		}
		if(tmp->prev != NULL)
		{
			tmp->prev->next = tmp->next;
			tmp->next->prev = tmp->prev;
		}
		else if(tmp->next != NULL)
		{
			tmp->next->prev = tmp->prev;
			tmp->prev->next = tmp->next;
		}
	}

	while(tmp != NULL)
	{
		tmp->pos--;
		tmp = tmp->next;
	}
	free(tmp);


	return LL;
}

node *delete_front(node *LL)
{
	int node_count = count_nodes(LL);

	node *tmp = LL;

	if(node_count == 1)
	{
		free(tmp);


		return NULL;
	}
	else
	{
		LL = LL->next;
		LL->prev = NULL;
		while(tmp != NULL)
		{
			tmp->pos--;
			tmp = tmp->next;
		}
		free(tmp);


		return LL;
	}
}

node *delete_end(node *LL)
{
	int node_count = count_nodes(LL);

	node *tmp = LL;

	if(node_count == 1)
	{
		free(tmp);

		
		return NULL;
	}
	else
	{
		while(tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->prev->next = NULL;
		free(tmp);


		return LL;
	}
}

void print_info(node *LL)
{
	int node_count = count_nodes(LL);

	while(LL != NULL)
	{
		if(LL->prev == NULL && LL->next == NULL)
		{
			printf("%12s: %c\n%12s: %i\n%12s: %c\n%12s: %p\n%12s: %c\n", "[Prev. Node]", NULL, "Node Number", LL->pos, "Data", LL->data, "Mem. Address", LL->data, "[Next Node]", NULL);
		}
		else if(LL->prev == NULL)
		{
			printf("%12s: %c\n%12s: %i\n%12s: %c\n%12s: %p\n", "[Prev. Node]", NULL, "Node Number", LL->pos, "Data", LL->data, "Mem. Address", LL->data);
			if(LL->next != NULL)
			{
				printf("%12s: %i\n%12s: %c\n", "[Next Node]", LL->next->pos, "[Next Data]", LL->next->data);
			}
			else
			{
				printf("%12c: %i\n", "[Next Node]", NULL);
			}
		}
		else if(LL->next == NULL)
		{
			printf("%12s: %i\n%12s: %c\n%12s: %i\n%12s: %c\n%12s: %p\n%12s: %c\n", "[Prev. Node]", LL->prev->pos, "[Prev. Data]", LL->prev->data, "Node Number", LL->pos, "Data", LL->data, "Mem. Address", LL->data, "[Next Node]", NULL);
		}
		else
		{
			printf("%12s: %i\n%12s: %c\n%12s: %i\n%12s: %c\n%12s: %p\n%12s: %i\n%12s: %c\n", "[Prev. Node]", LL->prev->pos, "[Prev. Data]", LL->prev->data, "Node Number", LL->pos, "Data", LL->data, "Mem. Address", LL->data, "[Next Node]", LL->next->pos, "[Next Data]", LL->next->data);
		}
		printf("%s\n", " ===================");
		LL = LL->next;
		sleep(2);
	}
	sleep(3);
}

int count_nodes(node *LL)
{
	int node_count = 0;

	while(LL != NULL)
	{
		node_count++;
		LL = LL->next;
	}


	return node_count;
}