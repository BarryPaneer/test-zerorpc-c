#include <zmq.h>
#include <stdio.h>
#include <string>
#include <iostream>


int main( int argc, char** argv )
{
	if( argc < 4 ) {
		std::cout << "not enough arguments" << std::endl;
		return -1;
	}

	int major, minor, patch;

	::zmq_version( &major, &minor, &patch );
	::printf ("zeromq version is %d.%d.%d\n", major, minor, patch);
	std::cout << "begin................\n" << std::endl;


	std::cout << "end.................\n" << std::endl;

	return 0;
}




