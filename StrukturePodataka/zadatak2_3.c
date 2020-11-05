#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME (256)

struct _node;
typedef struct _node Node;
typedef struct _node* Position;

struct _node {
	char firstName[MAX_NAME];
	char lastName[MAX_NAME];
	int birthYear;
	Position next;
};

Position createPerson(Position pos);
Position createStudent(char* firstName, char* lastName, int birthYear);
void insertAfter(Position where, Position what);
void insertStart(Position head, Position what);
void insertEnd(Position head, Position what);
void insertBefore(Position head, Position what);
void printList(Position from);
Position findElement(Position head);
Position findLastElement(Position head);
Position findPreviousElement(Position pos);
Position findSmaller(Position pos, Position what);
void deleteElement(Position pos);

int main(void) {
	Node head;
	Node* el, * el2;
	head.next = NULL;
	char lastName[MAX_NAME];

	for (int i = 0; i < 3; i++) {
		el = createPerson(&head);
	}

	el2 = findElement(&head);
	printf("\r\n%s je trazeno prezime", el2->lastName);

	deleteElement(&head);

	el = createPerson(&head);
	printf("Please insert after which person to insert %s %s (surname)\n", el->firstName, el->lastName);
	scanf(" %s", &lastName);
	insertAfter(findElement(&head), el);

	el = createPerson(&head);
	printf("Please insert before which person to insert %s %s (last name)\n", el->firstName, el->lastName);
	scanf(" %s", &lastName);
	insertAfter(findPreviousElement(&head), el);

	return EXIT_SUCCESS;
}

Position createPerson(Position pos) {
	char firstName[MAX_NAME] = { 0 };
	char lastName[MAX_NAME] = { 0 };
	int birthYear = 0;
	Node* el = NULL;

	printf("Please insert person\r\n");
	printf("First name:\t");
	scanf(" %s", firstName);
	printf("Last name:\t");
	scanf(" %s", lastName);
	printf("Birthyear:\t");
	scanf(" %d", &birthYear);
	el = createStudent(firstName, lastName, birthYear);
	insertAfter(findSmaller(pos, el), el);
	printList(pos);

	return el;
}
Position createStudent(char* firstName, char* lastName, int birthYear) {
	Position el = NULL;
	el = (Position)malloc(sizeof(Node));
	if (NULL == el) { // Da se teze falije
		printf("Memory allocation failed!\r\n");
		return NULL;
	}
	strcpy(el->firstName, firstName);
	strcpy(el->lastName, lastName);
	el->birthYear = birthYear;
	el->next = NULL;
	return el;
}

void insertAfter(Position where, Position what) {
	what->next = where->next;
	where->next = what;
}

void insertStart(Position head, Position what) {
	insertAfter(head, what);
}
void insertEnd(Position head, Position what) {
	insertAfter(findLastElement(head), what);
}
void insertBefore(Position head, Position what) {
	insertAfter(findPreviousElement(head), what);
}

void printList(Position head) {
	Position p = head->next;
	for (p = head->next; p != NULL; p = p->next)
		printf("%s %s %d\r\n", p->firstName, p->lastName, p->birthYear);
}

Position findElement(Position head) {
	char* lastName = NULL;
	printf("Insert the last name that you want to find: ");
	scanf(" %s", lastName);

	for (Position p = head->next; p != NULL; p = p->next)
		if (!strcmp(lastName, p->lastName))
			return p;

	return NULL;
}
Position findLastElement(Position pos) {
	while (NULL != pos->next) {
		pos = pos->next;
	}
	return pos;
}
Position findPreviousElement(Position pos) {
	char* lastName = NULL;
	printf("Insert the last name that you want to find: ");
	scanf(" %s", lastName);

	while (pos->next != NULL && strcmp(pos->next->lastName, lastName)) {
		pos = pos->next;
	}
	if (NULL == pos) {
		printf("\r\nFinding error");
		return NULL;
	}
	return pos;
}
Position findSmaller(Position pos, Position what) {
	if (NULL == pos->next)
		return pos;
	if (strcmp(pos->next->lastName, what->lastName) < 0)
		return pos;
	pos = pos->next;
	while(strcmp(pos->lastName, what->lastName) >= 0) {
		pos = pos->next;
	}
	return pos;
}
void deleteElement(Position pos) {
	Position el = findPreviousElement(pos);
	if (NULL != el) {
		printf("\r\nSuccesful deletion of element");
		pos = el->next;
		el->next = pos->next;
		free(pos);
	}
}