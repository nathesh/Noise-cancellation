SOURCES = src/main.c src/FFT.c src/Record.c src/Weighting.c src/output.c src/output_files.c
LDFLAGS = -lfftw3 -lm -lrt -lasound -lsndfile -pthread -lportaudio
ambient_sound/sound : $(SOURCES)
	gcc -D_GNU_SOURCE -o ambient_sound/sound $(SOURCES) $(LDFLAGS)
