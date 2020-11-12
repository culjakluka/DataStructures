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
void createList(Position head, Position what);
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

	readFile("poly1.txt", &head1);
	printList(head1.next);

	readFile("poly2.txt", &head2);
	printList(head2.next);

	addPolynomials(head1.next, head2.next, &r);
	printList(r.next);

	return 0;
}
Position createNode(int coef, int expo) {
	Position el = NULL;
	el = (Position)malloc(sizeof(Poly));
	if (NULL == el) {
		return NULL;
	}
	el->coef = coef;
	el->expo = expo;
	el->next = NULL;
	return el;
}
void createList(Position head, Position what) {
	if (NULL == head->next) {
		what->next = NULL;
		head->next = what;
		return;
	}
	head = head->next;
	for (head; head != NULL; head = head->next) {
		if (what->expo > head->expo) {
			what->next = head->next;
			head->next = what;
		}
	}
}
void addNode(Position head, Position what) {
	Position p = head;
	if (what->coef == 0)
		return;

	p = p->next;
	if (NULL == p) {
		what->next = NULL;
		head->next = what;
	}
	else 
		for (p; p != NULL; p = p->next) {
		/*if (p->expo == what->expo) {
			p->coef += what->coef;
			return;
		}*/
			 if ((what->expo > p->expo)) {
				what->next = NULL;
				p->next = what;
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
	if (NULL == what) {
		while (!(NULL == p->next))
			p = p->next;
		return p;
	}
	while (!(p->next->expo == what->expo)) {
		p = p->next;
	}
	return p;
}
void addPolynomials(Position p, Position q, Position r) {
	Position el = NULL;
	while (NULL != p && NULL != q) {
		if (p->expo < q->expo) {
			el = createNode(p->coef, p->expo);
			addNode(r, el);
			p = p->next;
		}
		else if (p->expo > q->expo) {
			el = createNode(q->coef, q->expo);
			addNode(r, q);
			q = q->next;
		}
		else if (p->expo == q->expo) {
			if (p->coef + q->coef != 0) {
				el = createNode(p->coef + q->coef, p->expo);
				addNode(r, el);
			}
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
		createList(pos, createNode(coef, expo));
	}
	fclose(fp);
}
//sscanf(b, " %d %d %n, &coef, &expo, &n) while strlen(b)>0
