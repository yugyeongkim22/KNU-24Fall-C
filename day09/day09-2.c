#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5

// Product 구조체 정의
typedef struct {
    int id;
    char name[50];
    int price;
} Product;

// 상품 정보를 출력하는 함수
void infoProduct(Product p) {
    printf("상품 ID: %d\n", p.id);
    printf("상품명: %s\n", p.name);
    printf("가격: %d\n", p.price);
}

int main() {
    Product products[MAX_PRODUCTS]; // 최대 5개의 상품을 저장할 배열
    int count = 0; // 입력된 상품의 개수

    while (count < MAX_PRODUCTS) {
        int id;
        printf("상품정보를 입력하세요 (입력중단은 id에 0입력)\n");
        printf("상품 ID: ");
        scanf_s("%d", &id);

        if (id == 0) { // 입력 중단 조건
            break;
        }

        products[count].id = id;

        printf("상품명: ");
        scanf_s(" %[^\n]", products[count].name, sizeof(products[count].name));

        printf("가격: ");
        scanf_s("%d", &products[count].price);

        count++;
    }

    printf("\n<<입력된 상품 품목>>\n");
    for (int i = 0; i < count; i++) {
        infoProduct(products[i]);
        printf("\n");
    }

    return 0;
}
