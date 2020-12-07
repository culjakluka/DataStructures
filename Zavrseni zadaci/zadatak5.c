#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define RAND_MAX 10

struct list;
typedef struct list List;
typedef struct list* Position;

struct list {
	int x;
	Position next;
};
void PrintList(Position);
int RandomInt();
void SortedAddToList(Position, int);
void AddToList(Position, Position);
void CreateUnion(Position, Position, Position);
void CreateIntersection(Position, Position, Position);


int main() {
	List L1, L2, unionList, intersectionList;
	L1.next = NULL;
	L2.next = NULL;
	unionList.next = NULL;
	intersectionList.next = NULL;
	L1.x = 0;
	L2.x = 0;
	unionList.x = 0;
	intersectionList.x = 0;

	srand((unsigned)time(NULL));

	for (int i = 0; i < 5; i++) {
		SortedAddToList(&L1, RandomInt());
		SortedAddToList(&L2, RandomInt());
	}
	CreateUnion(&unionList, &L1, &L2);
	if (NULL == unionList.next) {
		puts("Union list is empty!");
		return 0;
	}

	CreateIntersection(&intersectionList, &L1, &L2);
	if (NULL == intersectionList.next) {
		puts("Intersection list is empty!");
		return 0;
	}
	
	PrintList(L1.next);
	PrintList(L2.next);
	PrintList(unionList.next);
	PrintList(intersectionList.next);

	return 0;
}

void PrintList(Position pos) {
	if (NULL == pos) {
		puts("List is empty.");
		return;
	}
	puts("");
	for (pos; pos != NULL; pos = pos->next) {
		printf("\t%d", pos->x);
	}
}

int RandomInt() {
	return (rand() % (RAND_MAX + 1));
}

void SortedAddToList(Position pos, int val) {
	Position el = NULL;
	el = (Position)malloc(sizeof(List));
	el->x = val;
	printf("\r\n\tInt being added to list: %d", el->x);
	if (NULL == el) {
		puts("Error allocating memory!");
		return;
	}
	if (NULL == pos){
		puts("Error, head of list sent to function is NULL.");
	}
	for (pos; pos != NULL; pos = pos->next){
		if (NULL == pos->next) {
			AddToList(el, pos);
			return;
		}
		if (pos->x == el->x) {
			AddToList(el, pos);
			return;
		}
		if ((pos->x < el->x) && (el->x < pos->next->x)) {
			AddToList(el, pos);
			return;
		}
	}
}

void AddToList(Position what, Position where) {
	what->next = where->next;
	where->next = what;
}

void CreateUnion(Position newList, Position list1, Position list2) {
	for (Position pos = list1->next; pos != NULL; pos = pos->next) {
		SortedAddToList(newList, pos->x);
	}
	for (Position pos = list2->next; pos != NULL; pos = pos->next) {
		SortedAddToList(newList, pos->x);
	}
}
void CreateIntersection(Position newList, Position list1, Position list2) {
	for (Position i = list1->next; i != NULL; i = i->next) {
		for (Position j = list2->next; j != NULL; j = j->next) {
			if (i->x == j->x){
				SortedAddToList(newList, i->x);
				break;
			}
		}
	}
}
