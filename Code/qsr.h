#ifndef QSR_H
#define QSR_H

typedef struct QSR_params
{ // Structure for QRS parameters
   int SPKF;
   int NPKF; 
   int THRESHOLD1;
   int THRESHOLD2;
   
   int numPeaks;
   int *PEAKS;
   int numRPeaks;
   int *RPEAKS;
   int numRecentRR;
   int *RecentRR;
   int numRecentRROK;
   int *RecentRROK;

   int samplesSinceLastRpeak;

   int samplesTotal;

   int RR_AVERAGE1;
   int RR_AVERAGE2;
   int RR_LOW;
   int RR_HIGH;
   int RR_MISS;
   int RR_MISS_COUNT;
} QSR_params;

void peakDetection(QSR_params *params, int filterOutput[], int index);

#endif // QSR_H
