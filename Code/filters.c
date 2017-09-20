#include "filters.h"
#include <math.h>

int offset = 10;

void lowPassFilter(double input[], double output[], int n){
    /*
    y_n = 2*y_(n-1) - y_(n-2) + (1/32)*(x_n - 2*x_(n-6) + x_(n-12))
    */
    
    output[n] = 2*output[n-1] - output[n-2] + (1/32)*(input[n+offset] - 2*input[n+offset-6] + input[n+offset-12]);
}

void highPassFilter(double input[], double output[], int n){
    /*
    y_n = y_(n-1) - x_n/32 + x_(n-16) - x_(n-17) + x_(n-32)/32
    */

    output[n] = output[n-1] - input[n+offset]/32 + input[n+offset-16] - input[1+offset-17] + input[n+offset-32]/32;
}

void derivativeFilter(double input[], double output[], int n){
    /*
    y_n = (1/8)*(2*x_n + x_(n-1) - x(n-3) - 2*x_(n-4))
    */

    output[n] = (1/8)*(2*input[n+offset] + input[n+offset-1] - input[n+offset-3] - 2*input[n+offset-4]);
}

void squareFilter(double output[], int n){
    /*
    y_n = sqrt((y_n)^2)
    */

    output[n] = sqrt(pow(output[n],2));
}

void movingWindowIntegration(double input[], double output[], int n){
    /*
    y_n = (1/N)*(x_(n-(N-1)) + x_(n-(N-2)) + ... + x_n)
    */

    /* Size of moving window integration*/
    double N = 30;

    /*
    Sum is saved in temp
    */
    int temp;
    for(int i=1; i<=30; i++){
        temp += input[n+offset-30-i];
    }

    /*
    Multiplication part of calculation is made
    */
    output[n] = (1/30)*temp;
}
