#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIR_NAME_LENGTH 1024
#define err puts("ERROR")

struct _dir;
struct stack;
typedef struct _dir Dir;
typedef struct _dir* Position;
typedef struct stack Stack;
typedef struct stack* Pos;

struct _dir {
	char Name[DIR_NAME_LENGTH];
	Position next;
	Position child;
};
struct stack {
	Position prev;
	Pos next;
};

void MakeDirectory(Position);
Position CreateNewDirectory();
void CreateSortedList(Position, Position);

int main() {
	Dir head;
	strcpy(head.Name, "C:");
	head.next = NULL;
	head.child = NULL;
	int action = 0;
	Position current = &head;

	while (action!=5)
	{
		switch (action)
		{
		case 1:
			MakeDirectory(current);
		default:
			break;
		}
	}

	return 0;
}

void MakeDirectory(Position p){
	Position newDir = CreateNewDirectory();
	if (NULL == p->child) {
		p->child = newDir;
		newDir->next = NULL;
	}
	CreateSortedList(newDir, p->child);
}
Position CreateNewDirectory() {
	Position dir = NULL;
	char* name = "";
	dir = (Position)malloc(sizeof(Dir));
	if (NULL == dir) {
		err;
		return NULL;
	}
	puts("Unesite ime novog direktorija: ");
	while ("" == name) {
		scanf(" %s", name);
	}
	strcpy(dir->Name, name);
	dir->child = NULL;
	return dir;
}
void CreateSortedList(Position newDir, Position p) {
	if (NULL == p->child->next) {
		if(strcmp(p->child->Name, newDir->Name)){
			
		}
	}
}
