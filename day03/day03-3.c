#include <stdio.h>
#include <math.h>

// M_PI가 선언되지 않은 경우 직접 정의
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    // 절대값 함수 abs() 사용
    printf("%d\n", abs(-4)); // -4의 절대값 출력

    // sin 함수는 라디안 값을 입력으로 받음, 30도를 라디안으로 변환하여 sin 계산
    printf("%lf\n", sin(30 * (M_PI / 180))); // 30도의 sin 값 출력

    // cos 함수 사용 (소문자로 작성)
    printf("%lf\n", cos(30 * (M_PI / 180))); // 30도의 cos 값 출력

    // sqrt 함수로 제곱근 계산
    printf("%lf\n", sqrt(2.5)); // 2.5의 제곱근 출력

    // pow 함수로 거듭제곱 계산
    printf("%lf\n", pow(1.5, 4.0)); // 1.5의 4승 값 출력

    return 0;
}
