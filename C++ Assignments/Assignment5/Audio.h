#ifndef AUDIO_H_
#define AUDIO_H_
#include <memory>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <vector>


namespace RHLDEE001
{
	//partial template specialization for mono sounds
	//
	template <typename T, int Channel> class Audio
	{
		private:
		std::vector<T> data;
		int sampleRate;
		int sampleSize;
		int numChannels;
		int fileSize;
		int numberSamples;

		public:

			//constructor
			Audio(int sRate, int sSize): sampleRate(sRate), sampleSize(sSize), numChannels(Channel)
			{

			}

			//destructor
			~Audio()
			{

			}

			//copy constructor
			Audio(const Audio & rhs) : sampleRate(rhs.sampleRate), sampleSize(rhs.sampleSize), numChannels(rhs.numChannels), fileSize(rhs.fileSize), numberSamples(rhs.numberSamples)
			{
				data = rhs.data;
			}
			//move constructor
			Audio(Audio && rhs) : sampleRate(rhs.sampleRate), sampleSize(rhs.sampleSize), numChannels(rhs.numChannels), fileSize(rhs.fileSize), numberSamples(rhs.numberSamples)
			{
				this->data = rhs.data;

				rhs.sampleRate = -1;
				rhs.sampleSize = -1;
				rhs.numChannels = -1;
				rhs.numberSamples = -1;
			}

			//copy assignment
			Audio operator=(const Audio & rhs)
			{
				sampleRate = rhs.sampleRate;
				sampleSize = rhs.sampleSize;
				numChannels = rhs.numChannels;
				fileSize = rhs.fileSize;
				numberSamples = rhs.numberSamples;
				data = rhs.data;
				return *this;
			}

			//move assignment
			Audio operator=(Audio && rhs)
			{
				sampleRate = rhs.sampleRate;
				sampleSize = rhs.sampleSize;
				numChannels = rhs.numChannels;
				fileSize = rhs.fileSize;
				numberSamples = rhs.numberSamples;
				data = rhs.data;

				rhs.sampleRate = -1;
				rhs.sampleSize = -1;
				rhs.numChannels = -1;
				rhs.fileSize = -1;
				rhs.numberSamples = -1;

				return *this;
			}

			//reads raw file and stores it into image object
			void load(std::string fileName)
			{
				using namespace std;
				ifstream input;
				//read a binary file
				input.open(fileName, ios::binary);
				if(input.is_open())
				{
					//get file size
					input.seekg(0,input.end);
					fileSize = (int)(input.tellg());
					input.seekg(0, input.beg);

					//size of vector
					numberSamples = fileSize/(this->numChannels);

					data.resize(numberSamples);

					char * arr = new char[numberSamples];
					//read binary data block
					input.read(arr, numberSamples);
					for(int i = 0; i < numberSamples; i++)
					{
						data[i] = (T)(arr[i]);
					}
					delete arr;
					input.close();
				}

			}

			//save file
			void save(std::string outputName)
			{
				using namespace std;
				ofstream output(outputName, ios::binary);
				if(output.is_open())
				{
					char * arr = new char[numberSamples];
					for(int i = 0; i < numberSamples; ++i)
					{
						arr[i] = (char)data[i];
					}

					output.write(arr, numberSamples);
					delete arr;
					output.close();
				}
			}

			//overloaded operators
			//concatenate audio files
			Audio operator| (Audio & rhs)
		    {

				using namespace std;
				//AudioClip -> new object. copy attributes
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize + rhs.fileSize;
				audioClip.numberSamples = this->numberSamples + rhs.numberSamples;
				audioClip.data.resize(audioClip.numberSamples);
				int size = this->data.size();
				int sizeRhs = rhs.data.size();


				//loop through this data
				for(int i = 0; i < size; i++)
				{
					//append this data
					audioClip.data[i] = this->data[i];
				}

				//loop through rhs data
				for(int i = size, k=0; k < sizeRhs; i++,k++)
				{
					//append rhs data
				    audioClip.data[i] = rhs.data[k];
				}

				return audioClip;
			}


			//Volume factor
			Audio operator* (std::pair<float,float> factor)
			{
				using namespace std;
				//create new Audio object
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize;
				audioClip.numberSamples = this->numberSamples;
				audioClip.data.resize(audioClip.numberSamples);
				int size = audioClip.data.size();

				//loop through data
				for(int i = 0; i < size; i++)
				{
					//change volume
					audioClip.data[i] = this->data[i] * factor.first;
				}
				return audioClip;
			}


			Audio operator+ (Audio & rhs)
			{
				using namespace std;
				//AudioClip -> new object. copy attributes
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize + rhs.fileSize;
				audioClip.numberSamples = this->numberSamples;
				audioClip.data.resize(audioClip.numberSamples);

				//size of vector. loop by size
				int size = this->data.size();

				//loop through this data
				for(int i = 0; i < size; i++)
				{
					//append this data
					audioClip.data[i] = this->data[i] + rhs.data[i];
				}



				return audioClip;
			}

			//cut operator
			Audio operator^ (std::pair<int,int> factor)
			{
				using namespace std;
				//create new Audio object
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize - (factor.second*sampleRate - factor.first*sampleRate);
				audioClip.numberSamples = this->numberSamples - (factor.second*sampleRate - factor.first*sampleRate);
				audioClip.data.resize(audioClip.numberSamples);
				int size = data.size();

				
				//loop through data
				for(int i = 0; i < factor.first*sampleRate; i++)
				{
					//change volume
					audioClip.data[i] = this->data[i];

				}

				int pos = factor.first*sampleRate;
				for(int i = factor.second*sampleRate; i < size; i++)
				{
					//change volume
					audioClip.data[pos] = this->data[i];
					pos++;
				}
				return audioClip;
			}

			//reverse audio
			Audio reverseClip ()
			{
				using namespace std;
				//create new Audio object
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize;
				audioClip.numberSamples = this->numberSamples;
				audioClip.data.resize(audioClip.numberSamples);
				audioClip.data = this->data;


				std::reverse(audioClip.data.begin(),audioClip.data.end());
				return audioClip;
			}





	};





