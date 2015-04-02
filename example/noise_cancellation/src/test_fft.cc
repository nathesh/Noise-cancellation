#include <math.h>

#include <fftw3.h>
#define N 128 
#define REAL 0
#define IMAG 1

void inputsignal(fftwf_complex* signal) {
	int i; 
	for (i = 0; i < N; ++i) {
		double theta = (double)i / (double)N * M_PI;
		signal[i][REAL] = 1.0 * cos(10.0 * theta) + 0.5 * cos(25.0 * theta);
		signal[i][IMAG] = 1.0 * sin(10.0 * theta) + 0.5 * sin(25.0 * theta);
	}
}

void output(fftwf_complex* signal) {
	int i;
	for (i = 0; i < N; ++i) {
		double mag = sqrt(signal[i][REAL] * signal[i][REAL] +
			signal[i][IMAG] * signal[i][IMAG]);
		printf("%g\n", mag);
	}
}

int main() {
	fftwf_complex *in, *out;
	fftwf_plan p;
	in = (fftwf_complex*) fftwf_malloc(sizeof(fftw_complex) * N);
	out = (fftwf_complex*) fftwf_malloc(sizeof(fftw_complex) * N);
	p = fftwf_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	inputsignal(in); 
	fftwf_execute(p); /* repeat as needed */
	output(out); 
	fftwf_destroy_plan(p);
	fftwf_free(in);
	fftwf_free(out);
	return 0; 
}
