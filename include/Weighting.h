#include "../include/FFT.h"
#include "../include/Record.h"
#define NUM_BINS 10
#define F_RES SAMPLE_RATE/(2*FRAMES_PER_BUFFER)
#define Y1 20.598997*20.598997
#define Y2 107.65265*107.65265
#define Y3 737.86223*737.86223
#define Y4 12194.217*12194.217
float* A_compute_coeff();
float* A_weighted(fftw_complex* fftdata);
