#include <stdio.h>
#include "../include/Record.h"
#include "../include/FFT.h"

int main() 
{
	SAMPLE* recordedSamples = Record();
	fftw_complex* signal = input(recordedSamples);
	int i;
    for (i = 0; i < NUM_SAMPLES; ++i) 
    {
        double mag = sqrt(signal[i][REAL] * signal[i][REAL] +
                          signal[i][IMAG] * signal[i][IMAG]);

       // printf("%d\n", i);
    }

        printf("%d\n", i);
        printf("%d\n", NUM_SAMPLES);
    //A_weighted_Signal = A_weighted(signal);
    //Filtered_Bands = filter(A_weighted_Signal); // returns the signal as filtered bands 
    //output_weights = output_weights(Filtered_Bands); // output of n bands and the weights for each band.
    return 0;
}// 2*pi*n/T is N is the number of samples and T is current sample 	
