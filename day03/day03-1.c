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

   
    printf("�Ҽ����� Ȯ���� ���� �Է��ϼ���: ");
    scanf_s("%d", &number);

   
    if (is_prime(number)) {
        printf("�ش� ���� �Ҽ��Դϴ�.\n");
    }
    else {
        printf("�ش� ���� �Ҽ��� �ƴմϴ�.\n");
    }

    return 0;
}
