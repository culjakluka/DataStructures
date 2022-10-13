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
Position createSortedList(Position el, Position pos);
void insertAfter(Position where, Position what);
void insertStart(Position head, Position what);
void insertEnd(Position head, Position what);
void insertBefore(Position head, Position what, char* lastName);
void printList(Position from);
Position findElement(Position head, char* lastName);
Position findLastElement(Position head);
Position findPreviousElement(Position pos, char* lastName);
Position findSmaller(Position pos, Position what);
void deleteElement(Position pos, char* lastName);
void listToFile(Position head);
Position fileToList(Position head, char* fileName);

int main(void) {
	Node head;
	Node* el, * el2;
	head.next = NULL;
	char lastName[MAX_NAME];

	for (int i = 0; i < 2; i++) {
		el = createPerson(&head);
		createSortedList(el, &head);
	}
	printList(head.next);
	listToFile(&head);

	printf("\r\nInsert the last name that you want to find: ");
	scanf(" %s", lastName);
	el2 = findElement(&head, lastName);
	printf("\r\n%s %s %d je trazeni student.", el2->firstName, el2->lastName, el2->birthYear);

	printf("\r\nInsert the last name that you want to delete: ");
	scanf(" %s", lastName);
	deleteElement(&head, lastName);
	printList(head.next);

	puts("\r\nPlease insert a person to add to the list(after an element).");
	el = createPerson(&head);
	printf("\r\nPlease insert after which person to insert %s %s (surname)\n", el->firstName, el->lastName);
	scanf(" %s", &lastName);
	insertAfter(findElement(&head, lastName), el);
	printList(head.next);

	puts("\r\nPlease insert a person to add to the list(before an element).");
	el = createPerson(&head);
	printf("\r\nPlease insert before which person to insert %s %s (last name)\n", el->firstName, el->lastName);
	scanf(" %s", &lastName);
	insertBefore(&head, el, lastName);
	printList(head.next);

	return EXIT_SUCCESS;
}

Position createPerson(Position pos) {
	char firstName[MAX_NAME] = { 0 };
	char lastName[MAX_NAME] = { 0 };
	int birthYear = 0;
	Node* el = NULL;

	printf("\r\nPlease insert person\r\n");
	printf("First name:\t");
	scanf(" %s", firstName);
	printf("Last name:\t");
	scanf(" %s", lastName);
	printf("Birthyear:\t");
	scanf(" %d", &birthYear);
	el = createStudent(firstName, lastName, birthYear);

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
Position createSortedList(Position el, Position head) {
	Position pos = head;
	if (NULL == el) {
		puts("Element sent points to NULL!");
		return NULL;
	}
	if (NULL == pos->next) {
		insertAfter(pos, el);
		return NULL;
	}
	pos = pos->next;
	for (pos; pos != NULL; pos = pos->next) {
		if (NULL == pos->next) {
			if (strcmp(pos->lastName, el->lastName) > 0) {
				insertAfter(findPreviousElement(head, pos->lastName), el);
				return NULL;
			}
			insertAfter(pos, el);
			return NULL;
		}
		if (strcmp(pos->lastName, el->lastName) == 0) {
			insertAfter(pos, el);
			return NULL;
		}
		if (strcmp(pos->lastName, el->lastName) < 0 && strcmp(el->lastName, pos->next->lastName) < 0) {
			insertAfter(pos, el);
			return NULL;
		}
	}
	return NULL;
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
void insertBefore(Position head, Position what, char* lastName) {
	insertAfter(findPreviousElement(head, lastName), what);
}

void printList(Position pos) {
	if (NULL == pos) {
		puts("Empty list!");
		return;
	}
	puts("\r\nList: ");
	for (pos; pos != NULL; pos = pos->next)
		printf("\r\n%s %s %d", pos->firstName, pos->lastName, pos->birthYear);
}

Position findElement(Position head, char* lastName) {
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
Position findPreviousElement(Position pos, char* lastName) {
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
void deleteElement(Position pos, char* lastName) {
	Position el = findPreviousElement(pos, lastName);
	if (NULL != el) {
		printf("\r\nSuccesful deletion of element");
		pos = el->next;
		el->next = pos->next;
		free(pos);
	}
}

void listToFile(Position head) {
	FILE* fp = NULL;
	fp = fopen("students.txt", "w");
	if (NULL == fp) {
		puts("\r\nFile opening failed!");
		return;
	}
	head = head->next;
	for (head; head != NULL; head = head->next) {
		fprintf(fp, " %s %s %d\n", head->firstName, head->lastName, head->birthYear);
	}
}

Position fileToList(Position head, char* fileName) {
	char firstName[MAX_NAME] = { 0 };
	char lastName[MAX_NAME] = { 0 };
	int yearOfBirth = 0;
	Position el = NULL;
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (NULL == fp) {
		puts("\r\nFile opening failed!");
		return NULL;
	}
	while (!feof(fp)) {
		fscanf(fp, " %s %s %d", firstName, lastName, &yearOfBirth);
		el = createStudent(firstName, lastName, yearOfBirth);
		createSortedList(head, el);
	}
	return head;
}