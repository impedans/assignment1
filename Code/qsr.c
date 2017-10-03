
#include "qsr.h"
#include <stdio.h>
#include <stdlib.h>

// This function compares the last three datapoints in the filtered data and determines if the middle data point is a peak
void peakDetection(QSR_params *params, int *filterOutput, int index)
{
    // Don't do peak detection until we have sufficient inputs
    if (index < 3){
        return;
    }

    // Check if output at index 1 is a peak
    if ((filterOutput[index-1] > filterOutput[index-2]) && (filterOutput[index-1] > filterOutput[index])){
        params->PEAKS[params->numPeaks] = filterOutput[index-1];
        params->numPeaks++;
        params->PEAKS = realloc(params->PEAKS, (params->numPeaks+1)*sizeof(int)); // Increase size of dynamic array

        if (filterOutput[index-1] > params->THRESHOLD1){
            // Calculate the RR interval
            int RR = params->samplesSinceLastRpeak;
            params->samplesSinceLastRpeak = 0;

            //Outputting warning:
            if(filterOutput[index-1] < 2000){
                printf("WARNING: R-peak value below 2000 (%d)\n\n", filterOutput[index-1]);
            }

            if ((RR > params->RR_LOW) && (RR < params->RR_HIGH)){
                //Rest miss counter
                params->RR_MISS_COUNT = 0;

                // Store peak as Rpeak
                params->RPEAKS[params->numRPeaks] = filterOutput[index-2];
                params->numRPeaks++;
                params->RPEAKS = realloc(params->RPEAKS, (params->numRPeaks+1)*sizeof(int));

                // Update the SPKF
                params->SPKF = 0.125*filterOutput[index-1] + 0.875*params->SPKF;

                // Store RR element in RecentRR and RecentRROK
                if(params->numRecentRR < 7){
                    params->RecentRR[params->numRecentRR] = RR;
                    params->numRecentRR++;
                } else {
                    for (int i = 0; i < params->numRecentRR; i++){
                        params->RecentRR[params->numRecentRR] = params->RecentRR[params->numRecentRR+1];
                    } 
                    params->RecentRR[params->numRecentRR] = RR;
                }
                if(params->numRecentRROK < 7){
                    params->RecentRROK[params->numRecentRROK] = RR;
                    params->numRecentRROK++;
                } else {
                    for (int i = 0; i < params->numRecentRROK; i++){
                        params->RecentRROK[params->numRecentRROK] = params->RecentRROK[params->numRecentRROK+1];
                    } 
                    params->RecentRROK[params->numRecentRROK] = RR;
                }

                // Calculate the RR averages
                int temp = 0;
                for (int i = 0; i < params->numRecentRR; i++){
                    temp += params->RecentRR[i];
                } 
                params->RR_AVERAGE1 = temp/params->numRecentRR;

                temp = 0;
                for (int i = 0; i < params->numRecentRROK; i++){
                    temp += params->RecentRROK[i];
                } 
                params->RR_AVERAGE2 = temp/params->numRecentRROK;

                // Calculate other parameters
                params->RR_LOW = 0.92*params->RR_AVERAGE2;
                params->RR_HIGH = 1.16*params->RR_AVERAGE2;
                params->RR_MISS = 1.66*params->RR_AVERAGE2;
                params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
                params->THRESHOLD2 = 0.5*params->THRESHOLD1;

                //Outputting standard values:
                printf("R-peak amplitude: %d\n", filterOutput[index-1]);
                printf("Time elapsed since start for peak: %d (ms)\n", (params->samplesTotal*100)/25);
                printf("Heart rate: %d\n\n", (RR*60)/250);
            } else{
                //Registers miss, and tests for successiv misses
                params->RR_MISS_COUNT++;
                if(params->RR_MISS_COUNT >= 5){
                    printf("WARNING: High miss count (%d)\n\n", params->RR_MISS_COUNT);
                }

                if (RR > params->RR_MISS){
                    int peak2;
                    // Search through all peaks and find the first peak above THRESHOLD2
                    for (int i = params->numPeaks-1; i >= 0; i--){
                        if (params->PEAKS[i] > params->THRESHOLD2){
                            peak2 = params->PEAKS[i];
                            break;
                        } 
                    }
                    // Store peak2 as RPEAK
                    params->RPEAKS[params->numRPeaks] = peak2;
                    params->numRPeaks++;
                    params->RPEAKS = realloc(params->RPEAKS, (params->numRPeaks+1)*sizeof(int));

                    // Calculate SPKF again
                    params->SPKF = 0.25*peak2 + 0.75*params->SPKF;

                    // Store RR in recentRR
                    if(params->numRecentRR < 7){
                        params->RecentRR[params->numRecentRR] = RR;
                        params->numRecentRR++;
                    } else {
                        for (int i = 0; i < params->numRecentRR; i++){
                            params->RecentRR[params->numRecentRR] = params->RecentRR[params->numRecentRR+1];
                        } 
                        params->RecentRR[params->numRecentRR] = RR;
                    }

                    // Update RR_AVERAGE 1
                    int temp = 0;
                    for (int i = 0; i < params->numRecentRR; i++){
                        temp += params->RecentRR[i];
                    } 
                    params->RR_AVERAGE1 = temp/params->numRecentRR;

                    // Calculate RR_LOW, RR_HIGH and RR_MISS and thresholds
                    params->RR_LOW = 0.92*params->RR_AVERAGE1;
                    params->RR_HIGH = 1.16*params->RR_AVERAGE1;
                    params->RR_MISS = 1.66*params->RR_AVERAGE1;
                    params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
                    params->THRESHOLD2 = 0.5*params->THRESHOLD1;

                } 
            }

        } else {
            params->NPKF = 0.125*filterOutput[index-2] + 0.875*params->NPKF;
            params->THRESHOLD1 = params->NPKF + 0.25*(params->SPKF-params->NPKF);
            params->THRESHOLD2 = 0.5*params->THRESHOLD1;
        }
    }

}
