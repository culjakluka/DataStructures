#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct tree Tree;
typedef struct tree* Position;
struct tree {
	int x;
	Position left;
	Position right;
};

Position NewElement(int);
Position AddToSortedList(int, Position);
void PrintList(Position);
Position EmptyTree(Position);
Position findElement(int, Position);
Position findGreatestFromLeft(Position, Position);
Position findSmallestFromRight(Position, Position);
Position deleteElement(Position, Position);

int main() {
	Position root = NULL;
	int choice = 0;
	int temp = 0;
	Position elementFound = NULL;
	while (choice != 5)
	{
		printf("\r\n\t\tMENU:");
		printf("\r\n\t1 - Dodavanje novog elementa u stablo");
		printf("\r\n\t2 - Ispis liste");
		printf("\r\n\t3 - Brisanje elementa");
		printf("\r\n\t4 - Pronalazak elementa");
		printf("\r\n\t5 - Izlaz iz aplikacije");
		printf("\r\n\tUnesite broj ispred akcije:\t");
		if (scanf(" %d", &choice)) {
			switch (choice)
			{
			case 1:
				printf("\r\n\tUnesite vrijednost elementa:\t");
				if (scanf("%d", &temp)) {
					root = AddToSortedList(temp, root);
				}
				break;
			case 2:
				PrintList(root);
				break;
			case 3:
				if (NULL == root) {
					puts("\tList is empty!");
					break;
				}
				printf("\r\n\tUnesite element koji zelite izbrisati:\t");
				if (scanf("%d", &temp)) {
					if (elementFound = findElement(temp, root)) {
						root = deleteElement(elementFound, root);
					}
				}
				break;
			case 4:
				if (NULL == root) {
					puts("\tList is empty!");
					break;
				}
				printf("\r\n\tUnesite element koji zelite pronaci:\t");
				if (scanf("%d", &temp)) {
					elementFound = findElement(temp, root);
				}
				if (NULL != elementFound) {
					printf("\r\n\tElement found -> ((%d)) at adress (%d)", elementFound->x, elementFound);
				}
				break;
			case 5:
				break;
			default:
				printf("\r\n\tUnesite jedan od ponudenih brojeva!");
				choice = 0;
				break;
			}
		}
	}

	return 0;
}

Position NewElement(int x) {
	Position el = NULL;
	el = (Position)malloc(sizeof(Tree));
	if (NULL == el) {
		puts("Allocating error!");
		return NULL;
	}
	el->x = x;
	el->left = NULL;
	el->right = NULL;

	return el;
}

Position AddToSortedList(int x, Position s) {
	if (NULL == s) {
		s = NewElement(x);
		return s;
	}
	if (x < s->x) {
		s->left = AddToSortedList(x, s->left);
		return s;
	}
	if (x > s->x) {
		s->right = AddToSortedList(x, s->right);
		return s;
	}
	return s;
}

void PrintList(Position root) {
	if (NULL == root) {
		return;
	}
	if (NULL == root->left && NULL == root->right) {
		printf("\t(%d)", root->x);
		return;
	}
	
	PrintList(root->left);
	
	printf("\t(%d)", root->x);
	
	PrintList(root->right);
	

	return;
}

Position EmptyTree(Position s) {
	if (NULL != s) {
		EmptyTree(s->left);
		EmptyTree(s->right);
		free(s);
	}
	return NULL;
}

Position findElement(int x, Position pos) {
	if (NULL == pos) {
		puts("\tEmpty list!!!");
		return NULL;
	}
	else if (x < pos->x) {
		return 	findElement(x, pos->left);

	}
	else if (x > pos->x) {
		return findElement(x, pos->right);
	}
	return pos;
}

Position findGreatestFromLeft(Position el, Position list) {
	if (NULL == list) {
		puts("\tList empty!!!");
		return NULL;
	}
	if (NULL == list->left) {
		puts("\tLeft subtree empty!!!");
		return NULL;
	}
	list = list->left;
	while (NULL != list->right) {
		list = list->right;
	}
	return list;
}

Position findSmallestFromRight(Position el, Position list) {
	while (list->left != NULL) {
		list = list->left;
	}
	return list;
}

Position deleteElement(Position el, Position list) { //debuuuuuuuuuuuuuuuuuuuuuuuuuuuuug
	Position temp = NULL;
	if (NULL == list) {
		puts("\tEmpty tree!!!");
		return NULL;
	}
	if (el->x < list->x) {
		list->left = deleteElement(el, list->left);
	}
	if (el->x > list->x) {
		list->right = deleteElement(el, list->right);
	}
	else {
		if (NULL != list->left && NULL != list->right) {
			temp = findSmallestFromRight(el, list->right);
			list->x = temp->x;
			list->right = deleteElement(list, list->right);
		}
		if (NULL == list->left || NULL == list->right) {
			temp = list;
			if (NULL == list->left) {
				list = list->right;
			}
			else if(NULL==list->left){
				list = list->left;
			}
			free(temp);
		}
	}
	return list;
}
