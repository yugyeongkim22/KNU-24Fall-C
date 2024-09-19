#include <stdio.h>

int isPrimeNumber(int num)
{
	for (int i = 2; i < num; i++) {
		if (num % i == 0) {
			return 0;
		}
	}
	return 1;
}

int main()
{
	int num;
	scanf_s("%d", &num);
	int res = isPrimeNumber(num);

	printf("%d\n", res);

}