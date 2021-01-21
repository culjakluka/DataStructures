#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DATA_SIZE (11)
#define FILE_NAME_SIZE (256)

struct _node;
typedef struct _node Node;
typedef struct _node* NodePosition;

struct list;
typedef struct list List;
typedef struct list* ListPosition;

struct _node {
	char data[DATA_SIZE];
	NodePosition left;
	NodePosition right;
};
struct list {
	NodePosition data;
	ListPosition next;
};

NodePosition readPostfixFromFile(char* filename);
NodePosition createNode(char*);
ListPosition createListNode(NodePosition);
int push(ListPosition, NodePosition data);
NodePosition pop(ListPosition head);
int isNumber(char* str);
int pushBack(ListPosition head, NodePosition data);
int toInfixList(ListPosition head, NodePosition current);
void infixListToFile(ListPosition head, char* filename);

int main() {
	NodePosition root = NULL;
	List infixResult;
	ListPosition p = NULL;
	char filename[FILE_NAME_SIZE] = { 0 };

	infixResult.next = NULL;
	
	printf("Please insert postfix filename(for reading):\t\r\n");
	scanf(" %s", filename);

	root = readPostfixFromFile(filename);

	if (NULL == root) {
		return EXIT_FAILURE;
	}

	toInfixList(&infixResult, root);

	for (p = infixResult.next; p != NULL; p=p->next) {
		printf("%s ", p->data->data);
	}

	printf("Please insert postfix filename(for writing):\t\r\n");
	scanf(" %s", filename);

	infixListToFile(&infixResult, filename);

	return EXIT_SUCCESS;
}
	
NodePosition readPostfixFromFile(char *filename) {
	FILE* fp = NULL;
	NodePosition result = NULL;
	char readString[DATA_SIZE] = { 0 };
	List head;

	head.next = NULL;
	fp = fopen(filename, "r");

	if (NULL == fp) {
		puts("File doesn't exist or.....\n\r");
		return NULL;
	}
	
	while (!feof(fp)) {
		NodePosition node = NULL;
		fscanf(fp, " %s", readString);
		node = createNode(readString);

		if(NULL == node){
			fclose(fp);
			return NULL;
		}

		if (isNumber(node->data)) {
			push(&head, node);
		}
		else {
			node->right = pop(&head);

			if (NULL == node->right) {
					puts("Postfix isn't formatted correctly!\n\r");
					return NULL;
				}

			node->left = pop(&head);

			if (NULL == node->left) {
				puts("Postfix isn't formatted correctly!\n\r");
				return NULL;
			}
		
			push(&head, node);
		}
	}

	result = pop(&head);

	if (NULL == result) {
		puts("Postfix not right!");
		return NULL;
	}
	
	if (pop(&head) != NULL) {
		puts("Postfix not right!");
		return NULL;
	}

	return result;
}

NodePosition createNode(char* data) {
	NodePosition p = NULL;

	p = (NodePosition)malloc(sizeof(Node));
	if (NULL == p) {
		puts("Memory allocation failed!");
		return NULL;
	}
	strcpy(p->data, data);
	p->left = NULL;
	p->right = NULL;

	return p;
}

ListPosition createListNode(NodePosition data) {
	ListPosition node = NULL;
	node = (ListPosition)malloc(sizeof(List));
	if (NULL == node) {
		puts("Memory allocation failed!");
		return NULL;
	}

	node->data = data;
	node->next = NULL;
	return node;
}

int push(ListPosition head, NodePosition data) {
	ListPosition node = NULL;
	node = createListNode(data);
	if (NULL == node) {
		return -1;
	}

	node->next = head->next;
	head->next = node;
	return 0;
}

NodePosition pop(ListPosition head) {
	ListPosition first = head->next;
	NodePosition result = NULL;
	if (first == NULL) {
		return NULL;
	}

	head->next = first->next;
	result = first->data;
	free(first);

	return result;
}

int isNumber(char* str) {
	int number = 0;

	if (sscanf(str, " %d", &number)==1) {
		return 1;
	}
	else {
		return 0;
	}
}

int pushBack(ListPosition head, NodePosition data) {
	ListPosition p = head;

	while (p->next != NULL) {
		p = p->next;
	}
	
	return push(head, data);
}

int toInfixList(ListPosition head, NodePosition current) {
	if (NULL == current) return -1;

	toInfixList(head, current->left);
	pushBack(head, current);
	toInfixList(head, current->right);

	return 0;
}

void infixListToFile(ListPosition head, char* filename) {
	FILE* fp = NULL;
	ListPosition p = NULL;
	fp = fopen(filename, "w");
	if (NULL == fp) {
		puts("File open error!");
		return;
	}

	for (p=head->next; p != NULL; p = p->next) {
		fprintf(fp, " %s", p->data->data);
	}

	fclose(fp);

	return;
}