	//partial template specialization for stereo sounds
	template <typename T> class Audio<T,2>
	{
		private:
		std::vector<std::pair<T,T> > data;
		int sampleRate;
		int sampleSize;
		int numChannels;
		int fileSize;
		int numberSamples;

		public:

			//constructor
			Audio(int sRate, int sSize)
			{
				sampleRate = sRate;
				sampleSize = sSize;
				numChannels = 2;
			}

			//destructor
			~Audio()
			{

			}

			//copy constructor
			Audio(const Audio & rhs) : sampleRate(rhs.sampleRate), sampleSize(rhs.sampleSize), numChannels(rhs.numChannels), fileSize(rhs.fileSize), numberSamples(rhs.numberSamples)
			{
				data = rhs.data;
			}
			//move constructor
			Audio(Audio && rhs) : sampleRate(rhs.sampleRate), sampleSize(rhs.sampleSize), numChannels(rhs.numChannels), fileSize(rhs.fileSize), numberSamples(rhs.numberSamples)
			{
				this->data = rhs.data;

				rhs.sampleRate = -1;
				rhs.sampleSize = -1;
				rhs.numChannels = -1;
				rhs.numberSamples = -1;
			}

			//copy assignment
			Audio operator=(const Audio & rhs)
			{
				sampleRate = rhs.sampleRate;
				sampleSize = rhs.sampleSize;
				numChannels = rhs.numChannels;
				fileSize = rhs.fileSize;
				numberSamples = rhs.numberSamples;
				data = rhs.data;
				return *this;
			}

			//move assignment
			Audio operator=(Audio && rhs)
			{
				sampleRate = rhs.sampleRate;
				sampleSize = rhs.sampleSize;
				numChannels = rhs.numChannels;
				fileSize = rhs.fileSize;
				numberSamples = rhs.numberSamples;
				data = rhs.data;

				rhs.sampleRate = -1;
				rhs.sampleSize = -1;
				rhs.numChannels = -1;
				rhs.fileSize = -1;
				rhs.numberSamples = -1;

				return *this;
			}

			//reads raw file and stores it into image object
			void load(std::string fileName)
			{
				using namespace std;
				ifstream input;
				//read a binary file
				input.open(fileName, ios::binary);
				if(input.is_open())
				{
					//get file size
					input.seekg(0,input.end);
					fileSize = (int)(input.tellg());
					input.seekg(0, input.beg);

					//size of vector
					numberSamples = fileSize/numChannels;

					//16bit
					if(sampleSize == 16)
					{
						numberSamples*=2;
					}

					data.resize(numberSamples);

					char * arr = new char[numberSamples*2];
					//read binary data block
					input.read(arr, numberSamples*2);
					int pos = 0;
					for(int i = 0; i < numberSamples; i++)
					{
						pair<T, T> p;
						p.first = arr[pos];
						pos++;
						p.second = arr[pos];
						pos++;
						data[i] = p;
					}
					delete arr;
					input.close();
				}

			}

			//save file
			void save(std::string outputName)
			{
				using namespace std;
				ofstream output(outputName, ios::binary);
				if(output.is_open())
				{
					char * arr = new char[numberSamples*2];
					int pos = 0;
					for(int i = 0; i < this->data.size(); i++)
					{
						//store pair values for left and right
						arr[pos] = this->data[i].first;
						pos++;
						arr[pos] = this->data[i].second;
						pos++;
					}

					if(sampleSize == 8)
					{
						output.write(arr, numberSamples*2);
					}

					else
					{
						output.write(arr, numberSamples);
					}

					delete arr;
					output.close();
				}
			}

			//overloaded operators
			//concatenate audio files
			Audio operator| (Audio & rhs)
			{

				using namespace std;
				//AudioClip -> new object. copy attributes
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize + rhs.fileSize;
				audioClip.numberSamples = this->numberSamples + rhs.numberSamples;


				audioClip.data.resize(audioClip.numberSamples);
				int size = this->data.size();
				int sizeRhs = rhs.data.size();

				//edit 16bit files
				if(sampleSize == 16)
				{
					size /= 2;
					sizeRhs /= 2;
				}

				//loop through this data
				for(int i = 0; i < size; i++)
				{
					//append this data
					audioClip.data[i] = this->data[i];
				}

				//loop through rhs data
				for(int i = size, k=0; k < sizeRhs; i++,k++)
				{
					//append rhs data
					audioClip.data[i] = rhs.data[k];
				}

				return audioClip;
			}


			//Volume factor
			Audio operator* (std::pair<float,float> factor)
			{
				using namespace std;
				//create new Audio object
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize;
				audioClip.numberSamples = this->numberSamples;
				audioClip.data.resize(audioClip.numberSamples);
				int size = audioClip.data.size();

				//loop through data
				for(int i = 0; i < size; i++)
				{
					//change volume
					//left audio
					audioClip.data[i].first = this->data[i].first * factor.first;
					//right audio
					audioClip.data[i].second = this->data[i].second * factor.second;
				}
				return audioClip;
			}


			Audio operator+ (Audio & rhs)
			{
				using namespace std;
				//AudioClip -> new object. copy attributes
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize + rhs.fileSize;
				audioClip.numberSamples = this->numberSamples;
				audioClip.data.resize(audioClip.numberSamples);

				//size of vector. loop by size
				int size = this->data.size();

				//loop through this data
				for(int i = 0; i < size; i++)
				{
					//append this data
					audioClip.data[i].first = this->data[i].first + rhs.data[i].first;
					audioClip.data[i].second = this->data[i].second + rhs.data[i].second;
				}



				return audioClip;
			}

			//cut operator
			Audio operator^ (std::pair<int,int> factor)
			{
				using namespace std;
				//create new Audio object
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize - (factor.second*sampleRate - factor.first*sampleRate);
				audioClip.numberSamples = this->numberSamples - (factor.second*sampleRate - factor.first*sampleRate);
				audioClip.data.resize(audioClip.numberSamples);
				int size = data.size();

				//loop through data
				for(int i = 0; i < factor.first*sampleRate; i++)
				{
					//change volume
					audioClip.data[i] = this->data[i];

				}

				int pos = factor.first*sampleRate;
				for(int i = factor.second*sampleRate; i < size; i++)
				{
					//change volume
					audioClip.data[pos] = this->data[i];
					pos++;
				}
				return audioClip;
			}

			//reverse audio
			Audio reverseClip ()
			{
				using namespace std;
				//create new Audio object
				Audio audioClip(this->sampleRate, this->sampleSize);
				audioClip.fileSize = this->fileSize;
				audioClip.numberSamples = this->numberSamples;
				audioClip.data.resize(audioClip.numberSamples);
				audioClip.data = this->data;


				std::reverse(audioClip.data.begin(),audioClip.data.end());
				return audioClip;
			}






	};
}




#endif /* AUDIO_H_ */
