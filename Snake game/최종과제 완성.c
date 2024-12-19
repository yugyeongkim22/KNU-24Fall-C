#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define HEIGHT 20  // 게임판 세로 크기
#define WIDTH 60   // 게임판 가로 크기
#define BEST_SCORE_FILE "best_score.txt" // 최고점 파일 이름

// 전역 변수 선언
int gameover, score, bestScore, upCount, downCount, leftCount, rightCount;
int x, y, fruitx, fruity, flag;
int tailX[100], tailY[100];
int tailLength = 0;
int snakeColor = 7; // 기본 색상 (흰색)
char* fruitShape; // 현재 열매 모양 (문자열로 변경)
int isDoubleScoreFruit = 0;
char* fruitShapes[] = { "#", "@", "+", "$", "\\" }; // 일반 열매 모양 배열
char* doubleFruitShapes[] = { "$$", "\\\\" }; // 더블 스코어 열매 모양 배열
int fruitColor; // 현재 열매 색상

// 콘솔 텍스트 색상을 설정하는 함수
void setConsoleColor(int color) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, color);
}

// 콘솔 커서를 특정 위치로 이동시키는 함수
void gotoxy(int x, int y) {
    COORD pos = { y, x };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

// 최고 점수를 파일에서 불러오는 함수
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

// 최고 점수를 파일에 저장하는 함수
void saveBestScore() {
    if (score > bestScore) { // 점수가 최고점수보다 클 때만 저장
        FILE* file;
        if (fopen_s(&file, BEST_SCORE_FILE, "w") == 0) {
            fprintf(file, "%d", score);
            fclose(file);
        }
        bestScore = score; // 메모리의 bestScore도 갱신
    }
}

// 게임 초기화 함수
void setup() {
    gameover = 0;
    score = 0;
    upCount = downCount = leftCount = rightCount = 0; // 방향 키 입력 횟수 초기화

    x = HEIGHT / 4;
    y = WIDTH / 4;
    tailLength = 2; // 초기 꼬리 길이

    // 초기 뱀 꼬리 위치 설정
    tailX[0] = x;
    tailY[0] = y - 1;
    tailX[1] = x;
    tailY[1] = y - 2;

    // 초기 열매 위치 설정
    fruitx = rand() % (HEIGHT - 2) + 1;
    fruity = rand() % (WIDTH - 3) + 1;

    // 열매 속성 초기화
    if (rand() % 100 < 60) { // 60% 확률로 더블 스코어 열매 생성
        isDoubleScoreFruit = 1;
        fruitShape = doubleFruitShapes[rand() % 2];
    }
    else {
        isDoubleScoreFruit = 0;
        fruitShape = fruitShapes[rand() % (sizeof(fruitShapes) / sizeof(fruitShapes[0]))];
    }

    // 열매와 뱀 색상 설정
    do {
        fruitColor = rand() % 16;
    } while (fruitColor == 0 || fruitColor == 7); // 0과 7 제외 (검정, 기본 흰색)

    do {
        snakeColor = rand() % 16;
    } while (snakeColor == 0 || snakeColor == 7 || snakeColor == fruitColor);

    flag = 3; // 초기 이동 방향 (오른쪽)
}

// 게임 화면을 그리는 함수
void draw() {
    gotoxy(0, 0);

    // 상단 경계선 출력
    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 1) { // 좌우 경계선
                printf("\u315C");
            }
            else if (i == x && j == y) { // 뱀의 머리
                setConsoleColor(snakeColor);
                printf("0");
                setConsoleColor(7); // 기본 색상 복원
            }
            else if (i == fruitx && j == fruity) { // 열매 위치
                setConsoleColor(fruitColor);
                printf("%s", fruitShape);
                if (isDoubleScoreFruit) j++; // 더블 스코어 열매는 두 칸 차지
                setConsoleColor(7);
            }
            else {
                int isTail = 0;
                for (int k = 0; k < tailLength; k++) { // 뱀의 꼬리 확인
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

    // 하단 경계선 출력
    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("\n");

    // 점수, 방향 입력 횟수, 재시작, 멈추기 출력
    printf("aa's Score: %d  Best: %d\n", score, bestScore);
    printf("Up: %d / Down: %d / Left: %d / Right: %d\n", upCount, downCount, leftCount, rightCount);
    printf("R: Restart / X: Quit.\n");
}

// 게임 로직 처리 함수
void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    // 뱀의 꼬리 이동 처리
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // 방향에 따른 이동 처리
    switch (flag) {
    case 1: y--; break; // 왼쪽 이동
    case 2: x++; break; // 아래로 이동
    case 3: y++; break; // 오른쪽 이동
    case 4: x--; break; // 위로 이동
    }

    // 벽 충돌 검사
    if (x < 0 || x >= HEIGHT || y < 1 || y >= WIDTH - 1) {
        gameover = 1;
    }

    // 열매 섭취 처리
    if ((x == fruitx && y == fruity) ||
        (isDoubleScoreFruit && x == fruitx && y == fruity + 1)) {
        score += isDoubleScoreFruit ? 20 : 10; // 점수 증가
        tailLength++;//꼬리 길이 증가

        // 점수 증가 후 최고 점수 갱신
        if (gameover == 0 && score > bestScore) {
            bestScore = score;
            saveBestScore();
        }

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
    }

    // 뱀 자기 충돌 검사
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameover = 1;
        }
    }

    Sleep(50); // 게임 속도 조절
}

int main() {
    srand(time(0));
    hideCursor();
    loadBestScore(); // 최고 점수 로드
    setup();

    while (!gameover) {
        draw();
        if (_kbhit()) { // 키 입력 감지
            char key = _getch();
            key = tolower(key);
            switch (key) {
            case 'a': if (flag != 3) flag = 1; leftCount++; break;
            case 's': if (flag != 4) flag = 2; downCount++; break;
            case 'd': if (flag != 1) flag = 3; rightCount++; break;
            case 'w': if (flag != 2) flag = 4; upCount++; break;
            case 'r':
                saveBestScore(); // 재시작 전 점수 저장
                setup(); // 게임 초기화
                break;
            case 'x': gameover = 1; break;
            }
        }
        logic();
    }

    gotoxy(HEIGHT + 2, 0);
    if (score > bestScore) {
        printf("최고점 갱신! Best Score: %d\n", score);
        saveBestScore();
    }
    else {
        printf("게임 종료. Best Score: %d\n", bestScore);
    }

    return 0;
}
