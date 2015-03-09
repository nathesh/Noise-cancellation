#include "../include/FFT.h"
 
#define REAL 0
#define IMAG 1

void inputsignal(fftw_complex* signal,SAMPLE* Record) {
	int i; 
	for (i = 0; i < NUM_SAMPLES; ++i) {
        
        signal[i][REAL] = Record[i];

        signal[i][IMAG] = 0;
    }

}

fftw_complex* input(SAMPLE* Record) {
	fftw_complex *in, *out;
	fftw_plan p;
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NUM_SAMPLES);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NUM_SAMPLES);
	p = fftw_plan_dft_1d(NUM_SAMPLES, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	inputsignal(in,Record); 
	fftw_execute(p); /* repeat as needed */
	return out;
	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);
	return 0; 
}

