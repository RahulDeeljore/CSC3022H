/*****************************************************************
* Implementation file for the brain dead C++ factorial library
* Author: Benjamin Hugo
* Date: 2015
******************************************************************/

#include "factorial.h"
extern "C" {
	long long factorial(long long arg){
		using namespace std; //note: never use "using namespace" outside of a scope in a header file. We will penalize you for that!
		if (arg < 0)
			throw invalid_argument("Cannot take the factorial of a negative number");
		else if (arg == 0)
			return 1;
		else return (arg * factorial(arg - 1));
	}
}
