#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;  // 이차방정식의 계수
    double lol, root1, root2; //lol= 판별식

   
    printf("a, b, c를 입력하세요 (ax^2 + bx + c = 0)\n");
    scanf_s("%lf %lf %lf", &a, &b, &c);

   
    lol = b * b - 4 * a * c;

    
    if (lol > 0) {
        // 서로 다른 두 실근
        root1 = (-b + sqrt(lol)) / (2 * a);
        root2 = (-b - sqrt(lol)) / (2 * a);
        printf("서로 다른 두 실근: %.2lf, %.2lf\n", root1, root2);
    }
    else if (lol == 0) {
        // 중근
        root1 = -b / (2 * a);
        printf("중근: %.2lf\n", root1);
    }
    else {
        // 허근
        printf("허근, 값을 출력하지 않음\n");
    }

    return 0;
}
