#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

// Standard Template Library Recap Tutorial

// (1) Write a generic function, how_many, templated
//     on two types
//        - Iterator
//        - Predicate (Functor returning a boolean)
//     and taking three arguments by value:
//        - Iterator first
//        - Iterator last
//        - Predicate pred
//     and returning an integer containing the number of
//     times the predicate returned true for values in
//     the iterator range.

struct is_a {
	bool operator () (const char& n) const { return n == 'a'; }
	typedef int argument_type;
};

template <class InputIterator, class UnaryPredicate> 
int how_many (InputIterator first, InputIterator last, UnaryPredicate pred) {
	int ret = 0;
	while (first!=last) {
		if (pred(*first)) ++ret;
		++first;
	} return ret;
}


int main(int argc, char * argv[])
{
	std::string tartuffery = "The rain in spain falls mainly on the plain";

	std::size_t a_count = 0;

	// (2) Use how_many to count how many a's
	//     are in the tartuffery string. You'll have to
	//     construct a predicate to do this. Use a functor
	//     or a lambda, choosing the one you're most
	//     uncomfortable with.  For those interested in lambda expressions, you should read through the following:
	//  a) Section 8.5.2 on Page 114 in the cppnotes8.pdf
	//  b) https://blog.smartbear.com/c-plus-plus/c11-tutorial-lambda-expressions-the-nuts-and-bolts-of-functional-programming/
	//  c) Lecture slides cpp-18.pdf

	a_count = how_many(tartuffery.begin(), tartuffery.end(), is_a());

	std::cout << a_count << " a characters in \"" << tartuffery << "\"" << std::endl;


	std::string result;

	// (3) Use the copy_if algorithm to copy all characters
	//     in the tartuffery string not equal to 'a'. Since
	//     we're not really going to be sure what the size of
	//     the result string is going to be, it may be best to
	//     use a back_inserter on the output iterator range.
	//     http://www.cplusplus.com/reference/algorithm/copy_if

	auto it = std::copy_if(tartuffery.begin(), tartuffery.end(), back_inserter(result), std::not1(is_a()));

	std::cout << "\"" << tartuffery << "\" without a's looks like \""
		<< result << "\"" << std::endl;

}
