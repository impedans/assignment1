#ifndef FILTERS_H
#define FILTERS_H
#include <stdio.h>

// Feel free to change return statement and arguments
void lowPassFilter(double input[], double output[], int n);
void highPassFilter(double input[], double output[], int n);
void derivativeFilter(double input[], double output[], int n);
void squareFilter(double output[], int n);
void movingWindowIntegration(double input[], double output[], int n);

// Implement additional filters
 
#endif // FILTERS_H
