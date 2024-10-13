#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void) {
    double x = 0; 
    double y = 0; 
    double r = 1.0; 

    int count = 0; 
    int circle = 0; 
    int allBanBok = 1000000000; 
    int pyosi = 10000000;
    int allNemo = 20;
    int progressNemo = 0; 
    double estimate; 

    srand(time(NULL)); 

    
    while (count < allBanBok) {
       
        x = ((double)rand() / (double)RAND_MAX) * r;
        y = ((double)rand() / (double)RAND_MAX) * r;

        
        if (sqrt(x * x + y * y) <= r) {
            circle++;
        }

        
        count++;

        
        if (count % pyosi == 0) {
            
            estimate = 4.0 * (double)circle / (double)count;

            
            int progress = (count / (allBanBok / 100)); 
            progressNemo = progress / 5; 

           
            printf("%d%% 진행.. 원주율: %.6f ", progress, estimate);

           
            for (int i = 0; i < progressNemo; i++) {
                printf("■");
            }
         
            for (int i = progressNemo; i < allNemo; i++) {
                printf("□");
            }
            printf("\n");
        }
    }

    
    estimate = 4.0 * (double)circle / (double)count;
    printf("최종 계산된 원주율: %.6f\n", estimate);

    return 0;
}
