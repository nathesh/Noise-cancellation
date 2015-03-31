/*
3,10,6,7,2,9,2,8,7,5
0,1,2, 3,4,5,6,7,8,9
*/
#include "../include/output.h"
#include "../include/portaudio.h"


static int outputcallback(const void *input,
                            void *output,
                            unsigned long frameCount,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData ) 
{ 
   //sleep(120);
  //printf("%s\n","Here I am!");
//						printf("%3d %12f dB\n",i*F_RES,20*log10(mag));
  }
void output(float* bands) {
	long int x;
	int y;
	for(y=0;y<10;y++) 
	{
		for(x=0;x<LENGTH;x++) {
			output_files[LENGTH*y+x] *= bands[y];
			output_sound[x] += output_files[LENGTH*y+x]/10; 
		}
		output_audio();
	//printf("%s\n","DONE!");
	}
}
void output_audio(){
	PaStreamParameters outputParameters;
	PaStream *stream;
	PaError err;
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
						44100,
						paFramesPerBufferUnspecified,
						paClipOff,      /* we won't output out of range samples so don't bother clipping them */
						outputcallback, /* no callback, use blocking API */
						&output_sound ); /* no callback, so no callback userData */
    if( err != paNoError ) goto error;

    if( stream )
    {
        err = Pa_StartStream( stream );
        sleep(2);
        if( err != paNoError ) goto error;
        printf("Waiting for playback to finish.\n"); fflush(stdout);
       	//err = Pa_WriteStream(stream, output_sound, LENGTH);
        //sleep(10);
  		//if( err != paNoError ) goto error;
  		/*
       	while(sleep(1))
   			{
			    //printf("Now I am active!!\n");
			    err = Pa_IsStreamActive( stream ) ;
			    //if( err != paNoError ) goto error;
			}
		*/
		//sleep(5);
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