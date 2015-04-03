/*
3,10,6,7,2,9,2,8,7,5
0,1,2, 3,4,5,6,7,8,9
*/
#include "../include/output.h"
#include "../include/portaudio.h"


void output(float* bands) {
  long int x;
  int y;
  for(y=0;y<10;y++) 
  {
    for(x=0;x<LENGTH;x++) {
      output_files[LENGTH*y+x] *= 1;//bands[y];
      output_sound[x] += output_files[LENGTH*y+x]; 
      //printf("%.15f\n",output_files[LENGTH*y+x]);
    }
    
  //printf("%s\n","DONE!");
  }
  //return output_sound
  //output_audio();
}
void output_audio(){
  PaStreamParameters outputParameters;
  PaStream *stream;
  PaError err;
  int i;
  err = Pa_Initialize();
  if(err != paNoError) 
    goto error;
  outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
      fprintf(stderr,"Error: No default output device.\n");
      goto error;
     }
    outputParameters.channelCount = 2;
    outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

  printf("Begin playback.\n"); fflush(stdout);
  err = Pa_OpenStream(
            &stream,
            NULL, /* no input */
            &outputParameters,
            SAMPLE_RATE,
            FRAMES_PER_BUFFER,
            paClipOff,      /* we won't output out of range samples so don't bother clipping them */
            NULL, /* no callback, use blocking API */
            NULL ); /* no callback, so no callback userData */
    if( err != paNoError ) goto error;

    if( stream )
    {
        err = Pa_StartStream( stream );
        err = Pa_WriteStream(stream, test, FRAMES_PER_BUFFER );        
        if( err != paNoError ) goto error;
        printf("Waiting for playback to finish.\n"); fflush(stdout);
        if( err != paNoError ) goto error;
        err = Pa_StopStream( stream );
        if( err != paNoError ) goto error;
        err = Pa_CloseStream( stream );
        if( err != paNoError ) goto error;
        printf("Done.\n"); fflush(stdout);
    }
error:

    Pa_Terminate();
    fprintf( stderr, "An error occured while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
}