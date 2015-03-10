#include "../include/Weighting.h"
#include "../include/FFT.h"
#include <stdio.h>
#include <math.h>
#define NUM_BINS 10
#define REAL 0
#define IMAG 0
#define SAMPLE_RATE 8000
#define F_RES SAMPLE_RATE/(2*FRAMES_PER_BUFFER)
#define X 3.5041384E16
#define Y1 20.598997*20.598997
#define Y2 107.65265*107.65265
#define Y3 737.86223*737.86223
#define Y4 12194.217*12194.217
#define FRAMES_PER_BUFFER 1024

//A weight before or after seperation into bins
float* A_compute_coeff() {
	int i;
	int freq;
	float* A = malloc(sizeof(float) * SAMPLE_RATE/(2*F_RES));
  for (i=0; i < FRAMES_PER_BUFFER; i++) {
       freq = i * F_RES;
       A[i] = ((X *pow(freq,8))/ 
              ((Y1 + pow(freq,2)) * (Y2 + pow(freq,2)) * (Y3 + pow(freq,2)) * (Y4 + pow(freq,2))));
	}
	return A;
}

/*fftw_complex */float* A_weighted(fftw_complex * fftdata) {
  	//take magnitude of 
	int i;
	float mag;
	float sum = 0;
	float* bands = malloc(sizeof(float) * NUM_BINS);
  //do this better where A is a global variable
	float* A = A_compute_coeff();
	for (i = 0; i < FRAMES_PER_BUFFER; i++) {
       mag = (float) sqrt(fftdata[i][REAL]*fftdata[i][REAL]+
                    fftdata[i][IMAG]*fftdata[i][IMAG]);
       mag *= A[i];
       bands[(int)ceil(i*F_RES/4000 * 10)] += mag;
       sum += bands[(int)ceil(i*F_RES/4000 * 10)];
	}

	for (i = 0; i < NUM_BINS; i++) {
	     bands[i] /= sum;
       bands[i] = 10*log10(bands[i]);
	     printf("%4.1f dB \n",bands[i]);
	}
	return bands;
}
