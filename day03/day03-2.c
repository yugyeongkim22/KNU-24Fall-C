#include <stdio.h>


int fact(int num);

int main()
{
	int num;
	scanf_s("%d", &num);

	int result = fact(num);
	printf("result=%d\n", result);
	return 0;
}int fact(int num)
{
	int res;
	if (num == 0 || num == 1) {
		res = 1;
		return res;
	}

	res = num * fact(num - 1);
	return res;
}