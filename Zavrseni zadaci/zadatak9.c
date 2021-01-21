#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

struct element;
typedef struct element* Position;
typedef struct element Element;
typedef struct element
{
	int x;
	Position left;
	Position right;
};

Position addNewElement(Position, int);
Position NewNode(int);
int Print(Position);
Position Find(int, Position);
Position Delete(int, Position);
Position FindMax(Position);

int main(void)
{
	Position tree = NULL;
	Position keyElement = NULL;
	int choice = 0;
	int temp = 0;

	while (choice != 5)
	{
		printf("\nMENU\n1 - Unosenje novog elementa\n2 - Print elemenata\n3 - Delete\n4 - Find element\n5 - Gasi\n");
		printf("Unesite radnju koju zelite obaviti : ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Unesite vrijednost novog elemnta : ");
			scanf("%d", &temp);

			tree = addNewElement(tree, temp);
			break;
		case 2:
			if (Print(tree) != 0)
				printf("Greska!!!\n");
			break;
		case 3:
			printf("Unesite element koji zelite izbrisati : ");
			scanf("%d", &temp);
			tree = Delete(temp, tree);
			break;
		case 4:
			printf("Unesite element koji zelite pronaci : ");
			scanf("%d", &temp);
			keyElement = Find(temp, tree);

			if (keyElement != NULL)
				printf("element %d je na adresi %x !!!\n", temp, (unsigned int)keyElement);
			else
				printf("Trazeni elemnt ne postoji!!!\n");
			break;
		case 5:
			break;
		default:
			printf("Niste unjeli ni jednu od ponudenih opcija, pokusajte ponovo!\n");
		}
	}

	return 0;
}

Position FindMax(Position knotForDeletion)
{
	if (NULL != knotForDeletion)
	{
		if (NULL != knotForDeletion->right)
		{
			knotForDeletion = knotForDeletion->right;
			FindMax(knotForDeletion);
		}
	}

	return knotForDeletion;
}

Position Delete(int el, Position tree)
{
	Position temp = NULL;

	if (NULL == tree)
		return NULL;

	if (el < tree->x)
	{
		tree->left = Delete(el, tree->left);
		return tree;
	}
	if (el > tree->x)
	{
		tree->right = Delete(el, tree->right);
		return tree;
	}
	if (NULL == tree)
	{
		printf("Tree missing!\n");
		return tree;
	}

	//provjera broja djece
	if ((NULL != tree->left) && (NULL != tree->right))
	{
		temp = FindMax(tree->left);
		tree->x = temp->x;

		tree->left = Delete(tree->x, tree->left);

		return tree;
	}

	temp = tree;

	if (NULL == tree->left)
		tree = tree->right;
	else
		tree = tree->left;

	free(temp);


	return tree;
}

Position Find(int el, Position tree)
{
	if (NULL == tree)
		return NULL;

	if (tree->x > el)
		return Find(el, tree->left);

	if (tree->x < el)
		return Find(el, tree->right);

	return tree;
}

int Print(Position tree)
{
	if (NULL != tree)
	{
		Print(tree->left);

		printf("(%d)", tree->x);

		Print(tree->right);
	}
	return 0;
}

Position NewNode(int el)
{
	Position Temp = NULL;

	Temp = (Position)malloc(sizeof(Element));
	if (NULL == Temp)
		printf("Error!\n");

	Temp->left = NULL;
	Temp->right = NULL;
	Temp->x = el;

	return Temp;
}

Position addNewElement(Position S, int el)
{
	if (NULL == S)
	{
		S = NewNode(el);

		return S;
	}

	if (el < S->x)
	{
		S->left = addNewElement(S->left, el);
		return S;
	}

	if (el > S->x)
	{
		S->right = addNewElement(S->right, el);
		return S;
	}

	return S;
}
