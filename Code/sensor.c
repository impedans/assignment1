#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>

int getNextData(FILE *file)
{
   int nextDataValue;
   fscanf(file, "%i", &nextDataValue);
   return(nextDataValue); 
}

FILE* openfile(const char* filename)
{
   FILE *file = fopen(filename, "r");

   return file;
}
