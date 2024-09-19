#include <stdio.h>


int is_prime(int num) {
    if (num <= 1) {
        return 0; 
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; 
        }
    }

    return 1; 
}


int main() {
    int number;

   
    printf("소수인지 확인할 수를 입력하세요: ");
    scanf_s("%d", &number);

   
    if (is_prime(number)) {
        printf("해당 수는 소수입니다.\n");
    }
    else {
        printf("해당 수는 소수가 아닙니다.\n");
    }

    return 0;
}
