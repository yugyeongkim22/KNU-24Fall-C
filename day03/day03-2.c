#include <stdio.h>


int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;  
    }
    else {
        return n * factorial(n - 1); 
    }
}


int main() {
    int number;

   
    printf("계산할 팩토리얼 값 입력: ");
    scanf_s("%d", &number);

  
    printf("%d! = %d\n", number, factorial(number));

    return 0;
}
