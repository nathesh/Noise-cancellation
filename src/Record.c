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
  //printf("%d\n",test_code++);
  SAMPLE* data = (SAMPLE*) inputBuffer; 
  SAMPLE *out = (SAMPLE*)outputBuffer;
  SAMPLE* input = (SAMPLE*) userData;
  //fftw_complex* signal = input(data);
  test = data;
	//float* bands = A_weighted(signal); 
  int j = 0;
  int i = 0;
  float sum = 0;
 
    //*input++ = *data++;

  
  //for(j = 0;j<10;j++){
   // sum += abs(bands[j]);
 // }
  //write_stream(data);
  //output(bands);
  //for(j = 0;j<10;j++) {
   //printf("BAND:%d %4.1f dB \n",j,10*abs(bands[j])/sum); 
 // }
 

  return  paContinue ;
  }
static int callback_output(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData ) 
{ 
  //printf("%d\n",test_code++);
  
  SAMPLE *out = (SAMPLE*)outputBuffer;
  SAMPLE* input = (SAMPLE*) userData;
  //fftw_complex* signal = input(data);
  //test = data;
  //float* bands = A_weighted(signal); 
  int j = 0;
  int i = 0;
  float sum = 0;
 
    //*input++ = *data++;
  for(i;i<framesPerBuffer;i++){
    printf("%s\n", "There!");
    input[LENGTH-1];
    printf("%f, %d,%d\n", 20202.9, 900,test_code);
    out[i] = input[LENGTH-1];
    test_code++;
    out[i] = input[900];
    test_code++;
  }
  


  return  paContinue ;
  }

/*******************************************************************/
float* output_files;
float* output_sound;
float* test;
int test_code;

SAMPLE* Record(void)
{
    PaStreamParameters inputParameters, outputParameters;
    PaStream *stream_input, *stream_output;
    PaError err_input, err_output;
    SAMPLE *recordedSamples;
    int i;
    int totalFrames;
    int numSamples;
    int numBytes;
    test_code = 0;
    
    output_files = output_file();
    output_sound = (float*) malloc(sizeof(float)*LENGTH);
    test         = (float*) malloc(sizeof(float)*FRAMES_PER_BUFFER*NUM_CHANNELS);
    for(i = 0;i<LENGTH;i++){
      output_sound[i] = 0;
    }
    output(recordedSamples);
    printf("patest_read_record.c\n"); fflush(stdout);
    for(i=0;i<LENGTH;i++){
      //printf("%s,%f,%d\n","Filled Buffer",*output_sound++,i);
    }
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

    err_input = Pa_Initialize();
    if( err_input != paNoError ) goto error;
    err_output = Pa_Initialize();
    if( err_output != paNoError ) goto error;
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
    outputParameters.channelCount = NUM_CHANNELS;
    outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;
    /* Record some audio. -------------------------------------------- */
    err_input = Pa_OpenStream(
              &stream_input,
              NULL,
              &outputParameters,                  /* &outputParameters, */
              SAMPLE_RATE,
              FRAMES_PER_BUFFER,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              patestCallback, /* no callback, use blocking API */
              NULL); /* no callback, so no callback userData */
    if( err_input != paNoError ) goto error;  

    err_output = Pa_OpenStream(
            &stream_output,
            NULL, 
            &outputParameters,
            44100,
            paFramesPerBufferUnspecified,
            paClipOff,      
            callback_output, 
            &output_sound);//&recordedSamples); 

    if(err_output != paNoError ) goto error;
    err_input =  Pa_StartStream(stream_input);
    err_output = Pa_StartStream(stream_output);
    while(1) {
      
      printf("%s\n","Yay" );
      sleep(5);
    }
    if(err_output != paNoError) goto error;
    if( err_input != paNoError ) goto error;
    err_input = Pa_CloseStream( stream_input);
    err_output = Pa_StopStream(stream_output);
    if( err_input != paNoError ) goto error;
    if ( err_output != paNoError) goto error;

  
  
  err_input = Pa_CloseStream( stream_input );
  if( err_input != paNoError ) goto error;
  err_output = Pa_CloseStream(stream_output);
  if( err_output != paNoError) goto error;
error:

    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream_input\n" );
    fprintf( stderr, "Error number: %d\n", err_input );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err_input ) );
    
}
