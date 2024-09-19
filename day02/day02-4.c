#include <stdio.h>

int main() {
    int i, j, n;
    //i는 현재 층수,n은 총 층수

    printf("피라미드의 층수를 입력하세요:");
    scanf_s("%d", &n);

    for (i = 1; i <= n; i++) {
        //공백 생성
        for (j = 1; j <= n - i; j++) {
            printf(" ");
        }

        //별 생성
        for (j = 1; j <= (2 * i - 1); j++) {
            printf("*");
        }

        printf("\n");

    }

    return 0;


}
