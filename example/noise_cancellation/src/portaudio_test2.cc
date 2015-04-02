#include <portaudio.h>
#include <portaudiocpp/PortAudioCpp.hxx>
#include <stdio.h>
#include <unistd.h>
#include <math.h>


//-----------------------------------------------------------------------------
void HandleSamples(const float* samps, unsigned long nsamps)
//-----------------------------------------------------------------------------
{
//	printf("%s\n", __PRETTY_FUNCTION__);

	double powerSum;
	for (unsigned samp=0; samp<nsamps; samp++) {
		float f = samps[samp];
		powerSum += f*f;
	}
	powerSum /= nsamps;

	double psdB = 10*log10(powerSum);
	int barLen = 64 + floor(psdB-0.5);
	if (barLen<0) barLen = 0;
	printf("lvl: %4.1f dB ", psdB);
	for (unsigned i=0; i<barLen; i++)
		putchar('#');
	putchar('\n');
}

int main()
{
	portaudio::AutoSystem autoSystem;
	portaudio::System &sys = portaudio::System::instance();

	portaudio::DirectionSpecificStreamParameters inParams;
	portaudio::Device& device = sys.defaultInputDevice();
	inParams.setDevice(device);
	inParams.setNumChannels(1);
	inParams.setSampleFormat(portaudio::FLOAT32);
	inParams.setSuggestedLatency(device.defaultHighInputLatency());
	inParams.setHostApiSpecificStreamInfo(0);

	portaudio::DirectionSpecificStreamParameters outParams
		= portaudio::DirectionSpecificStreamParameters::null();

	double sampleRate = 44100;
	unsigned long framesPerBuffer = paFramesPerBufferUnspecified;
	PaStreamFlags flags = paClipOff;
	portaudio::StreamParameters params(inParams,outParams,sampleRate,framesPerBuffer,flags);
	
	portaudio::BlockingStream stream(params);
	stream.start();

	while (1) {
		const unsigned numSamps = 1024;
		flpaFramesPerBufferUnspecifiedoat samps[numSamps];
		stream.read(samps,numSamps);
		HandleSamples(samps,numSamps);
	}
}
