#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct stack;
typedef struct stack Stack;
typedef struct stack* Position;

struct stack {
	int x;
	Position next;
};

void AddToList(Position, Position);
void Push(Position, int);
int Pop(Position);
char* ReadFromFile(char* fileName);
float CalculatePostfix(char*, Position);

int main() {
	Stack head;
	head.next = NULL;
	head.x = 0;

	return 0;
}

void AddToList(Position what, Position where) {
	what->next = where->next;
	where->next = what;
}
void Push(Position pos, int x) {
	Position el = NULL;
	el = (Position)malloc(sizeof(Stack));
	if (NULL == el) {
		puts("\r\nAllocating error");
		return;
	}
	el->x = x;
	AddToList(el, pos);
	printf("\r\nAdded %d to list.");
}

int Pop(Position pos) {
	if (NULL == pos->next) {
		puts("\r\nList is empty!");
		return 0;
	}
	Position nextEl = pos->next;
	printf("\r\nPopped %d.", nextEl->x);
	pos->next = pos->next->next;
	return nextEl->x;
}

char* ReadFromFile(char* fileName) {
	char text[1000];
	int i = 0;
	FILE* fp = NULL;
	fp = fopen(fileName, 'r');
	if(NULL==fp){
		puts("\r\nFile load failure!");
		return NULL;
	}
	while (feof(fp))
		fgets(text, 1000, fp);
	return text;
}
float CalculatePostfix(char* text, Position head) {
	int x = 0;
	int n = 0;
	int num = 0;
	char* buff = NULL;
	char c;
	buff = (char*)malloc(1000 * sizeof(char));
	buff = text;
	int n = 0;
	if (sscanf(buff, "%d %n",&x, &n) != EOF){
		Push(head, x);
		buff += n;
	}
	else {
		sscanf(" %c",&c);
		switch (c)
		{
		case '+':
			while (Pop(head) != 0) {
				num += Pop(head);
			}
		default:
			break;
		}
	}
}

