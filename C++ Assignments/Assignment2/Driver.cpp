#include "Volimage.h"

#include <iostream>
#include <iostream>
#include <sstream>
#include <string>


using namespace std;

int main(int argc, char* argv[]) {

VolImage v;

if(argc < 3)
	{
		string fileName = (string)(argv[1]);
		v.readImages(fileName);
		int Size = v.volImageSize();
               
		cout << "Number of bytes required: " << Size << endl;
	}


	else
	{
		string fileName = (string)(argv[1]);
		v.readImages(fileName);
		string option = (string)argv[2];

		//diffmap
		if(option == "-d")
		{
			int i1;
			int i2; // convert to int

			istringstream(argv[3]) >> i1; // assign value to int
			istringstream(argv[4]) >> i2; 

			string prefix = (string)argv[5]; // output file name
			v.diffmap(i1, i2, prefix);
		}

		//extract method
		else if(option == "-x")
		{
			int i;
			istringstream(argv[3]) >> i; // convert to int
			string prefix = (string)argv[4]; //convert to string
			v.extract(i, prefix);
		}

		//Extra method
		else if(option == "-g")
		{
			int i;
			istringstream(argv[3]) >> i; //convert to int
			v.extraCredit(i); //no output file , default file assigned
		}


		//Input not accepted
		else
		{
			cout << "Input Incorrect" << endl;
		}

	}





	return 0;

return 0;}
