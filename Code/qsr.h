#ifndef QSR_H
#define QSR_H

typedef struct QRS_params
{ // Structure for QRS parameters
   int SPKF;
   int NPKF; 
   int THRESHOLD1;
   int THRESHOLD2;
   /*double SPKF;
   double NPKF; 
   double THRESHOLD1;
   double THRESHOLD2;*/
   
   int numPeaks;
   int *PEAKS;
   int numRPeaks;
   int *RPEAKS;
   int numRecentRR;
   int *RecentRR;
   //double *RecentRR;
   int numRecentRROK;
   int *RecentRROK;
   //double *RecentRROK;

   int samplesSinceLastRpeak;
   int samplesSinceLastRpeakTemp;

   int RR_AVERAGE1;
   int RR_AVERAGE2;
   int RR_LOW;
   int RR_HIGH;
   int RR_MISS;
   /*double RR_AVERAGE1;
   double RR_AVERAGE2;
   double RR_LOW;
   double RR_HIGH;
   double RR_MISS;*/
} QRS_params;

void peakDetection(QRS_params *params, int filterOutput[], int numInputs);

#endif // QSR_H
