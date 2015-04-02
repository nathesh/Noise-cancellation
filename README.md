Noise-cancellation
===================

Needed libraries: 
 - portaudio
 - FFTW
 - Libsndfile 
 
To run and compile the code:
method 1.
gcc main.c FFT.c Record.c Weighting.c output.c output_files.c -lfftw3 -lm -lrt -lasound -lsndfile -pthread -lportaudio -o ../output/output && ../output/output

method 2.
Run the make file

TO DO:
open the read and write stream first; 
Once the callback is called; write to the opened write stream; make it a queue to keep adding to output