#include <stdio.h>
#include <math.h>

// M_PI�� ������� ���� ��� ���� ����
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
    // ���밪 �Լ� abs() ���
    printf("%d\n", abs(-4)); // -4�� ���밪 ���

    // sin �Լ��� ���� ���� �Է����� ����, 30���� �������� ��ȯ�Ͽ� sin ���
    printf("%lf\n", sin(30 * (M_PI / 180))); // 30���� sin �� ���

    // cos �Լ� ��� (�ҹ��ڷ� �ۼ�)
    printf("%lf\n", cos(30 * (M_PI / 180))); // 30���� cos �� ���

    // sqrt �Լ��� ������ ���
    printf("%lf\n", sqrt(2.5)); // 2.5�� ������ ���

    // pow �Լ��� �ŵ����� ���
    printf("%lf\n", pow(1.5, 4.0)); // 1.5�� 4�� �� ���

    return 0;
}
