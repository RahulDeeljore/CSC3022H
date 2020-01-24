#include "image.h"
#include <fstream>
#include <iostream>
#include <sstream>


namespace RHLDEE001
{
    using namespace std;

    //constructor
    Image::Image()
    {
        width = 0;
        height = 0;

    }

    //destructor
    Image::~Image()
	{
		width = -1;
		height = -1;
		data.reset(nullptr);

	}

    //copy constructer
    Image::Image(Image &rhs)
    {
    	this->width = rhs.width;
    	this->height = rhs.height;
    	this->data.reset(new unsigned char [width*height]);
    	Image::iterator beg1 = this->begin();
    	Image::iterator end1 = this->end();
    	Image::iterator beg2 = rhs.begin();

    	while(beg1 != end1)
    	{
    		*beg1 = *beg2;
    		beg1++;
    		beg2++;
    	}
    }

	//move constructer
	Image::Image(Image && rhs)
	{
		this->width = rhs.width;
		this->height = rhs.height;
		this->data.reset(new unsigned char [width*height]);
		this->data = std::move(rhs.data);
		rhs.width = -1;
		rhs.height = -1;

	}

	//copy assignment
	Image& Image::operator=(Image & rhs)
	{
		if(this != &rhs)
		{
			this->width = rhs.width;
			this->height = rhs.height;
			this->data.reset(new unsigned char [width*height]);
			Image::iterator beg1 = this->begin();
			Image::iterator end1 = this->end();
			Image::iterator beg2 = rhs.begin();

			while(beg1 != end1)
			{
				*beg1 = *beg2;
				beg1++;
				beg2++;
			}
		}

		return *this;
	}

	//move assignment
	Image & Image::operator=(Image && rhs)
	{
		if(this != &rhs)
		{
			this->width = rhs.width;
			this->height = rhs.height;
			this->data.reset(new unsigned char [width*height]);
			//move method takes data out of rhs and into this.
			this->data = std::move(rhs.data);
			//reset width and height
			rhs.width = -1;
			rhs.height = -1;
		}

		return *this;
	}




//
    //Operators overloaded
	//operator +
    Image Image::operator+ (Image & rhs)
    {
		Image output = rhs; //give it values before overwriting data
		Image::iterator beg1 = this->begin();
		Image::iterator end1 = this->end();

		Image::iterator beg2 = rhs.begin();

		Image::iterator beg3 = output.begin();
		//make sure images have the same dimensions
		if(this->width == rhs.width && this->height == rhs.height)
		{
			while(beg1 != end1)
			{
				int temp = *beg1 + *beg2;
				if(temp > 255)
				{
					temp = 255;
				}
				*beg3 = (unsigned char)temp;

				//increment positions
				beg1++;
				beg2++;
				beg3++;
			}
        }
        return output;
    }

    //operator -
    Image Image::operator- (Image & rhs)
    {
    	Image output = rhs;
		Image::iterator beg1 = this->begin();
		Image::iterator end1 = this->end();

		Image::iterator beg2 = rhs.begin();

		Image::iterator beg3 = output.begin();
		if(this->width == rhs.width && this->height == rhs.height)
		{
			while(beg1 != end1)
			{
				int temp = *beg1 - *beg2;
				if(temp < 0)
				{
					temp = 0;
				}
				*beg3 = (unsigned char)temp;

				//advances position
				beg1++;
				beg2++;
				beg3++;
			}
		}
		return output;
    }

    //inverse image operator
    Image Image::operator! ()
    {
    	Image::iterator beg = this->begin();
    	Image::iterator end = this->end();
    	while(beg != end)
		{
			//inverse unsigned char
    		*beg = 255 - *beg;

			if(*beg < 0)
			{
				*beg = 0;
			}

			//advances position
			beg++;
		}
    	return *this;
    }

    //mask image
    Image Image::operator/ (Image & rhs)
    {
    	Image output = rhs;
		Image::iterator beg1 = this->begin();
		Image::iterator end1 = this->end();

		Image::iterator beg2 = rhs.begin();

		Image::iterator beg3 = output.begin();
		if(this->width == rhs.width && this->height == rhs.height)
		{
			while(beg1 != end1)
			{
				int temp;
				if(*beg2 == 255)
				{
					temp = *beg1;
				}

				else
				{
					temp = 0;
				}

				*beg3 = (unsigned char)temp;

				//increment positions
				beg1++;
				beg2++;
				beg3++;
			}
		}
		return output;
}
//threshold operator
    Image Image::operator* (int f)
    {
    	Image output = *this;
		Image::iterator beg1 = this->begin();
		Image::iterator end1 = this->end();

		Image::iterator beg2 = output.begin();

		while(beg1 != end1)
		{
			unsigned char temp;
			if(*beg1 > f)
			{
				temp = 255;
			}

			else
			{
				temp = 0;
			}

			*beg2 = temp;

			beg1++;
			beg2++;
		}

		return output;
    }

    //reads pgm file and stores it into image object
    void Image::load(string fileName)
    {

    	ifstream input;
    	//read a binary file
    	input.open(fileName, ios::binary);
    	if(input.is_open())
    	{
    		string line;
    		while(getline(input, line))
    		{
    			if(line != "P5" || line.substr(0) != "#")
    			{
    					if(line == "255")
    					{
    						break;
    					}

    					else
    					{
    						stringstream ss;
    						ss << line;

    						string w;
    						string h;
    						ss >> w >> ws >> h;
    						int width1;
    						int height1;
    						//convert string to int
    						istringstream bufferW(w);
    						bufferW >> width1;
    						//convert string to int
    						istringstream bufferH(h);
    						bufferH >> height1;
    						//set the width and height
    						this->width = width1;
    						this->height = height1;

    					}
    			}
    		}

    		//reset data
    		this->data.reset(new unsigned char [width * height]);
    		char *arr = new char [width * height];
    		//read binary data block
    		input.read(arr, width*height);
    		this->data.reset((unsigned char*)arr);
    		input.close();

    	}




    }

    //saves image to a file
    void Image::save(string outputName)
    {
    	ofstream output(outputName, ios::binary);
    	if(output.is_open())
    	{
    		output << "P5\n";
    		output << width << " " << height;
    		output << "\n255\n";
    		char *arr = new char [width * height];
    		arr = reinterpret_cast<char*>(data.get());
    		output.write(arr, width * height);

    		output.close();
    	}


    }


}
