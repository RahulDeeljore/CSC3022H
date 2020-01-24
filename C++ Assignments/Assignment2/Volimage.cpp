#include "Volimage.h"
#include <iostream>
#include <fstream>

using namespace std;

// constructor
VolImage::VolImage() {
	width, height = 0;
}

// destructor
VolImage::~VolImage() {
	for (int i = 0; i < 123; i ++) {
		for (int row = 0; row < height; row++) {
			delete [] slices[i][row];
		}
		delete [] slices[i];
	}
	slices.clear();
}	


bool VolImage::readImages(std::string baseName) {
	int number_of_slices;

	// Checking if header file exists
         // Opens if it exists
	ifstream headerFIle;
	headerFIle.open("./brain_mri_raws/MRI.data");
	if (!headerFIle) {
	    cerr << "MRI.data has not been found \n";
	    exit(1); 
	} else {
                // read values of header file accordingly
		headerFIle >> width;
		headerFIle >> height;
		headerFIle >> number_of_slices;
            }
	headerFIle.close();

	
	for (int i = 0; i < number_of_slices; i++) {
		string iStr = to_string(i);

		ifstream sliceFile;
		sliceFile.open("./brain_mri_raws/"+baseName+iStr+".raw", std::ios_base::binary); //opening .raw files
		if (!sliceFile) {
	    cerr << "File " <<  baseName+iStr+".raw" << "does not exist.\n"; // if .raw pic does not exist

	    exit(1); 
		} else if (sliceFile.is_open()) {
			
			// read the files into the  vector slices
			unsigned char x;
			unsigned char** slice = new unsigned char*[height];
				for (int i=0; i<height; i++) {
					slice[i] = new unsigned char [width];
					for (int j=0; j<width; j++) {
						x = sliceFile.get();
						slice[i][j] = x;
					}
				}
				slices.push_back (slice);

		}
		sliceFile.close();
	}
	std::cout << "Stack has been populated. Files read successfully." << std::endl;
}

void VolImage::diffmap(int sliceI, int sliceJ, std::string prefix) {

	ofstream output;
		string filename = prefix + ".raw"; //file name
		output.open(filename.c_str(),ios::binary); //write to binary file

		//loop through each row
		for(int r = 0; r < height; r++)
		{
			unsigned char* tempRow = new unsigned char[width];
			// loop through row
			for(int c = 0; c < width; c++)
			{
				tempRow[c] = (unsigned char)(abs((float)slices[sliceI][r][c] - (float)slices[sliceJ][r][c])/2);

			}
			output.write((char*)tempRow,width); //write row to file
		}
		output.close();
		cout << "diffmap method completed" << endl;
}

void VolImage::extract(int sliceId, std::string prefix) {
		using namespace std;
		// open binary file to write
		string filename = prefix + ".raw";
		ofstream output;
		output.open(filename.c_str(),ios::binary); 

		for(int h = 0; h < height; h++)
		{
			
			output.write((char*)slices[sliceId][h],width); // write each row to file
		}

		output.close(); 

		// write header file
		filename = prefix + ".data";
		output.open(filename.c_str());
		output << width << " " << height << " " << 1 << endl;
		output.close();
		cout << "Extract method completed" << endl;

}
int VolImage::volImageSize(void) {

         int SlicesSize = slices.size();
                cout << "Number of images: " << SlicesSize << endl;
        int x = sizeof(char*);
	int total = (height * width * SlicesSize) + (height * x);// size of images plus pointers
	
	return total;
	}



void VolImage::extraCredit(int slice){
	ofstream outFile ("ExtraCredit.raw", ios::binary); //binary file to store 
	for (int i = 0 ; i < slices.size(); i++){
		for (int j = 0; j < width; j++){
			outFile.write((char*) &slices[i][slice][j], 1); // write to file
		}
	}
	outFile.close();
cout << "Extra method completed" << endl;

}



