#include<stdio.h>

void swap(int* pnum1, int* pnum2)
{
	int temp = *pnum1;
	*pnum1 = *pnum2;
	*pnum2 = temp;
}

int main()
{
	int num1 = 30;
	int num2 = 40;

	printf("num1=%d , num2=%d\n", num1, num2);
	swap(&num1, &num2);
	printf("num1=%d , num2=%d\n", num1, num2);
	
	return 0; 

}