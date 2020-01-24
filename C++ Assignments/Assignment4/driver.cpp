#include <iostream>
#include <sstream>
#include "image.h"

using namespace std;

int main(int argc, char *argv[])
{
    //strings representing command line input
    string option;
    string imageName1;
    string imageName2;
    string outputName;

    //convert chars to strings
    stringstream ss;
    ss << argv[1];
    ss >> option;
    cout << option <<endl;
    ss.clear();

    ss << argv[2];
    ss >> imageName1;
    ss.clear();

	//add method
    if(option == "-a")
    {

    	//read image 2 name
    	ss << argv[3];
    	ss >> imageName2;
    	ss.clear();

    	//output name
    	ss << argv[4];
		ss >> outputName;
		ss.clear();

    	//load image 1
		RHLDEE001::Image image1;
		image1.load(imageName1);


    	//load image 2
    	RHLDEE001::Image image2;
    	image2.load(imageName2);

    	//add image 1 and 2 together
    	RHLDEE001::Image image3 = image1 + image2;
    	image3.save(outputName);
    }

    else if(option == "-s")
    {

		//read image 2 name
		ss << argv[3];
		ss >> imageName2;
		ss.clear();

		//output name
		ss << argv[4];
		ss >> outputName;
		ss.clear();

		//load image 1
		RHLDEE001::Image image1;
		image1.load(imageName1);


		//load image 2
		RHLDEE001::Image image2;
		image2.load(imageName2);

		//subtract image 1 and 2 together
		RHLDEE001::Image image3 = image1 - image2;
		image3.save(outputName);
    }

    //inverse image
    else if(option == "-i")
	{
    	//output name
		ss << argv[3];
		ss >> outputName;
		ss.clear();

		//load image 1
		RHLDEE001::Image image1;
		image1.load(imageName1);

		RHLDEE001::Image image2 = !image1;
		image2.save(outputName);


	}

    //mask image
    else if(option == "-l")
	{
    	//read image 2 name
		ss << argv[3];
		ss >> imageName2;
		ss.clear();

		//output name
		ss << argv[4];
		ss >> outputName;
		ss.clear();

		//load image 1
		RHLDEE001::Image image1;
		image1.load(imageName1);


		//load image 2
		RHLDEE001::Image image2;
		image2.load(imageName2);

		RHLDEE001::Image image3 = image1/image2;
		image3.save(outputName);
	}

    //image threshold
    else if(option == "-t")
	{
    	//threshold
    	int threshold;
		ss << argv[3];
		ss >> threshold;
		ss.clear();

    	//output name
		ss << argv[4];
		ss >> outputName;
		ss.clear();

		//load image 1
		RHLDEE001::Image image1;
		image1.load(imageName1);

		RHLDEE001::Image image3 = (image1 * threshold);
		image3.save(outputName);
		cout << "done";
	}

    else
    {
    	cout << "Error: Option not valid";
    }



}

