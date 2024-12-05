#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_TOPPING 10000

//topping_len은 배열 topping의 길이.
int solution(int topping[], size_t topping_len) {
	int left_tops[MAX_TOPPING + 1] = { 0, };//철수가 먹는 토핑
	int right_tops[MAX_TOPPING + 1] = { 0, }; //동생이 먹는 토핑
	int num_left = 0;
	int num_right = 0;
	int num_fairs = 0;

	for (int i = 0; i < topping_len; i++) { // 동생이 모두 먹을 때
		int top = topping[i];
		if (right_tops[top] == 0) num_right++; //동생이 먹는 토핑 가지 수 업
		right_tops[top]++;
	}
	for (int i = 0; i < topping_len; i++) { // 철수가 왼쪽부터 하나씩 토핑을 가져감.
		int top = topping[i];
		right_tops[top]--;
		if (right_tops[top] == 0) num_right--; //동생이 먹는 토핑 가지 수 다운

		if (left_tops[top] == 0) num_left++; //철수가 먹는 토핑 가지 수 증가
		left_tops[top]++;

		if (num_left == num_right) num_fairs++;//공평한 나누기 가지 수 증가
	}

	return num_fairs;
}