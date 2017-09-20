#ifndef FILTERS_H
#define FILTERS_H

// Feel free to change return statement and arguments
void lowPassFilter(int input[], int output[], int n);
void highPassFilter(int input[], int output[], int n);
void derivativeFilter(int input[], int output[], int n);
void squareFilter(int output[], int n);
void movingWindowIntegration(int input[], int output[], int n);

// Implement additional filters
 
#endif // FILTERS_H
