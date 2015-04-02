#include <portaudio.h>
#include <portaudiocpp/PortAudioCpp.hxx>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

class PowerSummer {
  public:
	PowerSummer(void) : numChans(1) {}
	int HandleSamples(const void *, void *, unsigned long,
		const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags);
  private:
	int numChans;
};

//-----------------------------------------------------------------------------
int PowerSummer::HandleSamples(const void* isamps, void* osamps,
	unsigned long nsamps, const PaStreamCallbackTimeInfo *, PaStreamCallbackFlags)
//-----------------------------------------------------------------------------
{
//	printf("%s\n", __PRETTY_FUNCTION__);

	const float* samps = (const float*) isamps;
	double powerSum[numChans];
	for (unsigned chan=0; chan<numChans; chan++) {
		for (unsigned samp=0; samp<nsamps; samp++) {
			float f = samps[chan+samp*numChans];
			powerSum[chan] += f*f;
		}
		powerSum[chan] /= nsamps;
	}

	for (unsigned chan=0; chan<numChans; chan++) {
		double psdB = 10*log10(powerSum[chan]);
		int barLen = 64 + floor(psdB-0.5);
		if (barLen<0) barLen = 0;
		printf("ch%d: %4.1f dB ", chan, psdB);
		for (unsigned i=0; i<barLen; i++)
			putchar('#');
		putchar('\n');
	}

	return paContinue;
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
	inParams.setSuggestedLatency(device.defaultLowInputLatency());
	inParams.setHostApiSpecificStreamInfo(0);

	portaudio::DirectionSpecificStreamParameters outParams
		= portaudio::DirectionSpecificStreamParameters::null();

	double sampleRate = 44100;
	unsigned long framesPerBuffer = paFramesPerBufferUnspecified;
	PaStreamFlags flags = paClipOff;
	portaudio::StreamParameters params(inParams,outParams,sampleRate,framesPerBuffer,flags);
	
	PowerSummer summer;
	portaudio::MemFunCallbackStream<PowerSummer>
		stream(params, summer, &PowerSummer::HandleSamples);

	stream.start();

	while (1) {
		sleep(5);
	}
}
