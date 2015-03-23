Noise-cancellation
===================

Needed libraries: 
 - portaudio
 - FFTW 
To run and compile the code:
gcc main.c FFT.c Record.c Weighting.c -lfftw3 -lm -lrt -lasound -pthread -lportaudio -o ../output/output && ../output/output