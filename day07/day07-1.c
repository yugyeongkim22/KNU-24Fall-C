#include <stdio.h>

int main() {

	int floor; // 피라미드의 층 수를 저장할 변수 선언
	scanf_s("%d", &floor); // 사용자로부터 층 수를 입력 받음
	printf("%d층 피라미드\n", floor); // 입력 받은 층 수를 출력

	// i는 현재 층, 0층부터 시작
	for (int i = 0; i < floor; i++)
	{
		// j는 공백을 출력, 각 층에 대해 공백을 출력하여 피라미드 모양을 맞춤
		for (int j = i; j < floor - 1; j++)
		{
			printf(" "); // 왼쪽에 필요한 공백을 출력
		}

		// k는 각 층에 찍힐 '*'의 개수
		for (int k = 0; k < i * 2 + 1; k++)
		{
			printf("*"); // '*'을 출력하여 피라미드 만들기
		}
		printf("\n"); // 한 층이 끝나면 다음 줄로
	}

	return 0; // 프로그램 종료
}

