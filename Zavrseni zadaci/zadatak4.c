#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME (256)

struct poly;
typedef struct poly Poly;
typedef struct poly* Position;

struct poly {
	int coef;
	int expo;
	Position next;
};
Position createNode(int coef, int expo);
Position addPolynomials(Position p, Position q);
void addNode(Position head, Position what);
void readFile(char* fileName, Position pos);
int main() {
	Poly head1, head2;
	head1.next = NULL;
	head2.next = NULL;
	readFile("poly1.txt", &head1);
	readFile("poly2.txt", &head2);
	Position r = addPolynomials(&head1, &head2);
	return 0;
}
Position createNode(int coef, int expo) {
	Position el = NULL;
	el = (Position)malloc(sizeof(Poly));
	el->coef = coef;
	el->expo = expo;
	return el;
}
void addNode(Position head, Position what) {
	Position p = head;
	if (what->expo == 0)
		return;
	else if (what->expo < p->expo)
		p = p->next;
	else if (what->expo == p->expo) {
		p->coef += what->coef;
		return;
	}else {
		what->next = p->next;
		p->next = what;
	}
}
Position addPolynomials(Position p, Position q) {
	Position r = NULL;
	while (NULL != p && NULL != q) {
		if (p->expo < q->expo) {
			addNode(r, p);
			p = p->next;
		}
		else if (p->expo > q->expo) {
			addNode(r, q);
			q = q->next;
		}
		else if (p->expo == q->expo) {
			addNode(r, p);
			addNode(r, q);
			p = p->next;
			q = q->next;
		}
	}
	return r;
}
void readFile(char* fileName, Position pos) {
	int coef = 0;
	int expo = 0;
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	while (!feof(fp)) {
		fscanf(fp, " %d %d", &coef, &expo);
		addNode(pos, createNode(coef, expo));
	}
}
//sscanf() while strlen(b)>0
