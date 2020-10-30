#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Student student;

struct Student {
	char name[50];
	char surname[50];
	int points;
};

int countStudents(char*, int*);
int allocateStudents(student**, int);
int readFromFile(char*, student*, int);
int findMax(student*, int*, int);
int outputStudents(student*, int, int);

int main() {
	student *st = NULL;
	int numStud = 0;
	int maxPoints;

	if (!countStudents("studenti.txt", &numStud)) {
		printf("\ncountStudents error");
		return -1;
	}

	st = (student*)malloc(numStud * sizeof(student));
	if (!st) {
		printf("malloc error\r\n");
		return -1;
	}
	/*if (!allocateMemory(&st, numStud)) {
		printf("\nallocateMemory error");
		return -1;
	}*/

	if (!readFromFile("studenti.txt", st, numStud)) {
		printf("\nreadFromFile error");
		return -1;
	}

	if (!findMax(st, &maxPoints, numStud)) {
		printf("\nfindMax error");
		return -1;
	}

	if (!outputStudents(st, numStud, maxPoints)) {
		printf("\noutputStudent error");
		return -1;
	}
	
	free(st);
	return 0;
}

int countStudents(char* fileName,int *n) {
	FILE* fp = NULL;
	char c;
	
	if (!(fp = fopen(fileName, "r"))) {
		perror("The following error has occured");
		return 0;
	}
	c = getc(fp);
	if(c=='\n') return 1;
	(*n)++;
	while (c != EOF) { 
		if (c == '\n') (*n)++;
		c = getc(fp);
	}
	fclose(fp);
	return 1;
}

int allocateStudents(student** st, int numStud) { //This function sucks
	*st = (student*)malloc(numStud * sizeof(student*)); 
	if (st == NULL) return 0;
	return 1;
}

int readFromFile(char* fileName, student* stArr, int n) {
	FILE* fp = NULL;

	if (!(fp = fopen(fileName, "r"))) {
		perror("The following error has occured");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		if (!fscanf(fp, "%s %s %d", stArr[i].name, stArr[i].surname, &stArr[i].points)) {
			printf("\nfscanf error");
			return 0;
		}
	}
	fclose(fp);
	return 1;
}

int findMax(student* stArr, int* max, int n) {
	int i, tempMax;
	tempMax = stArr[0].points;

	for (i = 1; i < n; i++) {
		if (stArr[i].points > tempMax) 
			tempMax = stArr[i].points;
	}

	*max = tempMax;
	return 1;
}

int outputStudents(student* stArr, int n, int maxPoints) {
	int i;

	for (i = 0; i < n; i++) {
		printf("\n %s %s %d %f", stArr[i].name, stArr[i].surname, stArr[i].points, ((float)stArr[i].points/maxPoints)*100);
	}
	return 1;
}