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
void AddToList(Position, Position);
Position Previous(Position, Position);
void CreateHashTable(Position, char*);
char* ReadFromFile(char*);
Position FromTextToPerson(char*, int*);

int main() {
	Position hashTable = NULL;
	hashTable = (Position)malloc(11 * sizeof(List));

	srand((unsigned)time(NULL));
	
	for (int i = 0; i != 11; i++) {
		strcpy(hashTable[i].name, "");
		strcpy(hashTable[i].surname, "");
		hashTable[i].next = NULL;
	}

	CreateHashTable(hashTable, "names.txt");

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

Position CreateNode(char* name, char* surname) {
	Position el = NULL;
	el = (Position)malloc(sizeof(List));
	if (NULL == el) {
		puts("Allocating error!");
		return NULL;
	}

	strcpy(el->name, name);
	strcpy(el->surname, surname);
	el->id = RandomNumber();
	return el;
}

int RandomNumber() {
	return rand() % ((RAND_MAX - RAND_MIN) + 1) + RAND_MIN;
}

char* Input(char* message) {
	char* userInput = NULL;
	userInput = (char*)malloc(NAME_SIZE*sizeof(char));
	printf("\r\n%s", message);
	scanf("%s", userInput);
	return userInput;
}

void CreateSortedList(Position what, Position where) {
	Position head = where;
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
			AddToList(what, Previous(head, where));
			return;
		}
		else if (strcmp(where->surname, what->surname) == 0) {
			while (strcmp(where->surname, what->surname) == 0) {
				if (strcmp(where->name, what->name) > 0) {
					AddToList(what, Previous(head, where));
					return;
				}
				else if (strcmp(where->name, what->name) < 0 && strcmp(where->next->name, what->name) > 0) {
					AddToList(what, where);
					return;
				}
				else if (strcmp(where->name, what->name) < 0 && where->next == NULL) {
					AddToList(what, where);
					return;
				}
				where = where->next;
			}
		}
		else if (strcmp(where->surname, what->surname) < 0 && strcmp(where->next->surname, what->surname) > 0) {
			AddToList(what, where);
			return;
		}
		else if (strcmp(where->surname, what->surname) < 0 && where->next == NULL) {
			AddToList(what, where);
			return;
		}
	}
}

void AddToList(Position what, Position where) {
	what->next = where->next;
	where->next = what;
}

Position Previous(Position head, Position what) {
	if (NULL == head) {
		puts("List sent is NULL!");
		return NULL;
	}
	while (head->next != what) {
		head = head->next;
	}
	return head;
}

void CreateHashTable(Position hashTable, char* filename) {
	Position person = NULL;
	int buffCount = 0;
	int index = 0;
	int counter = 0;
	char* buff = NULL;
	buff = ReadFromFile(filename);
	buffCount = (unsigned)strlen(buff);

	while (counter != buffCount) {
		person = FromTextToPerson(buff, &counter);
		index = CalculateHashIndex(person->surname);
		CreateSortedList(person, hashTable + index);
	}
}

char* ReadFromFile(char* filename) {
	char* buff = NULL;
	char* temp = NULL;
	FILE* fp = NULL;
	
	temp = (char*)malloc(5000 * sizeof(char));
	fp = fopen(filename, "r");
	if (NULL == fp) {
		puts("Cant open file!");
		return NULL;
	}
	
	while (fgets(temp, 100, fp)) {
		strcat(buff, temp); //TUSIBURAZ
	}
	return buff;
}

Position FromTextToPerson(char* buff, int* counter) {
	char* name = NULL;
	char* surname = NULL;
	int buffCounter = 0;
	int n = 0;
	Position person = NULL;
	buffCounter = (unsigned)strlen(buff);

	if (buffCounter != *counter) {
		sscanf(buff, "%s%n", name, &n);
		buff += n;
		counter += n;
		sscanf(buff, "%s%n", surname, &n);
		buff += n;
		counter += n;
	}
	person = CreateNode(name,surname);
	return person;
}
