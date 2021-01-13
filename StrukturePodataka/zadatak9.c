#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct tree;
typedef struct tree Tree;
typedef struct tree* Position;
struct tree{
	Position left;
	Position right;
	int x;
};

int main() {
	Tree root;
	root.left = NULL;
	root.right = NULL;

	return EXIT_SUCCESS;
}
