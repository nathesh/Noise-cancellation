#include "../include/FFT.h"
void inputsignal(fftw_complex* signal,SAMPLE* Record) {
	int k; 
	for (k = 0; k < FRAMES_PER_BUFFER/2; ++k) {
        
        signal[k][REAL] = Record[k];

        signal[k][IMAG] = 0;
    }

}

fftw_complex* input(SAMPLE* Record) {
	fftw_complex *in, *out;
	fftw_plan p;
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FRAMES_PER_BUFFER);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * FRAMES_PER_BUFFER);
	p = fftw_plan_dft_1d(FRAMES_PER_BUFFER, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	inputsignal(in,Record); 
	fftw_execute(p); /* repeat as needed */
	return out;
//	DUDE WE NEED TO FIX THIS>>>
//	fftw_destroy_plan(p);
//	fftw_free(in); fftw_free(out);
//	return 0; 
}

