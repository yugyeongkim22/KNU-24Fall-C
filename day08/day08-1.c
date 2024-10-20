#include <stdio.h>
#include <string.h>
#include <ctype.h>

void reverse(char* str) {
    char* start = str;
    char* end = str + strlen(str) - 1;
    char temp;

    // �����ͷ� ���ڿ��� ������
    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

int main() {
    char munja[101];//�ζ����� 101
    char onlyEng[101];
    int j = 0;

    printf("���ڿ��� �Է��ϼ���: ");
   
    scanf_s("%100s", munja, (unsigned int)sizeof(munja));

    for (int i = 0; munja[i] != '\0'; i++) {
        if (isalpha((unsigned char)munja[i])) {
            onlyEng[j++] = munja[i];
        }
    }
    onlyEng[j] = '\0'; // ���ڿ��� ���� �� ���� �߰�

    // ���ڿ� ������
    reverse(onlyEng);

    printf("�������� ���ڿ�: %s\n", onlyEng);

    return 0;
}
