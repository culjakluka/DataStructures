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
Position CreateNode(char*, char*);
int RandomNumber();
char* Input(char*);
void CreateSortedList(Position, Position);
void AddToList(Position, Position);
Position Previous(Position, Position);
void CreateHashTable(Position, char*);
char* ReadFromFile(char*);
Position FromTextToPerson(char*, int*, int*);
void PrintList(Position, int);
void PrintId(Position);
void PrintIdPersonFromList(Position, int, char*, char*);

int main() {
	Position hashTable = NULL;
	int choice = 0;
	hashTable = (Position)malloc(11 * sizeof(List));
	if (NULL == hashTable) {
		puts("hashTable allocation failed!");
		return EXIT_FAILURE;
	}
	srand((unsigned)time(NULL));
	
	for (int i = 0; i != 11; i++) {
		strcpy(hashTable[i].name, "");
		strcpy(hashTable[i].surname, "");
		hashTable[i].id = i;
		hashTable[i].next = NULL;
	}

	CreateHashTable(hashTable, "names.txt");
	for (int i = 0; i < 11; i++) {
		PrintList(&hashTable[i], i);
	}

	do{ 
		printf("\n\r\tIzaberite broj ispred akcije koju zelite izvrsiti: \r\n1 - ispis maticnog broja osobe\r\n0 - izlaz iz aplikacije\r\n\t");
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			PrintId(hashTable);
			break;
		default:
			break;
		}
	} while (choice != 0);

	return EXIT_SUCCESS;
}

int CalculateHashIndex(char* surname) {
	int letterSum = 0;
	int n = 0;
	char c;

	for (int i = 0; i < 5; i++) {
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
	el->next = NULL;
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
	if (NULL == where->next) {
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
				else if (strcmp(where->name, what->name) < 0 && where->next == NULL) {
					AddToList(what, where);
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
	int buffLength = 0;
	int index = 0;
	int counter = 0;
	char* buff = NULL;
	char* temp;

	if (temp = ReadFromFile(filename)) {
		buffLength = (unsigned)strlen(temp);
		buff = (char*)malloc(buffLength * sizeof(char));
		if (NULL == buff) {
			puts("buff allocation failed!");
			return;
		}
		strcpy(buff, temp);
	}
	if (NULL == buff) {
		puts("buff allocation failed!");
		return;
	}

	while (counter != buffLength) {
		person = FromTextToPerson(buff + counter, &counter, &buffLength);
		index = CalculateHashIndex(person->surname);
		CreateSortedList(person, hashTable + index);
	}
}

char* ReadFromFile(char* filename) {
	char* buff = NULL;
	char* temp = NULL;
	FILE* fp = NULL;

	buff = (char*)malloc(5000 * sizeof(char));
	if (NULL == buff) {
		puts("buff allocation failed!");
		return NULL;
	}
	temp = (char*)malloc(1000 * sizeof(char));
	if (NULL == temp) {
		puts("temp allocation failed!");
		return NULL;
	}
	fp = fopen(filename, "r");
	if (NULL == fp) {
		puts("Cant open file!");
		return NULL;
	}
	if (fgets(temp, 100, fp)) {
		strcpy(buff, temp);
	}
	while (fgets(temp, 100, fp)) {
		strcat(buff, temp);
	}
	return buff;
}

Position FromTextToPerson(char* buff, int* counter, int* buffCounter) {
	char* name = NULL;
	char* surname = NULL;
	int n = 0;
	Position person = NULL;

	name = (char*)malloc(100 * sizeof(char));
	surname = (char*)malloc(100 * sizeof(char));

	if (*buffCounter != *counter) {
		sscanf(buff, "%s%n", name, &n);
		buff += n;
		*counter += n;
		sscanf(buff, "%s%n", surname, &n);
		buff += n;
		*counter += n;
		person = CreateNode(name,surname);
		return person;
	}
	return NULL;
}

void PrintList(Position pos, int index) {
	printf("\r\n\tIndex - %d", index);
	while (pos->next != NULL) {
		pos = pos->next;
		printf("\r\n\t%s %s", pos->name, pos->surname);
	}
}

void PrintId(Position hashTable) {
	int index;
	char* surname = NULL;
	char* name = NULL;
	name = Input("\n\rUnesite ime osobe za koju zelite znati maticni broj: ");
	surname = Input("\n\rUnesite prezime osobe za koju zelite znati maticni broj: ");
	index = CalculateHashIndex(surname);
	PrintIdPersonFromList(hashTable + index, index, name, surname);
}

void PrintIdPersonFromList(Position pos, int index, char* name, char* surname) {
	printf("\n\rIndex: %d", index);
	while ((strcmp(pos->surname, surname) != 0) && (strcmp(pos->name, name) !=0)) {
		pos = pos->next;
	}
	printf("\n\r%s %s (maticni broj) - %d", pos->name, pos->surname, pos->id);
}
