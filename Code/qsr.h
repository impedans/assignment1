#ifndef QSR_H
#define QSR_H

typedef struct QRS_params
{ // Structure for QRS parameters
   double SPKF;
   double NPKF; 
   double THRESHOLD1;
   double THRESHOLD2;
   
   int numPeaks;
   int *PEAKS;
   int numRPeaks;
   int *RPEAKS;
   int numRecentRR;
   int *RecentRR;
   int numRecentRROK;
   int *RecentRROK;

   int samplesSinceLastRpeak;

   double RR_AVERAGE1;
   double RR_AVERAGE2;
   double RR_LOW;
   double RR_HIGH;
   double RR_MISS;
} QRS_params;

void peakDetection(QRS_params *params, int filterOutput[]);

#endif // QSR_H
