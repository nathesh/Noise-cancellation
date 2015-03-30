Noise-cancellation
===================

Needed libraries: 
 - portaudio
 - FFTW
 - Libsndfile 
 
To run and compile the code:
gcc main.c FFT.c Record.c Weighting.c output.c output_files.c -lfftw3 -lm -lrt -lasound -lsndfile -pthread -lportaudio -o ../output/output && ../output/output