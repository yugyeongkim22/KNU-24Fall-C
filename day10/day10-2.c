#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX (50)

enum rank { THIRD = 3, SECOND = 2, FIRST = 1 }; // �� ��� (1�� ���� �켱������ ����)

struct Customer
{
    char customerName[NAME_MAX];
    enum rank customerRank;
    int order_amount;
    int point;
    struct Customer* prev;
    struct Customer* next;
};

struct Customer* head = NULL; // �� ����Ʈ�� ���

// ���ο� �� ��带 ����
struct Customer* create_customer(char* name, enum rank rank, int order_amount, int point)
{
    struct Customer* new_customer = (struct Customer*)malloc(sizeof(struct Customer));
    strncpy_s(new_customer->customerName, NAME_MAX, name, _TRUNCATE);  // ������ ���ڿ� ����
    new_customer->customerRank = rank;
    new_customer->order_amount = order_amount;
    new_customer->point = point;
    new_customer->prev = NULL;
    new_customer->next = NULL;

    return new_customer;
}

// ���� �켱������ ���� ����Ʈ�� ����
void insert_customer(struct Customer* new_customer)
{
    if (head == NULL) {
        head = new_customer;
    }
    else {
        struct Customer* cur = head;
        while (cur != NULL) {
            // �켱������ �°� ����
            if (new_customer->customerRank < cur->customerRank ||
                (new_customer->customerRank == cur->customerRank && new_customer->order_amount > cur->order_amount) ||
                (new_customer->customerRank == cur->customerRank && new_customer->order_amount == cur->order_amount && new_customer->point > cur->point)) {
                if (cur->prev == NULL) {
                    // ù ��° ��忡 ����
                    new_customer->next = cur;
                    cur->prev = new_customer;
                    head = new_customer;
                    return;
                }
                else {
                    // �߰��� ����
                    new_customer->next = cur;
                    new_customer->prev = cur->prev;
                    cur->prev->next = new_customer;
                    cur->prev = new_customer;
                    return;
                }
            }
            cur = cur->next;
        }

        // ����Ʈ�� �������� �߰�
        struct Customer* last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_customer;
        new_customer->prev = last;
    }
}

// ���� ����
int delete_customer(char* name)
{
    struct Customer* cur = head;
    while (cur != NULL) {
        if (strcmp(cur->customerName, name) == 0) {
            if (cur->prev != NULL) {
                cur->prev->next = cur->next;
            }
            else {
                head = cur->next; // ù ��° ��带 ������ ���
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

// ���� ����
int update_customer(char* name, enum rank rank, int order_amount, int point)
{
    struct Customer* cur = head;
    while (cur != NULL) {
        if (strcmp(cur->customerName, name) == 0) {
            // ���� ����� ������ ������Ʈ�ϱ� ���� ����Ʈ���� ����
            if (cur->prev != NULL) {
                cur->prev->next = cur->next;
            }
            else {
                head = cur->next; // ù ��° ����� ���
            }
            if (cur->next != NULL) {
                cur->next->prev = cur->prev;
            }

            // ������Ʈ�� ������ �ٽ� ����
            cur->customerRank = rank;
            cur->order_amount = order_amount;
            cur->point = point;

            cur->prev = NULL; // �ʱ�ȭ
            cur->next = NULL;
            insert_customer(cur); // �ٽ� ����
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

// �� ����Ʈ ���
void print_customers()
{
    struct Customer* cur = head;
    printf("------------------ �� ����Ʈ ------------------\n");
    while (cur != NULL) {
        printf("�̸�: %s, ���: %d, �ֹ���: %d, ����Ʈ: %d\n", cur->customerName, cur->customerRank, cur->order_amount, cur->point);
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
        printf("1. �� �߰�\n");
        printf("2. �� ����\n");
        printf("3. �� ����\n");
        printf("4. �� ����Ʈ ���\n");
        printf("5. ���α׷� ����\n");
        printf("��� �Է�: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("�̸�: ");
            scanf_s("%s", name, NAME_MAX);  // �迭 ũ�� ����
            printf("���(1- FIRST, 2- SECOND, 3- THIRD): ");
            scanf_s("%d", &rank);
            printf("�ֹ���: ");
            scanf_s("%d", &order_amount);
            printf("����Ʈ: ");
            scanf_s("%d", &point);

            insert_customer(create_customer(name, rank, order_amount, point));
            break;
        case 2:
            printf("������ ���� �̸�: ");
            scanf_s("%s", name, NAME_MAX);  // �迭 ũ�� ����
            if (delete_customer(name)) {
                printf("���� �����Ǿ����ϴ�.\n");
            }
            else {
                printf("���� ã�� �� �����ϴ�.\n");
            }
            break;
        case 3:
            printf("������ ���� �̸�: ");
            scanf_s("%s", name, NAME_MAX);  // �迭 ũ�� ����
            printf("�� ���(1- FIRST, 2- SECOND, 3- THIRD): ");
            scanf_s("%d", &rank);
            printf("�� �ֹ���: ");
            scanf_s("%d", &order_amount);
            printf("�� ����Ʈ: ");
            scanf_s("%d", &point);

            if (update_customer(name, rank, order_amount, point)) {
                printf("�� ������ �����Ǿ����ϴ�.\n");
            }
            else {
                printf("���� ã�� �� �����ϴ�.\n");
            }
            break;
        case 4:
            print_customers();
            break;
        case 5:
            return 0;
        default:
            printf("�߸��� �Է��Դϴ�.\n");
            break;
        }
    }

    return 0;
}
