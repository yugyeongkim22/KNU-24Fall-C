#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_TOPPING 10000

//topping_len�� �迭 topping�� ����.
int solution(int topping[], size_t topping_len) {
	int left_tops[MAX_TOPPING + 1] = { 0, };//ö���� �Դ� ����
	int right_tops[MAX_TOPPING + 1] = { 0, }; //������ �Դ� ����
	int num_left = 0;
	int num_right = 0;
	int num_fairs = 0;

	for (int i = 0; i < topping_len; i++) { // ������ ��� ���� ��
		int top = topping[i];
		if (right_tops[top] == 0) num_right++; //������ �Դ� ���� ���� �� ��
		right_tops[top]++;
	}
	for (int i = 0; i < topping_len; i++) { // ö���� ���ʺ��� �ϳ��� ������ ������.
		int top = topping[i];
		right_tops[top]--;
		if (right_tops[top] == 0) num_right--; //������ �Դ� ���� ���� �� �ٿ�

		if (left_tops[top] == 0) num_left++; //ö���� �Դ� ���� ���� �� ����
		left_tops[top]++;

		if (num_left == num_right) num_fairs++;//������ ������ ���� �� ����
	}

	return num_fairs;
}