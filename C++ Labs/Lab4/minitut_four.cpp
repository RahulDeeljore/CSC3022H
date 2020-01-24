/*
 * minitut4.cpp
 * Author: simon
 */

#include <iostream>
#include <string>
#include <set>

#include "cheapsocket.h"
#include "noisy.h"

// g++ minitut_four.cpp -o minitut_four -std=c++11

// Take a look at PART ONE, where a cheapsocket library is used (see cheapsocket.h).
// * A socket is acquired using the get_socket() method
// * The socket is written to, and read from by the write_to_socket and read_from_socket methods
// * Once finished. the socket is released. by the release_socket method.
// The number of sockets is limited and our programmer hasn't released the sockets!
// Create a class that manages sockets automatically.
// * Implement the six special member functions, except for the
//   copy constructor and copy assigment operator. They should be deleted.
//   It doesn't make sense to create a copy of a socket handle in this case.
// * Implement write/read methods that delegate to the cheapsocket methods.
// You can define all the methods within the raii_socket
// class declaration above the main method.

// Resources: week5/lecture 9 & week6/r_value_example.cpp & the wand/student class here: http://ideone.com/N5iJkl
// for further insight into the special member functions and where they occur

// Take a look at PART TWO
// Examine the output to see the extent of object creation, copying and destruction.
// Make the arguments of addrats and addtorat references and note
// the creation + destruction changes.
// addtorat could return a reference to the lhs argument.
// Change this and note the creation + destruction changes.



// Adds two noisy rational numbers together, creating
// a new object
noisyrat addrats(noisyrat & lhs, noisyrat & rhs) // Changed to references to avoid deep copying
{
	std::cout << "addrats()" << std::endl;
	return noisyrat(
		lhs.get_n()*rhs.get_d() + rhs.get_n()*lhs.get_d(),
		lhs.get_d()*rhs.get_d());
}

// Adds the value of rhs to that of lhs and returns lhs
noisyrat & addtorat(noisyrat & lhs, noisyrat & rhs)
{
	std::cout << "addtorats()" << std::endl;
	lhs.set_n(lhs.get_n()*rhs.get_d() + rhs.get_n()*lhs.get_d()) ;
	lhs.set_d(lhs.get_d()*rhs.get_d());
	return lhs;
}

// Implement the six special member functions here.
class raii_socket {
	public:
		
		int socket = -1;

		//constructor
		raii_socket () {
			socket = cheapsocket::get_socket();
		}

		// Destructor
		~raii_socket () {

			if (socket != -1) cheapsocket::release_socket(socket);
			socket = -1;
		}

		// Move constructor
		raii_socket (raii_socket && other) : socket(other.socket) {
			other.socket = -1; // socket other is taken
		}

		
		raii_socket & operator = (raii_socket && other) {
			if (this != &other) // same socket check
                                 {

				if (socket != -1) cheapsocket::release_socket(socket);

				// take resource
				socket = other.socket;
				other.socket = -1;
			}
			// Return reference to curent object
			return *this;
		}

		
		void write (std::string input) {
			cheapsocket::write_to_socket(socket, input);
		}

		
		std::string read (void) {
			return cheapsocket::read_from_socket(socket);
		}
		
};


int main(void)
{
	std::cout << "PART ONE:" << std::endl;
	for(int i=0; i<10;++i)
	{
		int socket = cheapsocket::get_socket();
		cheapsocket::write_to_socket(socket, "Hello World!");
		std::string s = cheapsocket::read_from_socket(socket);
		cheapsocket::release_socket(socket); // Uncommented since this leads to sockets running out of handles
	}

	{
		raii_socket socket;
		socket.write("Hello World");
		std::string s1 = socket.read();

		// raii_socket copy = socket; // This should fail
		// confirmed: this does not compile since copy assignmet operator deleted
		raii_socket new_socket = std::move(socket); // This should succeed.
		new_socket.write("Hello World");
		std::string s2 = new_socket.read();
	}

	std::cout << "PART TWO:" << std::endl;
	{
		noisyrat n1(2,3);
		noisyrat n2(4,5);
		noisyrat n3(5,6);
		n3 = addrats(n1,n2);
		std::cout << "n3=" << n3 << std::endl;
		std::cout.flush();
	}

	{
		noisyrat n1(2,3);
		noisyrat n2(4,5);
		addtorat(n1,n2);
		std::cout << "n1=" << n1 << std::endl;
		std::cout.flush();
	}
}
