#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;  // ������������ ���
    double lol, root1, root2; //lol= �Ǻ���

   
    printf("a, b, c�� �Է��ϼ��� (ax^2 + bx + c = 0)\n");
    scanf_s("%lf %lf %lf", &a, &b, &c);

   
    lol = b * b - 4 * a * c;

    
    if (lol > 0) {
        // ���� �ٸ� �� �Ǳ�
        root1 = (-b + sqrt(lol)) / (2 * a);
        root2 = (-b - sqrt(lol)) / (2 * a);
        printf("���� �ٸ� �� �Ǳ�: %.2lf, %.2lf\n", root1, root2);
    }
    else if (lol == 0) {
        // �߱�
        root1 = -b / (2 * a);
        printf("�߱�: %.2lf\n", root1);
    }
    else {
        // ���
        printf("���, ���� ������� ����\n");
    }

    return 0;
}
