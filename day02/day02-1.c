#include <stdio.h>

int main() {

	int operation;
	printf("����Ÿ��:");
	scanf_s("%d", &operation);

	double num1, num2;

	printf("���� 1�� �Է��ϼ���:");
	scanf_s("%lf", &num1);

	printf("���� 2�� �Է��ϼ���:");
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
		printf("�߸��Է��߽��ϴ�.\n");
	}
	printf("result=%lf\n",result);
	return 0;
}