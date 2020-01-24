/*
 * cheapsocket.h
 * Author: simon
 */

#ifndef CHEAPSOCKET_H_
#define CHEAPSOCKET_H_

#include <iostream>
#include <string>
#include <set>

namespace cheapsocket {

std::set<int> available_sockets = { 53, 29, 12, 5, 37 };
std::set<int> leased_sockets;

int get_socket(void)
{
	if(available_sockets.empty())
	{
		std::cout << "NO MORE HANDLES! " << std::endl;
		throw std::exception();
	}

	int socket = *available_sockets.begin();
	leased_sockets.insert(socket);
	available_sockets.erase(socket);
	std::cout << "Leasing socket " << socket << std::endl;
	return socket;
}
void write_to_socket(int socket, std::string s)
{
	if(leased_sockets.count(socket) == 0)
	{
		std::cout << "Write to invalid socket " << socket << std::endl;
		throw std::exception();
	}
	std::cout << "Wrote: " << s << " on socket " << socket << std::endl;
}

std::string read_from_socket(int socket)
{
	if(leased_sockets.count(socket) == 0)
	{
		std::cout << "Read from invalid socket " << socket << std::endl;
		throw std::exception();
	}

	std::cout << "Read data" << " on socket " << socket << std::endl; return "data";
}

void release_socket(int socket)
{
	if(leased_sockets.count(socket) == 0)
	{
		std::cout << "Try to release an invalid socket " << socket << std::endl;
		throw std::exception();
	};

	leased_sockets.erase(socket);
	available_sockets.insert(socket);

	std::cout << "Re-obtained socket " << socket << std::endl;
}

}

#endif /* CHEAPSOCKET_H_ */
