/*****************************************************************
* Header file for the brain dead C++ factorial library
* Author: Benjamin Hugo
* Date: 2015
******************************************************************/

#include <stdexcept>
extern "C" {
	/**
	* This is a brain-dead recursive implementation of factorial
	* If you value your life don't try and run this with large numbers. It will be as slow as hell.
	* Note: 0! := 1
	* Arguement: a small positive integer
	* Throws: invalid_argument when a negative integer is passed in
	*/
	long long factorial(long long arg);
}
