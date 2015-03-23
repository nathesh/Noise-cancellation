typedef float SAMPLE;
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_SAMPLES (8000)
#define FRAMES_PER_BUFFER (1024)
#define SAMPLE_RATE  (8000) 
#define NUM_SECONDS     (5)
#define NUM_CHANNELS    (2)
#define PA_SAMPLE_TYPE  paFloat32
#define SAMPLE_SILENCE  (0.0f)
/* #define DITHER_FLAG     (paDitherOff)  */
#define DITHER_FLAG     (0) /**/
SAMPLE* Record(void); 
