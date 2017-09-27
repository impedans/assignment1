#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int offset = 9;
int n = 3;
double output[] = {0, 0, 0, 0}; 
double input[] = {10, 20, 15, 12, 8, 5, 15, 11, 7, 8, 20, 64, 53, 20, 40};   

int main(){
    /*
    y_n = 2*y_(n-1) - y_(n-2) + (1/32)*(x_n - 2*x_(n-6) + x_(n-12))
    */
    n--;
    
    output[n] = 2.0*output[n-1] - output[n-2] + (1.0/32.0)*(input[n+offset] - 2.0*input[n+offset-6] + input[n+offset-12]);

    printf("Whatever: %lf\n", output[n]);

    return 0;
}
