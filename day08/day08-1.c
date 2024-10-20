#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverse(char* str) {
    char* start = str;
    char* end = str + strlen(str) - 1;
    char temp;

    // 포인터로 문자열을 뒤집음
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

int main() {
    char munja[101];//널때문에 101
    char onlyEng[101];
    int j = 0;

    printf("문자열을 입력하세요: ");
   
    scanf_s("%100s", munja, (unsigned int)sizeof(munja));

    for (int i = 0; munja[i] != '\0'; i++) {
        if (isalpha((unsigned char)munja[i])) {
            onlyEng[j++] = munja[i];
        }
    }
    onlyEng[j] = '\0'; // 문자열의 끝에 널 문자 추가

    // 문자열 뒤집기
    reverse(onlyEng);

    printf("뒤집어진 문자열: %s\n", onlyEng);

    return 0;
}
