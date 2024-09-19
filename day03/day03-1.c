#include <stdio.h>

// 소수 판별 함수
int is_prime(int num) {
    if (num <= 1) {
        return 0; // 1 이하의 숫자는 소수가 아님
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; // 나누어떨어지는 경우 소수가 아님
        }
    }

    return 1; // 소수일 경우
}


int main() {
    int number;

    // 사용자 입력 받기
    printf("소수인지 확인할 수를 입력하세요: ");
    scanf_s("%d", &number);

    // 소수 판별 및 결과 출력
    if (is_prime(number)) {
        printf("해당 수는 소수입니다.\n");
    }
    else {
        printf("해당 수는 소수가 아닙니다.\n");
    }

    return 0;
}
