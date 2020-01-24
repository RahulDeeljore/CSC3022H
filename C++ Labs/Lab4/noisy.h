#ifndef _NOISY_H
#define _NOISY_H

#include <iostream>
#include <string>

// Class that makes noise upon construction,
// deep copy and destruction
class noisy
{
public:
	// Constructor
	noisy(const std::string & description=get_d()) : _d(description), pokee(0)
		{ std::cout << "Constructing " << _d << std::endl; }
	// Copy constructor. Don't actually copy anything tho.
	noisy(const noisy & rhs) : _d(get_d()), pokee(0)
	{
		std::cout << "Constructing " << _d
			<< " with a ***DEEP COPY*** of " << rhs._d
			<< std::endl;
	}
	// operator=. Assignment. Don't actually copy anything tho...
	noisy & operator=(const noisy & rhs)
	{
		std::cout << "***DEEP COPYING*** " << rhs._d
			<< " to " << _d
			<< std::endl;
		return *this;
	}
	// Destructor
	~noisy(void)
		{ std::cout << "Destroying " << _d << std::endl; }

	void poke(void)
		{ ++pokee; }

	int get_pokes(void)
		{ return pokee; }

	// For return by reference
	const std::string & get_description(void)
		{ return _d; }

private:
	// Static function for creating some kind of random description
	static std::string get_d(void)
	{
		char array[5] = { 'A', 'A', 'A', 'A', 'A' };
		unsigned int work = id;

		// Just add the id's digits to the char value
		for(int i=0; i<5; ++i)
			{ array[i] += int(work % 10); work /= 10; }

		++id; // Bump the static id variable
		return std::string(array, array+5);
	}

	// String to hold the description
	std::string _d;
	int pokee;
	static unsigned int id;
};

unsigned int noisy::id = 0;

// Forward declaration of noisyrat
class noisyrat;


// Actual declaration of noisyrat
class noisyrat
{
public:

	friend std::ostream & operator<<(std::ostream & out, const noisyrat & n);
	
	// Constructor
	noisyrat(int num=0, int den=0) : n(num), d(den)
		{ std::cout << "Constructing " << *this << std::endl; }
	// Copy Constructor
	noisyrat(const noisyrat & rhs) : n(rhs.n), d(rhs.d)
	{
		std::cout << "Constructing new " << *this
			<< " with a ***DEEP COPY*** of "
			<< rhs << std::endl;
	}
	noisyrat & operator=(const noisyrat & rhs)
	{
		if(this != &rhs)
		{
			std::cout << "***DEEP COPYING*** " << rhs
			<< " over " << *this
			<< std::endl;

			n = rhs.n; d = rhs.d;
		}
		return *this;
	}

	~noisyrat(void)
	{
		std::cout << "Destroying " << *this << std::endl;
	}


	void set_n(int num) { n = num; }
	void set_d(int num) { d = num; }
	int get_n(void) const { return n; }
	int get_d(void) const { return d; }

private:
	//std::ostream & operator<<(std::ostream & out, const noisyrat & n);

	int n, d;
};

// Overload the << operator for noisyrat
std::ostream & operator<<(std::ostream & out, const noisyrat & n)
	{ out << n.n << '/' << n.d; return out; }


#endif
