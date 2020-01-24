#include "Audio.h"
#include <iostream>
#include <sstream>
#include <cstdint>

int main(int argc, char *argv[])
{
	using namespace std;



	//variables representing command line input
	int sampleRate;
	int bitCount;
	int noChannels;
	string outputName = "out.raw";
	string option;
	string inputName1;
	string inputName2;

	stringstream ss;

	//read in arguments
	//sample rate
	ss << argv[2];
	ss >> sampleRate;
	ss.clear();

	//bit count
	ss << argv[4];
	ss >> bitCount;
	ss.clear();

	//number of channels
	ss << argv[6];
	ss >> noChannels;
	ss.clear();

	//Check if output specified
	string outputOption;
	ss << argv[7];
	ss >> outputOption;
	ss.clear();
	int argPosition;
	if(outputOption == "-o")
	{
		//output name
		ss << argv[8];
		ss >> outputName;
		ss.clear();
		argPosition = 9;
	}

	else
	{
		argPosition = 7;
	}


	//option
	ss << argv[argPosition];
	ss >> option;
	ss.clear();
	argPosition++;

	//add 2 audio files
	if(option == "-add")
	{
		//input file 1
		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;

		//input file 2
		ss << argv[argPosition];
		ss >> inputName2;
		ss.clear();
		argPosition++;

		//8bit sounds
		if(bitCount == 8)
		{
			//mono sounds
			if(noChannels == 1)
			{
				RHLDEE001::Audio<int8_t,1> audioClip1(sampleRate,8);
				RHLDEE001::Audio<int8_t,1> audioClip2(sampleRate,8);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//add 2 audio files together
				RHLDEE001::Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 + audioClip2;
				audioClip3.save(outputName);

			}

			//stereo sounds
			if(noChannels == 2)
			{
				RHLDEE001::Audio<int8_t,2> audioClip1(sampleRate,8);
				RHLDEE001::Audio<int8_t,2> audioClip2(sampleRate,8);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//add 2 audio files together
				RHLDEE001::Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 + audioClip2;
				audioClip3.save(outputName);
			}

		}

		//16 bit sounds
		else if(bitCount == 16)
		{
			//mono sounds
			if(noChannels == 1)
			{
				RHLDEE001::Audio<int16_t,1> audioClip1(sampleRate,16);
				RHLDEE001::Audio<int16_t,1> audioClip2(sampleRate,16);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//add 2 audio files together
				RHLDEE001::Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 + audioClip2;
				audioClip3.save(outputName);
			}

			//stereo sounds
			if(noChannels == 2)
			{
				RHLDEE001::Audio<int16_t,2> audioClip1(sampleRate,16);
				RHLDEE001::Audio<int16_t,2> audioClip2(sampleRate,16);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//add 2 audio files together
				RHLDEE001::Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 + audioClip2;
				audioClip3.save(outputName);
			}
		}
	}

	//cut audio file in a range specified
	if(option == "-cut")
	{
		int r1;
		int r2;
		//factor value 1
		ss << argv[argPosition];
		ss >> r1;
		ss.clear();
		argPosition++;

		//factor value 2
		ss << argv[argPosition];
		ss >> r2;
		ss.clear();
		argPosition++;

		//input file 1
		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;

		//pair-consists of range to cut by
		pair<int, int> factor;
		factor.first = r1;
		factor.second = r2;

		//8bit sounds
		if(bitCount == 8)
		{
			//mono sounds
			if(noChannels == 1)
			{
				RHLDEE001::Audio<int8_t,1> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);

				//factor audio file
				RHLDEE001::Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 ^ factor;
				audioClip3.save(outputName);

			}

			//stereo sounds
			if(noChannels == 2)
			{
				RHLDEE001::Audio<int8_t,2> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);

				//add 2 audio files together
				RHLDEE001::Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 ^ factor;
				audioClip3.save(outputName);
			}

		}

		//16 bit sounds
		else if(bitCount == 16)
		{
			//mono sounds
			if(noChannels == 1)
			{
				RHLDEE001::Audio<int16_t,1> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);

				//add 2 audio files together
				RHLDEE001::Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 ^ factor;
				audioClip3.save(outputName);
			}

			//stereo sounds
			if(noChannels == 2)
			{
				RHLDEE001::Audio<int16_t,2> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);

				//add 2 audio files together
				RHLDEE001::Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 ^ factor;
				audioClip3.save(outputName);
			}
		}
	}

	if(option == "-radd")
	{
		//input file 2
		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
	}

	//concatenate audio files
	if(option == "-cat")
	{
		
		//input file 1
		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;

		//input file 2
		ss << argv[argPosition];
		ss >> inputName2;
		ss.clear();

		//8bit sounds
		if(bitCount == 8)
		{
			
			//mono sounds
			if(noChannels == 1)
			{
				
				RHLDEE001::Audio<int8_t,1> audioClip1(sampleRate,8);
				RHLDEE001::Audio<int8_t,1> audioClip2(sampleRate,8);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//concatenate 2 audio files together
				RHLDEE001::Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 | audioClip2;
				audioClip3.save(outputName);

			}

			//stereo sounds
			if(noChannels == 2)
			{
				
				RHLDEE001::Audio<int8_t,2> audioClip1(sampleRate,8);
				RHLDEE001::Audio<int8_t,2> audioClip2(sampleRate,8);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//concatenate 2 audio files together
				RHLDEE001::Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 | audioClip2;
				audioClip3.save(outputName);
			}

		}

		//16 bit sounds
		else if(bitCount == 16)
		{
			//mono sounds
			if(noChannels == 1)
			{
				RHLDEE001::Audio<int16_t,1> audioClip1(sampleRate,16);
				RHLDEE001::Audio<int16_t,1> audioClip2(sampleRate,16);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//concatenate 2 audio files together
				RHLDEE001::Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 | audioClip2;
				audioClip3.save(outputName);
			}

			//stereo sounds
			if(noChannels == 2)
			{
				RHLDEE001::Audio<int16_t,2> audioClip1(sampleRate,16);
				RHLDEE001::Audio<int16_t,2> audioClip2(sampleRate,16);
				audioClip1.load(inputName1);
				audioClip2.load(inputName2);

				//concatenate 2 audio files together
				RHLDEE001::Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 | audioClip2;
				audioClip3.save(outputName);
			}
		}
	}

	//volume factor
	if(option == "-v")
	{
		float r1;
		float r2;
		//factor value 1
		ss << argv[argPosition];
		ss >> r1;
		ss.clear();
		argPosition++;

		//factor value 2
		ss << argv[argPosition];
		ss >> r2;
		ss.clear();
		argPosition++;

		//input file 1
		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;

		//pair-consists of range to cut by
		pair<float, float> factor;
		factor.first = r1;
		factor.second = r2;

		//8bit sounds
		if(bitCount == 8)
		{
			//mono sounds
			if(noChannels == 1)
			{
				RHLDEE001::Audio<int8_t,1> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);

				//factor audio file
				RHLDEE001::Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 * factor;
				audioClip3.save(outputName);

			}

			//stereo sounds
			if(noChannels == 2)
			{
				RHLDEE001::Audio<int8_t,2> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);

				//add 2 audio files together
				RHLDEE001::Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1 * factor;
				audioClip3.save(outputName);
			}

		}

		//16 bit sounds
		else if(bitCount == 16)
		{
			//mono sounds
			if(noChannels == 1)
			{
				RHLDEE001::Audio<int16_t,1> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);

				//add 2 audio files together
				RHLDEE001::Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 * factor;
				audioClip3.save(outputName);
			}

			//stereo sounds
			if(noChannels == 2)
			{
				RHLDEE001::Audio<int16_t,2> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);

				//add 2 audio files together
				RHLDEE001::Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1 * factor;
				audioClip3.save(outputName);
			}
		}
	}

	//reverse audio clip
	if(option == "-rev")
	{
		//input file 1
		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
		argPosition++;



		//8bit sounds
		if(bitCount == 8)
		{
			//mono sounds
			if(noChannels == 1)
			{
				RHLDEE001::Audio<int8_t,1> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);

				//factor audio file
				RHLDEE001::Audio<int8_t,1> audioClip3(sampleRate,8);
				audioClip3 = audioClip1.reverseClip();
				audioClip3.save(outputName);

			}

			//stereo sounds
			if(noChannels == 2)
			{
				RHLDEE001::Audio<int8_t,2> audioClip1(sampleRate,8);
				audioClip1.load(inputName1);

				//add 2 audio files together
				RHLDEE001::Audio<int8_t,2> audioClip3(sampleRate,8);
				audioClip3 = audioClip1.reverseClip();
				audioClip3.save(outputName);
			}

		}

		//16 bit sounds
		else if(bitCount == 16)
		{
			//mono sounds
			if(noChannels == 1)
			{
				RHLDEE001::Audio<int16_t,1> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);

				//add 2 audio files together
				RHLDEE001::Audio<int16_t,1> audioClip3(sampleRate,16);
				audioClip3 = audioClip1.reverseClip();
				audioClip3.save(outputName);
			}

			//stereo sounds
			if(noChannels == 2)
			{
				RHLDEE001::Audio<int16_t,2> audioClip1(sampleRate,16);
				audioClip1.load(inputName1);

				//add 2 audio files together
				RHLDEE001::Audio<int16_t,2> audioClip3(sampleRate,16);
				audioClip3 = audioClip1.reverseClip();
				audioClip3.save(outputName);
			}
		}
	}

	if(option == "-rms")
	{

	}

	if(option == "-norm")
	{
		//input file 2
		ss << argv[argPosition];
		ss >> inputName1;
		ss.clear();
	}



}
