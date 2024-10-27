#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5

// Product ����ü ����
typedef struct {
    int id;
    char name[50];
    int price;
} Product;

// ��ǰ ������ ����ϴ� �Լ�
void infoProduct(Product p) {
    printf("��ǰ ID: %d\n", p.id);
    printf("��ǰ��: %s\n", p.name);
    printf("����: %d\n", p.price);
}

int main() {
    Product products[MAX_PRODUCTS]; // �ִ� 5���� ��ǰ�� ������ �迭
    int count = 0; // �Էµ� ��ǰ�� ����

    while (count < MAX_PRODUCTS) {
        int id;
        printf("��ǰ������ �Է��ϼ��� (�Է��ߴ��� id�� 0�Է�)\n");
        printf("��ǰ ID: ");
        scanf_s("%d", &id);

        if (id == 0) { // �Է� �ߴ� ����
            break;
        }

        products[count].id = id;

        printf("��ǰ��: ");
        scanf_s(" %[^\n]", products[count].name, sizeof(products[count].name));

        printf("����: ");
        scanf_s("%d", &products[count].price);

        count++;
    }

    printf("\n<<�Էµ� ��ǰ ǰ��>>\n");
    for (int i = 0; i < count; i++) {
        infoProduct(products[i]);
        printf("\n");
    }

    return 0;
}
