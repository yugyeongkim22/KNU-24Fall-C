#include <stdio.h>
#include <math.h>

// 함수 f(x)
double f(double x) {
    return -log10(1 / x) + sin(x);
}

// 구분적분법 함수
double integration_by_rectangles(double start, double end, int num_intervals) {
    double dx = (end - start) / num_intervals;
    double result = 0.0;

    for (int i = 0; i < num_intervals; i++) {
        double x = start + i * dx;
        result += f(x) * dx;
    }

    return result;
}

int main() {
    double start, end;
    int max_intervals_exp;

   
    printf("적분할 시작 값을 입력하세요: ");
    scanf_s("%lf", &start);
    printf("적분할 끝 값을 입력하세요: ");
    scanf_s("%lf", &end);
    printf("시행할 최대 구간을 입력하세요(2^n): ");
    scanf_s("%d", &max_intervals_exp);

    // 결과 
    int intervals = 1;
    for (int i = 0; i <= max_intervals_exp; i++) {
        double result = integration_by_rectangles(start, end, intervals);
        printf("구간 %10d 적분 결과: %.6lf\n", intervals, result);
        intervals *= 2; 
    }

    return 0;
}
