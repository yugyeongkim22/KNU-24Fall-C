#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX (50)

enum rank { THIRD = 3, SECOND = 2, FIRST = 1 }; // 고객 등급 (1이 가장 우선순위가 높음)

struct Customer
{
    char customerName[NAME_MAX];
    enum rank customerRank;
    int order_amount;
    int point;
    struct Customer* prev;
    struct Customer* next;
};

struct Customer* head = NULL; // 고객 리스트의 헤드

// 새로운 고객 노드를 생성
struct Customer* create_customer(char* name, enum rank rank, int order_amount, int point)
{
    struct Customer* new_customer = (struct Customer*)malloc(sizeof(struct Customer));
    strncpy_s(new_customer->customerName, NAME_MAX, name, _TRUNCATE);  // 안전한 문자열 복사
    new_customer->customerRank = rank;
    new_customer->order_amount = order_amount;
    new_customer->point = point;
    new_customer->prev = NULL;
    new_customer->next = NULL;

    return new_customer;
}

// 고객을 우선순위에 따라 리스트에 삽입
void insert_customer(struct Customer* new_customer)
{
    if (head == NULL) {
        head = new_customer;
    }
    else {
        struct Customer* cur = head;
        while (cur != NULL) {
            // 우선순위에 맞게 삽입
            if (new_customer->customerRank < cur->customerRank ||
                (new_customer->customerRank == cur->customerRank && new_customer->order_amount > cur->order_amount) ||
                (new_customer->customerRank == cur->customerRank && new_customer->order_amount == cur->order_amount && new_customer->point > cur->point)) {
                if (cur->prev == NULL) {
                    // 첫 번째 노드에 삽입
                    new_customer->next = cur;
                    cur->prev = new_customer;
                    head = new_customer;
                    return;
                }
                else {
                    // 중간에 삽입
                    new_customer->next = cur;
                    new_customer->prev = cur->prev;
                    cur->prev->next = new_customer;
                    cur->prev = new_customer;
                    return;
                }
            }
            cur = cur->next;
        }

        // 리스트의 마지막에 추가
        struct Customer* last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_customer;
        new_customer->prev = last;
    }
}

// 고객을 삭제
int delete_customer(char* name)
{
    struct Customer* cur = head;
    while (cur != NULL) {
        if (strcmp(cur->customerName, name) == 0) {
            if (cur->prev != NULL) {
                cur->prev->next = cur->next;
            }
            else {
                head = cur->next; // 첫 번째 노드를 삭제할 경우
            }
            if (cur->next != NULL) {
                cur->next->prev = cur->prev;
            }
            free(cur);
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

// 고객을 수정
int update_customer(char* name, enum rank rank, int order_amount, int point)
{
    struct Customer* cur = head;
    while (cur != NULL) {
        if (strcmp(cur->customerName, name) == 0) {
            // 현재 노드의 정보를 업데이트하기 전에 리스트에서 삭제
            if (cur->prev != NULL) {
                cur->prev->next = cur->next;
            }
            else {
                head = cur->next; // 첫 번째 노드의 경우
            }
            if (cur->next != NULL) {
                cur->next->prev = cur->prev;
            }

            // 업데이트된 정보로 다시 삽입
            cur->customerRank = rank;
            cur->order_amount = order_amount;
            cur->point = point;

            cur->prev = NULL; // 초기화
            cur->next = NULL;
            insert_customer(cur); // 다시 삽입
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

// 고객 리스트 출력
void print_customers()
{
    struct Customer* cur = head;
    printf("------------------ 고객 리스트 ------------------\n");
    while (cur != NULL) {
        printf("이름: %s, 등급: %d, 주문량: %d, 포인트: %d\n", cur->customerName, cur->customerRank, cur->order_amount, cur->point);
        cur = cur->next;
    }
    printf("--------------------------------------------\n");
}

int main()
{
    int choice;
    char name[NAME_MAX];
    enum rank rank;
    int order_amount, point;

    while (1) {
        printf("1. 고객 추가\n");
        printf("2. 고객 삭제\n");
        printf("3. 고객 수정\n");
        printf("4. 고객 리스트 출력\n");
        printf("5. 프로그램 종료\n");
        printf("명령 입력: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("이름: ");
            scanf_s("%s", name, NAME_MAX);  // 배열 크기 지정
            printf("등급(1- FIRST, 2- SECOND, 3- THIRD): ");
            scanf_s("%d", &rank);
            printf("주문량: ");
            scanf_s("%d", &order_amount);
            printf("포인트: ");
            scanf_s("%d", &point);

            insert_customer(create_customer(name, rank, order_amount, point));
            break;
        case 2:
            printf("삭제할 고객의 이름: ");
            scanf_s("%s", name, NAME_MAX);  // 배열 크기 지정
            if (delete_customer(name)) {
                printf("고객이 삭제되었습니다.\n");
            }
            else {
                printf("고객을 찾을 수 없습니다.\n");
            }
            break;
        case 3:
            printf("수정할 고객의 이름: ");
            scanf_s("%s", name, NAME_MAX);  // 배열 크기 지정
            printf("새 등급(1- FIRST, 2- SECOND, 3- THIRD): ");
            scanf_s("%d", &rank);
            printf("새 주문량: ");
            scanf_s("%d", &order_amount);
            printf("새 포인트: ");
            scanf_s("%d", &point);

            if (update_customer(name, rank, order_amount, point)) {
                printf("고객 정보가 수정되었습니다.\n");
            }
            else {
                printf("고객을 찾을 수 없습니다.\n");
            }
            break;
        case 4:
            print_customers();
            break;
        case 5:
            return 0;
        default:
            printf("잘못된 입력입니다.\n");
            break;
        }
    }

    return 0;
}
