#include <stdio.h>
#include <math.h>


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main() {
   
    printf("%d\n", abs(-4)); 

    
    printf("%lf\n", sin(30 * (M_PI / 180))); 

    
    printf("%lf\n", cos(30 * (M_PI / 180))); 

   
    printf("%lf\n", sqrt(2.5)); 

   
    printf("%lf\n", pow(1.5, 4.0)); 


    return 0;
}
