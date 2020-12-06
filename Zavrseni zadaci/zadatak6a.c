#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RAND_MAX 100
#define RAND_MIN 10
 
struct stack;
typedef struct stack Stack;
typedef struct stack* Position;

struct stack {
	int x;
	Position next;
};

int RandomInt();
void Push(Position);
void Pop(Position);
void PrintList(Position);

int main() {
	Stack head;
	head.next = NULL;
	head.x = 0;

	srand(time(NULL));
	Push(&head);
	Push(&head);
	Push(&head);
	Push(&head);

	PrintList(head.next);

	Pop(&head);
	Pop(&head);
	Pop(&head);
	Pop(&head);
	Pop(&head);

	return 0;
}

int RandomInt() {
	return (rand() % (RAND_MAX - RAND_MIN + 1)) + RAND_MIN;
}
void Push(Position pos) {
	Position el = NULL;
	el = (Position)malloc(sizeof(Stack));
	if (NULL == pos) {
		puts("\r\nAllocating error");
		return;
	}
	el->x = RandomInt();

	el->next = pos->next;
	pos->next = el;
	printf("\r\nAdded %d to start of list.", el->x);
}
void Pop(Position pos) {
	if (NULL == pos->next) {
		printf("\r\nNema elemenata u listi");
		return;
	}
	Position nextEl = pos->next;
	printf("\r\nLast in first out: %d", pos->next->x);
	pos->next = pos->next->next;
	free(nextEl);
}
void PrintList(Position pos) {
	for (pos; pos != NULL; pos = pos->next) {
		printf("\n\r%d", pos->x);
	}
}
