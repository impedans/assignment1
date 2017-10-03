#include "filters.h"
#include <math.h>

void lowPassFilter(int input[], int output[], int n){
    /*
    y_n = 2*y_(n-1) - y_(n-2) + (1/32)*(x_n - 2*x_(n-6) + x_(n-12))
    */
    
    if(n>=12){  
        output[n] = 2*output[n-1] - output[n-2] + ((input[n] - 2*input[n-6] + input[n-12])/32);
    } else if(n >= 6){
        output[n] = 2*output[n-1] - output[n-2] + ((input[n] - 2*input[n-6])/32);
    } else{
        if(n >= 2){
            output[n] = 2*output[n-1] - output[n-2] + (input[n]/32);
        } else if(n == 1){
            output[1] = 2*output[0] + (input[n]/32);
        } else{
            output[0] = input[n]/32;
        }
    }
   
//    printf("\nThese are the values %lf = 2*%lf-%lf+(1/32)*(%lf-2*%lf+%lf)\n", output[2], output[1], output[0], input[n], input[n-6], input[n-12]);
}

void highPassFilter(int input[], int output[], int n){
    /*
    y_n = y_(n-1) - x_n/32 + x_(n-16) - x_(n-17) + x_(n-32)/32
    */

    if(n>=32){
        output[n] = output[n-1] - input[n]/32 + input[n-16] - input[n-17] + input[n-32]/32;
    } else if(n>=17){
        output[n] = output[n-1] - input[n]/32 + input[n-16] - input[n-17];
    } else if(n>=16){
        output[n] = output[n-1] - input[n]/32 + input[n-16];
    } else if(n>=1){
        output[n] = output[n-1] - input[n]/32;
    } else{
        output[n] =-input[n]/32;
    }
}

void derivativeFilter(int input[], int output[], int n){
    /*
    y_n = (1/8)*(2*x_n + x_(n-1) - x(n-3) - 2*x_(n-4))
    */

    if(n>=4){
        output[n] = (2*input[n] + input[n-1] - input[n-3] - 2*input[n-4])/8;
    } else if(n==3){
        output[n] = (2*input[n] + input[n-1] - input[n-3])/8;
    } else if(n==1){
        output[n] = (2*input[n] + input[n-1])/8;
    } else{
        output[n] = (2*input[n])/8;
    }
}

void squareFilter(int output[], int n){
    /*
    y_n = sqrt((y_n)^2)
    */

    output[n] = pow(output[n],2);
}

void movingWindowIntegration(int input[], int output[], int n){
    /*
    y_n = (1/N)*(x_(n-(N-1)) + x_(n-(N-2)) + ... + x_n)
    */
    int temp = 0;

    if(n < 30){
        /* Size of moving window integration*/
        int N = n+1;
    
        /* Sum is saved in temp*/
        for(int i=1; i<=N; i++){
            temp += (input[n-(N-i)]);
        }

        /* Multiplication part of calculation is made*/
        output[n] = temp/N;
    } else{
        /* Size of moving window integration*/
        int N = 30;

        /* Sum is saved in temp*/
        for(int i=1; i<=N; i++){
            temp += (input[n-(N-i)]);
        }

        /* Multiplication part of calculation is made*/
        output[n] = temp/N;
    }
}
