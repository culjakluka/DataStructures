#define _CRT_SECURE_NO_WARNINGS	
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RAND_MAX 100
#define RAND_MIN 10

struct queue;
typedef struct queue Queue;
typedef struct queue* Position;

struct queue {
	int x;
	Position next;
};

int RandomInt();
void Push(Position);
void Pop(Position);
void PrintList(Position);

int main() {
	Queue head;
	head.next = NULL;
	head.x = 0;

	srand((unsigned)time(NULL));

	Push(&head);
	Push(&head);
	Push(&head);

	PrintList(head.next);

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
	el = (Position)malloc(sizeof(Queue));
	if (NULL == el){
		puts("\r\nAllocating error!");
		return;
	}
	while (pos->next != NULL) {
		pos = pos->next;
	}
	el->next = pos->next;
	pos->next = el;
	el->x = RandomInt();
	printf("\r\nAdded %d to list.", el->x);
}

void Pop(Position pos) {
	if (NULL == pos->next) {
		puts("\r\nEmpty list!");
		return;
	}
	Position nextEl = pos->next;
	pos->next = pos->next->next;
	printf("\r\nPopped %d", nextEl->x);
	free(nextEl);
}

void PrintList(Position pos) {
	if (NULL == pos) {
		puts("Printing error!");
		return;
	}
	for (pos; pos != NULL; pos=pos->next) {
		printf("\r\n%d", pos->x);
	}
}
