#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define NAME_SIZE (128)
#define RAND_MAX (2000)
#define RAND_MIN (1)

struct list;
typedef struct list List;
typedef struct list* Position;
struct list {
	char name[NAME_SIZE];
	char surname[NAME_SIZE];
	int id;
	Position next;
};

int CalculateHashIndex(char*);
Position CreateNode();
int RandomNumber();
char* Input(char*);
void CreateSortedList(Position, Position);
Position Previous(Position);

int main() {
	Position hashTable = NULL;
	hashTable = (Position)malloc(11 * sizeof(List));

	srand((unsigned)time(NULL));
	
	for (int i = 0; i != 11; i++) {
		strcpy(hashTable[i].name, "");
		strcpy(hashTable[i].surname, "");
		hashTable[i].next = NULL;
	}

	return 0;
}

int CalculateHashIndex(char* surname) {
	int letterSum = 0;
	int n;
	char c;

	for (int i = 0; i != 5; i++) {
		if (sscanf(surname, "%c%n", &c, &n)) {
			letterSum += (int)c;
			surname += n;
		}
	}
	return letterSum % 11;
}

Position CreateNode() {
	Position el = NULL;
	el = (Position)malloc(sizeof(List));
	if (NULL == el) {
		puts("Allocating error!");
		return NULL;
	}

	strcpy(el->name, Input("\r\nUnesite ime osobe:\t"));
	strcpy(el->surname, Input("\r\nUnesite prezime osobe:\t"));
	el->id = RandomNumber();
	return el;
}

int RandomNumber() {
	return rand() % ((RAND_MAX - RAND_MIN) + 1) + RAND_MIN;
}

char* Input(char* message) {
	char* userInput = NULL;
	userInput = (char*)malloc(NAME_SIZE*sizeof(char));
	printf("%s", message);
	scanf("%s", userInput);
	return userInput;
}

void CreateSortedList(Position what, Position where) {
	Position p = where;
	if (NULL == what) {
		puts("Element empty!");
		return;
	}
	if (NULL == where) {
		AddToList(what, where);
		return;
	}
	while (where->next != NULL) {
		where = where->next;
		if (strcmp(where->surname, what->surname) > 0) {
			AddToList(what, Previous(p, where));
			return;
		} 
		//TUSIBURAZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ
	}
}

void AddToList(Position what, Position where) {
	what->next = where->next;
	where->next = what;
}

Position Previous(Position head, Position what) {
	while (head->next != what) {
		head = head->next;
	}
	return head;
}
