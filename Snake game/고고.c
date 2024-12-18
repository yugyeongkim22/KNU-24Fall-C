

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define HEIGHT 20  // 게임판 세로 크기
#define WIDTH 60   // 게임판 가로 크기
#define BEST_SCORE_FILE "best_score.txt" // 최고점 파일 이름

int gameover, score, bestScore, upCount, downCount, leftCount, rightCount;
int x, y, fruitx, fruity, flag;
int tailX[100], tailY[100];
int tailLength = 0;
int snakeColor = 7; // 기본 색상 (흰색)
char* fruitShape; // 현재 열매 모양 (문자열로 변경)
int isDoubleScoreFruit = 0; // 더블 스코어 열매 여부
char* fruitShapes[] = { "#", "@", "+", "$", "\\" }; // 일반 열매 모양 배열
char* doubleFruitShapes[] = { "$$", "\\\\" }; // 더블 스코어 열매 모양 배열
int fruitColor; // 현재 열매 색상

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void gotoxy(int x, int y) {
    COORD pos = { y, x };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setConsoleColor(int color) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, color);
}

void loadBestScore() {
    FILE* file;
    if (fopen_s(&file, BEST_SCORE_FILE, "r") == 0) {
        if (fscanf_s(file, "%d", &bestScore) != 1) {
            bestScore = 0;
        }
        fclose(file);
    }
    else {
        bestScore = 0;
    }
}

void saveBestScore() {
    FILE* file;
    if (fopen_s(&file, BEST_SCORE_FILE, "w") == 0) {
        fprintf(file, "%d", bestScore);
        fclose(file);
    }
}

void setup() {
    gameover = 0;
    score = 0; // 점수를 초기화하지만 bestScore는 건드리지 않음
    upCount = downCount = leftCount = rightCount = 0;

    x = HEIGHT / 4;
    y = WIDTH / 4;
    tailLength = 2;

    tailX[0] = x;
    tailY[0] = y - 1;
    tailX[1] = x;
    tailY[1] = y - 2;

    fruitx = rand() % (HEIGHT - 2) + 1;
    fruity = rand() % (WIDTH - 3) + 1;

    // 열매 속성 초기화
    if (rand() % 100 < 60) {
        isDoubleScoreFruit = 1;
        fruitShape = doubleFruitShapes[rand() % 2];
    }
    else {
        isDoubleScoreFruit = 0;
        fruitShape = fruitShapes[rand() % (sizeof(fruitShapes) / sizeof(fruitShapes[0]))];
    }

    do {
        fruitColor = rand() % 16; // 열매 색상 설정
    } while (fruitColor == 0 || fruitColor == 7);

    do {
        snakeColor = rand() % 16; // 뱀 색상 설정
    } while (snakeColor == 0 || snakeColor == 7 || snakeColor == fruitColor);

    flag = 3; // 기본 방향: 오른쪽
}

void draw() {
    gotoxy(0, 0);

    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 1) {
                printf("ㅣ");
            }
            else if (i == x && j == y) {
                setConsoleColor(snakeColor);
                printf("0");
                setConsoleColor(7); // 기본 색상 복원
            }
            else if (i == fruitx && j == fruity) {
                setConsoleColor(fruitColor);
                printf("%s", fruitShape);
                if (isDoubleScoreFruit) j++; // 두 글자 출력 후 칸 건너뛰기
                setConsoleColor(7);
            }
            else {
                int isTail = 0;
                for (int k = 0; k < tailLength; k++) {
                    if (tailX[k] == i && tailY[k] == j) {
                        setConsoleColor(snakeColor);
                        printf("o");
                        setConsoleColor(7);
                        isTail = 1;
                        break;
                    }
                }
                if (!isTail) printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("\n");

    printf("aa's Score: %d  Best: %d\n", score, bestScore);
    printf("Up: %d / Down: %d / Left: %d / Right: %d\n", upCount, downCount, leftCount, rightCount);
    printf("R: Restart / X: Quit.\n");
}
void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (flag) {
    case 1: y--; break;
    case 2: x++; break;
    case 3: y++; break;
    case 4: x--; break;
    }

    if (x < 0 || x >= HEIGHT || y < 1 || y >= WIDTH - 1) {
        gameover = 1;
    }

    if ((x == fruitx && y == fruity) ||
        (isDoubleScoreFruit && x == fruitx && y == fruity + 1)) {
        score += isDoubleScoreFruit ? 20 : 10; // 점수 증가
        tailLength++;

        // 새로운 열매 위치 및 속성 초기화
        fruitx = rand() % (HEIGHT - 2) + 1;
        fruity = rand() % (WIDTH - 3) + 1;

        if (rand() % 100 < 60) {
            isDoubleScoreFruit = 1;
            fruitShape = doubleFruitShapes[rand() % 2];
        }
        else {
            isDoubleScoreFruit = 0;
            fruitShape = fruitShapes[rand() % (sizeof(fruitShapes) / sizeof(fruitShapes[0]))];
        }

        do {
            fruitColor = rand() % 16;
        } while (fruitColor == 0 || fruitColor == 7);

        do {
            snakeColor = rand() % 16;
        } while (snakeColor == 0 || snakeColor == 7 || snakeColor == fruitColor);

        if (score > bestScore) { // 점수 갱신 체크
            bestScore = score;
            saveBestScore();
        }
    }

    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameover = 1;
        }
    }

    Sleep(50);
}


int main() {
    srand(time(0));
    hideCursor();
    loadBestScore();
    setup();

    while (!gameover) {
        draw();
        if (_kbhit()) {
            char key = _getch();
            key = tolower(key);
            switch (key) {
            case 'a': if (flag != 3) flag = 1; leftCount++; break;
            case 's': if (flag != 4) flag = 2; downCount++; break;
            case 'd': if (flag != 1) flag = 3; rightCount++; break;
            case 'w': if (flag != 2) flag = 4; upCount++; break;
            case 'r': setup(); break;
            case 'x': gameover = 1; break;
            }
        }
        logic();
    }

    gotoxy(HEIGHT + 2, 0);
    if (score > bestScore) {
        printf("최고점 갱신! Best Score: %d\n", score);
    }
    else {
        printf("게임 종료. Best Score: %d\n", bestScore);
    }

    return 0;
}