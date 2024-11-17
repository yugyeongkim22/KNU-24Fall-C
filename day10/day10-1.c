#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX (50)

struct NODE
{
	int data;
	struct NODE* link;
};

struct NODE* head;

struct NODE* create_node(int data)
{
	struct NODE* new_node = (struct NODE*)malloc(sizeof(struct NODE));
	new_node->data = data;
	new_node->link = NULL;

	return new_node;
}

struct NODE* last_node()
{
	struct NODE* cur = head;
	while (cur->link != NULL) {
		cur = cur->link;
	}
	return cur;
}

void insert_node_last(struct NODE* new_node)
{
	struct NODE* last = last_node();
	last->link = new_node;
}

void print_nodes()
{
	struct NODE* cur = head->link;
	printf("------------------\n");
	while (cur != NULL) {
		printf("%d\n", cur->data);
		cur = cur->link;
	}
	printf("------------------\n");
}

struct NODE* find_node(int value)
{
	struct NODE* cur = head->link;
	while (cur != NULL) {
		if (cur->data == value) return cur;

		cur = cur->link;
	}
	return NULL;
}

int delete_node(int value)
{
	struct NODE* prev = head;
	struct NODE* cur = head->link;
	while (cur != NULL) {
		if (cur->data == value) {
			prev->link = cur->link;
			free(cur);
			return 1;
		}
		prev = cur;
		cur = cur->link;
	}
	return 0;
}

int main()
{
	head = (struct NODE*)malloc(sizeof(struct NODE));
	head->link = NULL;

	int inst;
	int iteration = 1;

	char name[NAME_MAX];
	int score;

	while (1) {
		printf("1.학생 성적 입력\n");
		printf("2. 학생 삭제\n");
		printf("3. 프로그램 종료\n");
		printf("명령 입력: ");
		scanf_s("%d", &inst);

		switch (inst)
		{
		case 1:
			printf("학생 이름: ");
			scanf_s("%s", name, NAME_MAX);
			printf("점수: ");
			scanf_s("%d", &score);
			//create new node
			insert_node_last(create_node(score));
			break;
		case 2:
			printf("삭제할 학생의 점수: ");
			scanf_s("%d", &score);
			delete_node(score);
			break;
		case 3:
		default:
			iteration = 0;
			break;
		}

		print_nodes();
	}

	return 0;
}