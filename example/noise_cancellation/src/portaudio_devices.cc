#include <portaudio.h>
#include <portaudiocpp/PortAudioCpp.hxx>
#include <stdio.h>

int main() {
	portaudio::AutoSystem autoSystem;
	portaudio::System &sys = portaudio::System::instance();
	
	printf("PortAudio version: %d\n", sys.version());
	printf("PortAudio versionText: %s\n", sys.versionText());
	
	for (int i=0; i<sys.deviceCount(); i++) {
		portaudio::Device& device = sys.deviceByIndex(i);
		printf("- name: %s\n", device.name());
		printf("  deviceIndex: %d\n", i);
		printf("  hostAPI: %s\n", device.hostApi().name());
		printf("  maxInputChannels: %d\n", device.maxInputChannels());
		printf("  maxOutputChannels: %d\n", device.maxOutputChannels());
		printf("  defaultSampleRate: %g\n", device.defaultSampleRate());

		printf("  defaultLowInputLatency: %g\n", device.defaultLowInputLatency());
		printf("  defaultLowOutputLatency: %g\n", device.defaultLowOutputLatency());
		printf("  defaultHighInputLatency: %g\n", device.defaultHighInputLatency());
		printf("  defaultHighOutputLatency: %g\n", device.defaultHighOutputLatency());

		if (device.isSystemDefaultInputDevice()) {
			printf("  isSystemDefaultInputDevice: true\n");
		}
		if (device.isSystemDefaultOutputDevice()) {
			printf("  isSystemDefaultOutputDevice: true\n");
		}
		if (device.isHostApiDefaultInputDevice()) {
			printf("  isHostApiDefaultInputDevice: true\n");
		}
		if (device.isHostApiDefaultOutputDevice()) {
			printf("  isHostApiDefaultOutputDevice: true\n");
		}
		printf("  isFullDuplexDevice: %s\n", device.isFullDuplexDevice()?"true":"false");
	}
}
