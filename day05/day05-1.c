#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    int* snum;
    char** name;
    int* score;

    printf("학생 수 입력:");
    scanf_s("%d", &N);

    snum = (int*)malloc(N * sizeof(int));
    score = (int*)malloc(N * sizeof(int));
    name = (char**)malloc(N * sizeof(char*));

    for (int i = 0; i < N; i++) {
        name[i] = (char*)malloc(100 * sizeof(char));
    }

    for (int i = 0; i < N; i++) {
        printf("학번:");
        scanf_s("%d", &snum[i]);

        printf("이름:");
        scanf_s("%s", name[i], 100);

        printf("점수:");
        scanf_s("%d", &score[i]);
    }

    for (int i = 0; i < N; i++) {
        printf("%d %s %d\n", snum[i], name[i], score[i]);
    }

    free(name);
    free(snum);
    free(score);

    return 0;
}