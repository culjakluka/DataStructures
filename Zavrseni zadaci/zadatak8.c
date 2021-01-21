#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct Dir;
typedef struct Dir* Position;
typedef struct Dir Dir;
typedef struct Dir {
	char* dirname;
	Position sibling;
	Position child;
};

struct stack;
typedef struct stack* StackPosition;
typedef struct stack Stack;
typedef struct stack {
	Position Dir;
	StackPosition next;
};

int MenuChoice(char*);
Position AddDirectory(Position, char*);
int SubdirectoryPrint(Position);
Position Subdirectory(Position, char*, StackPosition);
int Push(Position, StackPosition);
Position ParentDirectory(Position, StackPosition);

int main()
{
	Dir root;
	root.sibling = NULL;
	root.child = NULL;
	char* cmd_line = NULL;
	char* buff = NULL;
	int pos = 0;
	Position last = NULL;
	Stack stack;
	stack.Dir = NULL;
	stack.next = NULL;
	StackPosition NewNode = NULL;


	root.dirname = (char*)malloc(4 * sizeof(char));
	if (NULL == root.dirname)
		printf("An error occured!\n");

	strcpy(root.dirname, "Root");

	last = &root;

	cmd_line = (char*)malloc(30 * sizeof(char));
	if (NULL == cmd_line)
		printf("An error occured!\n");

	memset(cmd_line, 0, 30);

	buff = (char*)malloc(30 * sizeof(char));
	if (NULL == buff)
		printf("An error occured!\n");

	memset(buff, 0, 30);

	NewNode = (StackPosition)malloc(sizeof(Stack));
	if (NULL == NewNode)
		printf("An error occured!\n");

	NewNode->next = NULL;
	NewNode->Dir = NULL;

	NewNode->Dir = last;
	NewNode->next = stack.next;
	stack.next = NewNode;

	while (strcmp(buff, "exit"))
	{
		memset(cmd_line, 0, 30);
		gets(cmd_line);
		sscanf(cmd_line, "%s%n", buff, &pos);

		switch (MenuChoice(buff))
		{
		case 1://md
			memset(buff, 0, 30);
			sscanf(cmd_line + pos, "%s", buff);
			last = AddDirectory(last, buff);
			break;
		case 2://cd..
			last = ParentDirectory(last, &stack);
			break;
		case 3://cd Dir
			memset(buff, 0, 30);
			sscanf(cmd_line + pos, "%s", buff);
			last = Subdirectory(last->child, buff, &stack);
			break;
		case 4://Dir
			if (SubdirectoryPrint(last) != 0)
				printf("An error occured!\n");
			break;
		case 5://exit
			break;
		default:
			printf("%s is not recognized as an internal or external command, operable program or batch file.", buff);
			break;
		}
	}

	free(cmd_line);
	free(buff);

	return 0;
}

Position ParentDirectory(Position last, StackPosition stack)
{
	StackPosition tmp = NULL;
	Position temp = NULL;

	tmp = stack->next;
	stack->next = tmp->next;

	temp = stack->next->Dir;
	free(tmp);

	return temp;
}

Position Subdirectory(Position lastchild, char* buff, StackPosition stack)
{
	Position current = NULL;

	current = lastchild;

	while (strcmp(current->dirname, buff) && current != NULL)
		current = current->sibling;


	if (Push(current, stack) != 0)
		printf("An error occured!\n");

	return current;
}

int Push(Position current, StackPosition stack)
{
	StackPosition NewNode = NULL;

	NewNode = (StackPosition)malloc(sizeof(Stack));
	if (NULL == NewNode)
		printf("An error occured!\n");

	NewNode->next = NULL;
	NewNode->Dir = NULL;


	NewNode->Dir = current;
	NewNode->next = stack->next;
	stack->next = NewNode;

	return 0;
}

int SubdirectoryPrint(Position last)
{
	Position current = NULL;

	current = last->child;

	printf("\nDirectory of %s\n\n", last->dirname);

	while (current != NULL)
	{
		printf("<Dir>\t%s\n", current->dirname);
		current = current->sibling;
	}

	return 0;
}

Position AddDirectory(Position last, char* dirname)
{
	Position newKnot = NULL;
	Position previous = NULL;

	newKnot = (Position)malloc(sizeof(Dir));
	if (NULL == newKnot)
		printf("An error occured!\n");

	newKnot->dirname = (char*)malloc(30 * sizeof(char));
	if (NULL == newKnot->dirname)
		printf("An error occured!\n");

	strcpy(newKnot->dirname, dirname);
	newKnot->child = NULL;
	newKnot->sibling = NULL;

	if (NULL == last->child)
	{
		newKnot->child = last->child;
		last->child = newKnot;

		return last;
	}

	previous = last->child;

	while (previous->sibling != NULL && (strcmp(previous->sibling->dirname, newKnot->dirname) < 0))
		previous = previous->sibling;

	if (previous != NULL && (strcmp(previous->dirname, newKnot->dirname) < 0))
	{
		newKnot->sibling = previous->sibling;
		previous->sibling = newKnot;

		return last;
	}
	else
	{
		newKnot->sibling = last->child;
		last->child = newKnot;

		return last;
	}
}

int MenuChoice(char* choice)
{
	if (!strcmp(choice, "md"))
		return 1;
	else if (!strcmp(choice, "cd.."))
		return 2;
	else if (!strcmp(choice, "cd"))
		return 3;
	else if (!strcmp(choice, "Dir"))
		return 4;
	else if (!strcmp(choice, "exit"));
	return 5;
}
