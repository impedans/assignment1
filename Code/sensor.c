#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>

double getNextData(FILE *file)
{
   double nextDataValue;
   fscanf(file, "%lf", &nextDataValue);
   //printf("DEBUG: %f\n", nextDataValue);
   return(nextDataValue); 
}

FILE* openfile(const char* filename)
{
   FILE *file = fopen(filename, "r");

   return file;
}
