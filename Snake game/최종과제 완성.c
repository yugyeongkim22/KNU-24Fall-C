#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define HEIGHT 20  // ������ ���� ũ��
#define WIDTH 60   // ������ ���� ũ��
#define BEST_SCORE_FILE "best_score.txt" // �ְ��� ���� �̸�

// ���� ���� ����
int gameover, score, bestScore, upCount, downCount, leftCount, rightCount;
int x, y, fruitx, fruity, flag;
int tailX[100], tailY[100];
int tailLength = 0;
int snakeColor = 7; // �⺻ ���� (���)
char* fruitShape; // ���� ���� ��� (���ڿ��� ����)
int isDoubleScoreFruit = 0;
char* fruitShapes[] = { "#", "@", "+", "$", "\\" }; // �Ϲ� ���� ��� �迭
char* doubleFruitShapes[] = { "$$", "\\\\" }; // ���� ���ھ� ���� ��� �迭
int fruitColor; // ���� ���� ����

// �ܼ� �ؽ�Ʈ ������ �����ϴ� �Լ�
void setConsoleColor(int color) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(consoleHandle, color);
}

// �ܼ� Ŀ���� Ư�� ��ġ�� �̵���Ű�� �Լ�
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

// �ְ� ������ ���Ͽ��� �ҷ����� �Լ�
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

// �ְ� ������ ���Ͽ� �����ϴ� �Լ�
void saveBestScore() {
    if (score > bestScore) { // ������ �ְ��������� Ŭ ���� ����
        FILE* file;
        if (fopen_s(&file, BEST_SCORE_FILE, "w") == 0) {
            fprintf(file, "%d", score);
            fclose(file);
        }
        bestScore = score; // �޸��� bestScore�� ����
    }
}

// ���� �ʱ�ȭ �Լ�
void setup() {
    gameover = 0;
    score = 0;
    upCount = downCount = leftCount = rightCount = 0; // ���� Ű �Է� Ƚ�� �ʱ�ȭ

    x = HEIGHT / 4;
    y = WIDTH / 4;
    tailLength = 2; // �ʱ� ���� ����

    // �ʱ� �� ���� ��ġ ����
    tailX[0] = x;
    tailY[0] = y - 1;
    tailX[1] = x;
    tailY[1] = y - 2;

    // �ʱ� ���� ��ġ ����
    fruitx = rand() % (HEIGHT - 2) + 1;
    fruity = rand() % (WIDTH - 3) + 1;

    // ���� �Ӽ� �ʱ�ȭ
    if (rand() % 100 < 60) { // 60% Ȯ���� ���� ���ھ� ���� ����
        isDoubleScoreFruit = 1;
        fruitShape = doubleFruitShapes[rand() % 2];
    }
    else {
        isDoubleScoreFruit = 0;
        fruitShape = fruitShapes[rand() % (sizeof(fruitShapes) / sizeof(fruitShapes[0]))];
    }

    // ���ſ� �� ���� ����
    do {
        fruitColor = rand() % 16;
    } while (fruitColor == 0 || fruitColor == 7); // 0�� 7 ���� (����, �⺻ ���)

    do {
        snakeColor = rand() % 16;
    } while (snakeColor == 0 || snakeColor == 7 || snakeColor == fruitColor);

    flag = 3; // �ʱ� �̵� ���� (������)
}

// ���� ȭ���� �׸��� �Լ�
void draw() {
    gotoxy(0, 0);

    // ��� ��輱 ���
    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("\n");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0 || j == WIDTH - 1) { // �¿� ��輱
                printf("\u315C");
            }
            else if (i == x && j == y) { // ���� �Ӹ�
                setConsoleColor(snakeColor);
                printf("0");
                setConsoleColor(7); // �⺻ ���� ����
            }
            else if (i == fruitx && j == fruity) { // ���� ��ġ
                setConsoleColor(fruitColor);
                printf("%s", fruitShape);
                if (isDoubleScoreFruit) j++; // ���� ���ھ� ���Ŵ� �� ĭ ����
                setConsoleColor(7);
            }
            else {
                int isTail = 0;
                for (int k = 0; k < tailLength; k++) { // ���� ���� Ȯ��
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

    // �ϴ� ��輱 ���
    for (int i = 0; i < WIDTH; i++) printf("-");
    printf("\n");

    // ����, ���� �Է� Ƚ��, �����, ���߱� ���
    printf("aa's Score: %d  Best: %d\n", score, bestScore);
    printf("Up: %d / Down: %d / Left: %d / Right: %d\n", upCount, downCount, leftCount, rightCount);
    printf("R: Restart / X: Quit.\n");
}

// ���� ���� ó�� �Լ�
void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    // ���� ���� �̵� ó��
    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // ���⿡ ���� �̵� ó��
    switch (flag) {
    case 1: y--; break; // ���� �̵�
    case 2: x++; break; // �Ʒ��� �̵�
    case 3: y++; break; // ������ �̵�
    case 4: x--; break; // ���� �̵�
    }

    // �� �浹 �˻�
    if (x < 0 || x >= HEIGHT || y < 1 || y >= WIDTH - 1) {
        gameover = 1;
    }

    // ���� ���� ó��
    if ((x == fruitx && y == fruity) ||
        (isDoubleScoreFruit && x == fruitx && y == fruity + 1)) {
        score += isDoubleScoreFruit ? 20 : 10; // ���� ����
        tailLength++;//���� ���� ����

        // ���� ���� �� �ְ� ���� ����
        if (gameover == 0 && score > bestScore) {
            bestScore = score;
            saveBestScore();
        }

        // ���ο� ���� ��ġ �� �Ӽ� �ʱ�ȭ
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

    // �� �ڱ� �浹 �˻�
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameover = 1;
        }
    }

    Sleep(50); // ���� �ӵ� ����
}

int main() {
    srand(time(0));
    hideCursor();
    loadBestScore(); // �ְ� ���� �ε�
    setup();

    while (!gameover) {
        draw();
        if (_kbhit()) { // Ű �Է� ����
            char key = _getch();
            key = tolower(key);
            switch (key) {
            case 'a': if (flag != 3) flag = 1; leftCount++; break;
            case 's': if (flag != 4) flag = 2; downCount++; break;
            case 'd': if (flag != 1) flag = 3; rightCount++; break;
            case 'w': if (flag != 2) flag = 4; upCount++; break;
            case 'r':
                saveBestScore(); // ����� �� ���� ����
                setup(); // ���� �ʱ�ȭ
                break;
            case 'x': gameover = 1; break;
            }
        }
        logic();
    }

    gotoxy(HEIGHT + 2, 0);
    if (score > bestScore) {
        printf("�ְ��� ����! Best Score: %d\n", score);
        saveBestScore();
    }
    else {
        printf("���� ����. Best Score: %d\n", bestScore);
    }

    return 0;
}
