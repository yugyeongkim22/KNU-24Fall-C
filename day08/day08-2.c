#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define SIZE 10

void fillRandom(int array[SIZE][SIZE]);
void printArray(int array[SIZE][SIZE]);
void movePointer(void* array);

int main() {
    int array[SIZE][SIZE];

    //시작점을 시간으로 설정함>> 난수 달라지게 하려고
    srand((unsigned int)time(NULL));

    fillRandom(array); // 배열 랜덤 초기화
    printArray(array); // 배열 출력
    movePointer(array); // 포인터를 이용한 이동

    return 0;
}

// 배열을 1~20 사이의 랜덤 값으로 초기화
void fillRandom(int array[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            array[i][j] = rand() % 20 + 1; // 1~20 범위의 난수
        }
    }
}

//배열을 출력하는 함수
void printArray(int array[SIZE][SIZE]) {
    printf("배열 출력:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%2d ", array[i][j]);
        }
        printf("\n");
    }
}

// 포인터 이용해 배열을 이동하는 함수
void movePointer(void* array) {
    int(*arr)[SIZE] = (int(*)[SIZE])array; // 배열을 2차원 배열 포인터로 캐스팅
    int x = 0, y = 0; // 시작 위치
    int value;

    while (1) {
        value = arr[x][y];
        printf("현재 위치: (%d, %d), 배열의 값: %d\n", x, y, value);

        // 이동할 새 위치를 계산
        int newX = x;
        int newY = y + value; // 현재 위치의 값만큼 오른쪽으로 이동

        // 배열의 경계를 벗어나는지 체크
        if (newY >= SIZE) {
            newX = x + (newY / SIZE); // 행을 증가
            newY = newY % SIZE; // 열을 조정
        }

        // 경계를 넘어서면 종료
        if (newX >= SIZE || newY >= SIZE) {
            printf("더 이상 이동할 수 없습니다.\n");
            printf("종료 위치: (%d, %d), 배열의 값: %d\n", x, y, value);
            break;
        }

        // 위치를 업데이트
        x = newX;
        y = newY;
    }
}
