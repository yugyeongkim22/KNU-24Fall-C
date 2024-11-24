#include <stdio.h>
#include <math.h>

// �Լ� f(x)
double f(double x) {
    return -log10(1 / x) + sin(x);
}

// �������й� �Լ�
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

   
    printf("������ ���� ���� �Է��ϼ���: ");
    scanf_s("%lf", &start);
    printf("������ �� ���� �Է��ϼ���: ");
    scanf_s("%lf", &end);
    printf("������ �ִ� ������ �Է��ϼ���(2^n): ");
    scanf_s("%d", &max_intervals_exp);

    // ��� 
    int intervals = 1;
    for (int i = 0; i <= max_intervals_exp; i++) {
        double result = integration_by_rectangles(start, end, intervals);
        printf("���� %10d ���� ���: %.6lf\n", intervals, result);
        intervals *= 2; 
    }

    return 0;
}
