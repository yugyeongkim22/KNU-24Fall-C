#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10

void fillRandom(int array[SIZE][SIZE]);
void printArray(int array[SIZE][SIZE]);
void movePointer(void* array);

int main() {
    int array[SIZE][SIZE];

    //�������� �ð����� ������>> ���� �޶����� �Ϸ���
    srand((unsigned int)time(NULL));

    fillRandom(array); // �迭 ���� �ʱ�ȭ
    printArray(array); // �迭 ���
    movePointer(array); // �����͸� �̿��� �̵�

    return 0;
}

// �迭�� 1~20 ������ ���� ������ �ʱ�ȭ
void fillRandom(int array[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            array[i][j] = rand() % 20 + 1; // 1~20 ������ ����
        }
    }
}

//�迭�� ����ϴ� �Լ�
void printArray(int array[SIZE][SIZE]) {
    printf("�迭 ���:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }
}

// ������ �̿��� �迭�� �̵��ϴ� �Լ�
void movePointer(void* array) {
    int(*arr)[SIZE] = (int(*)[SIZE])array; // �迭�� 2���� �迭 �����ͷ� ĳ����
    int x = 0, y = 0; // ���� ��ġ
    int value;

    while (1) {
        value = arr[x][y];
        printf("���� ��ġ: (%d, %d), �迭�� ��: %d\n", x, y, value);

        // �̵��� �� ��ġ�� ���
        int newX = x;
        int newY = y + value; // ���� ��ġ�� ����ŭ ���������� �̵�

        // �迭�� ��踦 ������� üũ
        if (newY >= SIZE) {
            newX = x + (newY / SIZE); // ���� ����
            newY = newY % SIZE; // ���� ����
        }

        // ��踦 �Ѿ�� ����
        if (newX >= SIZE || newY >= SIZE) {
            printf("�� �̻� �̵��� �� �����ϴ�.\n");
            printf("���� ��ġ: (%d, %d), �迭�� ��: %d\n", x, y, value);
            break;
        }

        // ��ġ�� ������Ʈ
        x = newX;
        y = newY;
    }
}
