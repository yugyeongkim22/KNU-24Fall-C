#include <stdio.h>

int main() {

	int operation;
	printf("연산타입:");
	scanf_s("%d", &operation);

	double num1, num2;

	printf("숫자 1를 입력하세요:");
	scanf_s("%lf", &num1);

	printf("숫자 2를 입력하세요:");
	scanf_s("%lf", &num2);

	double result;
	if (operation == 1) {
		result = num1 + num2;

	}
	else if (operation == 2) {
		result = num1 - num2;
	}
	else if (operation == 3) {
		result = num1 * num2;
	}
	else if (operation == 4) {
		result = num1 /num2;
	}
	else {
		printf("잘못입력했습니다.\n");
	}
	printf("result=%lf\n",result);
	return 0;
}