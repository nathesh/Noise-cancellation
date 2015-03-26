#include "../include/Weighting.h"
#include "../include/FFT.h"
#include "../include/Record.h"
#include <stdio.h>
#include <math.h>



//A weight before or after seperation into bins
float* A_compute_coeff() {
	int i;
	int freq;
	float* A = malloc(sizeof(float) * SAMPLE_RATE/(2*F_RES));
  for (i=0; i < FRAMES_PER_BUFFER/2; i++) {
       freq = i * F_RES;
       A[i] = 20*log10(((Y4 *pow(freq,4))/ 
              ((Y1 + pow(freq,2)) * sqrt(Y2 + pow(freq,2)) * sqrt(Y3 + pow(freq,2)) * (Y4 + pow(freq,2)))))+2;
	//		 printf("freq:%3d  %12f \n",i*F_RES,A[i]);
		}
	return A;
}

/*fftw_complex */float* A_weighted(fftw_complex * fftdata) {
  	//take magnitude of 
	int i;
	float mag;
	float sum = 0;
	float* bands = malloc(sizeof(float) * NUM_BINS);
 //init bands with 0's
	for (i=0; i<NUM_BINS; i++){
		bands[i] = 0;
}
  //do this better where A is a global variable
	int max[2];
max[0] = 0;
max[1] = 0;
int index = (int) floor(FRAMES_PER_BUFFER/(2*NUM_BINS));
float* A = A_compute_coeff();
for (i = 0; i < FRAMES_PER_BUFFER/2; i++) {
       mag = (float) sqrt(fftdata[i][REAL]*fftdata[i][REAL]+
                    fftdata[i][IMAG]*fftdata[i][IMAG]);
       mag = 20*log10(mag);
       mag += A[i];
			// printf("%4.1f",mag);
      //is there a better way to check if btw - and infinity
			  if((-10000 < mag)&&(mag < 10000)){
         //  printf("freq: %d  bin:%d mag:%4.1f dB \n",i*F_RES,(int)floor(i*F_RES*NUM_BINS*2/SAMPLE_RATE),mag);
				   bands[(int)floor(i/index)] += mag;
				   //printf("%d\n",(int)floor(i/index));
				  // printf("freq:%d %d \n",2*i*F_RES,mag);
				   sum += bands[(int)floor(i*F_RES*NUM_BINS*2/SAMPLE_RATE)];
					if (max[0]<mag){
						  max[0] = mag;
							max[1] = i;
}
				}
				//printf("freq:%d %d \n",2*max[1]*F_RES,max[0]);
}
//	printf("%4.1f",sum);
	for (i = 0; i < NUM_BINS; i++) {
	    bands[i] /= FRAMES_PER_BUFFER/NUM_BINS;
	    //printf("BAND:%d %4.1f dB \n",i,bands[i]);
	}
	return bands;
}
