#include <stdio.h>
#include <stdlib.h>

typedef struct Student student;

struct Student {
	char ime[50];
	char prezime[50];
	unsigned int bodovi;
};
int countStudents(char* fileName, int* n);
int readFromFile(char* filename, int n);
int main() {
	student* st;
	int numStud = 0;

	if (!countStudents("studenti.txt", &numStud)) {
		printf("\ncountStudents error");
		return -1;
	}
	st = (student*)malloc(numStud * sizeof(student));

	return 0;
}

int countStudents(char* fileName, int* n) {
	FILE* fp;
	char c;
	
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		perror(fp);
		return 0;
	}
	for (c = getc(fp); c == EOF; c = getc(fp))
		if (c == '\n') (*n)++;

	fclose(fp);
	return 1;
}