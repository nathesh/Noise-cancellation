#include "../include/portaudio.h"
#include "../include/FFT.h"
#include "../include/Record.h"
#include "../include/Weighting.h"
#include "../include/output_files.h"
#include "../include/output.h"
#include <math.h>

static int patestCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData ) 
{ 
  printf("%d\n",test_counter++);
  SAMPLE* data = (SAMPLE*) inputBuffer; 
  SAMPLE *out = (SAMPLE*)outputBuffer;
  fftw_complex* signal = input(data);
  test = data;
	float* bands = A_weighted(signal); 
  int j = 0;
  int i = 0;
  float sum = 0;
  for(j = 0;j<10;j++){
    sum += abs(bands[j]);
  }
  output(bands);
  for(j = 0;j<10;j++) {
   //printf("BAND:%d %4.1f dB \n",j,10*abs(bands[j])/sum); 
  }
  /*
  for(j = 0;j<LENGTH;j++) {
      out[j%framesPerBuffer] = output_sound[j]; 
      //printf("%d, %.8f\n",j,out[j%framesPerBuffer]);
      //out[j%framesPerBuffer] = *output_sound++; 
  
  }
    */

  return 0;
  }
/*******************************************************************/
float* output_files;
float* output_sound;
float* test;
int test_counter;

SAMPLE* Record(void)
{
    test_counter = 0;
    PaStreamParameters inputParameters, outputParameters;
    PaStream *stream;
    PaError err;
    SAMPLE *recordedSamples;
    int i;
    int totalFrames;
    int numSamples;
    int numBytes;

    
    output_files = output_file();
    output_sound = (float*) malloc(sizeof(float)*LENGTH);
    test         = (float*) malloc(sizeof(float)*FRAMES_PER_BUFFER*NUM_CHANNELS);
    for(i = 0;i<LENGTH;i++){
      output_sound[i] = 0;
    }

    printf("patest_read_record.c\n"); fflush(stdout);

    totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
    numSamples = totalFrames * NUM_CHANNELS; 

    numBytes = numSamples * sizeof(SAMPLE);
    recordedSamples = (SAMPLE *) malloc( numBytes );
    if( recordedSamples == NULL )
    {
        printf("Could not allocate record array.\n");
        exit(1);
    }
    for( i=0; i<numSamples; i++ ) recordedSamples[i] = 0;

    err = Pa_Initialize();
    if( err != paNoError ) goto error;

    inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
    if (inputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default input device.\n");
      goto error;
   }
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;
   
    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default output device.\n");
      goto error;
     }
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    /* Record some audio. -------------------------------------------- */
    err = Pa_OpenStream(
              &stream,
              &inputParameters,
              NULL,                  /* &outputParameters, */
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              patestCallback, /* no callback, use blocking API */
              &recordedSamples ); /* no callback, so no callback userData */
    if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;
    printf("Now recording!!\n"); fflush(stdout);

   while(1)
   {
    //printf("Now I am active!!\n");
    err = Pa_IsStreamActive( stream ) ;
    //if( err != paNoError ) goto error;
   }
  err = Pa_StopStream( stream );
  if( err != paNoError ) goto error;
    
    
    /* Measure maximum peak amplitude. */
   
    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

    
    /*
    printf("Number of Samples= %d\n", numSamples);
    printf("Sample max amplitude = "PRINTF_S_FORMAT"\n", max);
    printf("Sample average = "PRINTF_S_FORMAT"\n", average);
/**
/*  Was as below. Better choose at compile time because this
    keeps generating compiler-warnings:
    if( PA_SAMPLE_TYPE == paFloat32 )
    {
        printf("sample max amplitude = %f\n", max );
        printf("sample average = %f\n", average );
    }
    else
    {
        printf("sample max amplitude = %d\n", max );
        printf("sample average = %d\n", average );
    }
*/
    /* Write recorded data to a file. */
#if 0
    {
        FILE  *fid;
        fid = fopen("recorded.raw", "wb");
        if( fid == NULL )
        {
            printf("Could not open file.");
        }
        else
        {
            fwrite( recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), totalFrames, fid );
            fclose( fid );
            printf("Wrote data to 'recorded.raw'\n");
        }
    }
#endif

    /* Playback recorded data.  -------------------------------------------- */
    

error:

    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    
}
