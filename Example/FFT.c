#include <math.h>

#include <fftw3.h>
#define N 128 
#define REAL 0
#define IMAG 1

void inputsignal(fftw_complex* signal) {
	int i; 
	for (i = 0; i < N; ++i) {
        double theta = (double)i / (double)N * M_PI;

        signal[i][REAL] = 1.0 * cos(10.0 * theta) +
                          0.5 * cos(25.0 * theta);

        signal[i][IMAG] = 1.0 * sin(10.0 * theta) +
                          0.5 * sin(25.0 * theta);
    }

}
void output(fftw_complex* signal) {
	int i;
    for (i = 0; i < N; ++i) {
        double mag = sqrt(signal[i][REAL] * signal[i][REAL] +
                          signal[i][IMAG] * signal[i][IMAG]);

        printf("%g\n", mag);
    }

}

int main() {
	fftw_complex *in, *out;
	fftw_plan p;
	in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
	p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	inputsignal(in); 
	fftw_execute(p); /* repeat as needed */
	output(out); 
	fftw_destroy_plan(p);
	fftw_free(in); fftw_free(out);
	return 0; 
}

