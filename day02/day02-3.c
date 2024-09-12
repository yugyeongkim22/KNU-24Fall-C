

#include <stdio.h>

    int main() {
        int i;

        for (i = 0; i <= 99; i++) {
            if ((i % 12 == 0) || (i % 7 == 0)) {
                printf("%d ", i);
            }
        }

        return 0;
    }
