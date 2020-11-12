#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct poly;
typedef struct poly Poly;
typedef struct poly* Position;

struct poly {
	int coef;
	int expo;
	Position next;
};

Position createNode(int coef, int expo);
void addPolynomials(Position p, Position q, Position r);
void addNode(Position head, Position what);
void printList(Position head);
void deleteNode(Position head, Position what);
Position findPrevious(Position head, Position what);
void readFile(char* fileName, Position pos);
int main() {
	Poly head1, head2, r;
	head1.next = NULL;
	head1.coef = 0;
	head1.expo = 0;
	head2.next = NULL;
	head2.coef = 0;
	head2.expo = 0;
	r.next = NULL;
	readFile("poly1.txt", head1.next);
	printList(head1.next);
	readFile("poly2.txt", head2.next);
	printList(head2.next);
	addPolynomials(head1.next, head2.next, &r);
	printList(r.next);
	return 0;
}
Position createNode(int coef, int expo) {
	Position el = NULL;
	el = (Position)malloc(sizeof(Poly));
	el->coef = coef;
	el->expo = expo;
	el->next = NULL;
	return el;
}
void addNode(Position head, Position what) {
	Position p = head;
	if (what->coef == 0)
		return;
	//here

	while (NULL != p) {
		if (what->expo < p->expo)
			p = p->next;
		else if (what->expo == p->expo) {
			p->coef += what->coef;
			if (0 == p->coef)
				deleteNode(head, p);
			return;
		}
		else {
			what->next = p->next;
			p->next = what;
			return;
		}
	}
}
void deleteNode(Position head, Position what) {
	Position p = findPrevious(head, what);
	//dovrsi
	if (NULL != p) {
		puts("Deleted successfully");
		p->next = what->next;				// provjerit jos 
		free(what);
	}
}
Position findPrevious(Position head, Position what) {
	Position p = head;
	while (!(p->next->expo == what->expo)) {
		p = p->next;
	}
	return p;
}
void addPolynomials(Position p, Position q, Position r) {
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
}
void printList(Position head) {
	Position p = head;
	while (NULL != p) {
		printf("\r\n%d*x^%d", p->coef, p->expo);
		p = p->next;
	}
	printf("\n");
}
void readFile(char* fileName, Position pos) {
	int coef = 0;
	int expo = 0;
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (NULL == fp) {
		printf("\r\nCouldn't open file");
		return;
	}
	while (!feof(fp)) {
		fscanf(fp, " %d %d", &coef, &expo);
		addNode(pos, createNode(coef, expo));
	}
	fclose(fp);
}
//sscanf(b, " %d %d %n, &coef, &expo, &n) while strlen(b)>0
