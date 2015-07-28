#ifndef SAMPLES_H
#define SAMPLES_H

#include <Audio.h>
#include <SerialFlash.h>
#include <play_serial_raw.h>

#define SAMPLE_COUNT				12
#define CHANNEL_COUNT				11

//If 
#define DOUBLE_HIT_THRESHOLD		20

namespace digitalcave {

	class Samples {
		private:
			//All the audio junk.  This, most notably the AudioConnection objects, 
			// need to be explicitly defined and can't really be automated to 
			// fit properly depending on the SAMPLE_COUNT.  We keep the SAMPLE_COUNT
			// for self-documenting purposes, but note that it can't really be changed
			// and expected to work without other code changes to support it.
			AudioPlaySerialRaw samples[SAMPLE_COUNT];
			AudioMixer16 mixer;
			AudioOutputI2S output;
			AudioInputI2Sslave input;
			
			//Samples to mixer
			AudioConnection patchCord00;
			AudioConnection patchCord01;
			AudioConnection patchCord02;
			AudioConnection patchCord03;
			AudioConnection patchCord04;
			AudioConnection patchCord05;
			AudioConnection patchCord06;
			AudioConnection patchCord07;
			AudioConnection patchCord08;
			AudioConnection patchCord09;
			AudioConnection patchCord10;
			AudioConnection patchCord11;
			
			//Input passthrough to mixer
			AudioConnection patchCord12;
			AudioConnection patchCord13;

			//Mixer to output
			AudioConnection patchCord14;
			AudioConnection patchCord15;

			//The index of this array is the sample index;
			// the value is the channel which was last played
			// on the given sample.  Init'd to 0xFF.
			uint8_t sampleToChannelMap[SAMPLE_COUNT];
			
			//The index of this array is the channel number;
			// the value is the sample index which was last 
			// played for the given channel.  Init'd to 0xFF.
			uint8_t channelToSampleMap[CHANNEL_COUNT];
			
			//The time in millis in which this channel was last played.
			// Used for double hit threshold detection.
			uint32_t lastPlayedChannel[CHANNEL_COUNT];
			
			//Find the first available sample that is not currently playing; if all samples
			// are playing, then find the oldest one to stop it.
			uint8_t findAvailableSample();
			
			
		public:
			Samples();
			
			void play(uint8_t channel, uint8_t value);

	};
	
}

#endif