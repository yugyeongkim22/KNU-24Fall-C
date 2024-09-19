#include <stdio.h>

// �Ҽ� �Ǻ� �Լ�
int is_prime(int num) {
    if (num <= 1) {
        return 0; // 1 ������ ���ڴ� �Ҽ��� �ƴ�
    }

    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return 0; // ����������� ��� �Ҽ��� �ƴ�
        }
    }

    return 1; // �Ҽ��� ���
}


int main() {
    int number;

    // ����� �Է� �ޱ�
    printf("�Ҽ����� Ȯ���� ���� �Է��ϼ���: ");
    scanf_s("%d", &number);

    // �Ҽ� �Ǻ� �� ��� ���
    if (is_prime(number)) {
        printf("�ش� ���� �Ҽ��Դϴ�.\n");
    }
    else {
        printf("�ش� ���� �Ҽ��� �ƴմϴ�.\n");
    }

    return 0;
}
