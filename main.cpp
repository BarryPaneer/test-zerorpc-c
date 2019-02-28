#include <stdio.h>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include <time.h>
#include "rpc.h"


int main( int argc, char** argv )
{
	if( argc < 3 ) {
		std::cout << "not enough arguments" << std::endl;
		return -1;
	}

	int	major = 0;
	int	minor = 0;
	int	patch = 0;

	::zmq_version( &major, &minor, &patch );
	::printf ("zeromq version is %d.%d.%d\n", major, minor, patch);

	///////////////////////////////////////////////////////////////
	std::cout << "begin................\n" << std::endl;

	unsigned long   		msg_id = 0;	///< should be a uuid
	unsigned int			body_size = 0;
	std::map<std::string,int>	head;
	std::vector<int>		args;
	unsigned int			listing_id = ::atoi( argv[1] );
	unsigned int			customer_id = ::atoi( argv[2] );
	RpcClient			rpc_cli( "tcp://192.168.168.33:8084" );
	std::stringstream		command_listing;
	std::stringstream		command_customer;

	if( customer_id == 23764 ) {
		msg_id = 99999;
	}

	head["v"] = 3;
	args.push_back( 0 );
	std::cout << "listing id :" << listing_id << ", customer id :" << customer_id << std::endl;
	if( 0 != rpc_cli.connect2server() ) {
		std::cout << "cannot connect 2 server" << std::endl;
		return -1024;
	}

	while( true ) {
		///< 1) get_main_customer_properties() /////////
		command_customer.clear();
		head["message_id"] = msg_id++;
		args[0] = customer_id;

		msgpack::type::tuple<std::map<std::string,int>, std::string, std::vector<int> > args_customer_1( head, "get_main_customer_properties", args );
		msgpack::pack( command_customer, args_customer_1 );
		command_customer.seekp( 0, std::ios::end );
		body_size = command_customer.tellp();

		int error = rpc_cli.invoke( command_customer.str().c_str(), body_size );
		if( 0 >= error ) {
			std::cout << "1) failed 2 invoke get_main_customer_properties, size = " << body_size << ", errorcode = " << error << std::endl;
		}

		char    buffer_1[1024*20] = { 0 };

		error = rpc_cli.receive( buffer_1, sizeof(buffer_1) );
		error = rpc_cli.receive( buffer_1, sizeof(buffer_1) );
		std::cout << buffer_1 << std::endl;
		std::cout << "1) get_main_customer_properties() " << error << std::endl;

		///< 2) get_main_customer_properties() //////////
		command_customer.clear();
		head["message_id"] = msg_id++;
		args[0] = customer_id;

		msgpack::type::tuple<std::map<std::string,int>, std::string, std::vector<int> > args_customer_2( head, "get_main_customer_properties", args );
		msgpack::pack( command_customer, args_customer_2 );
		command_customer.seekp( 0, std::ios::end );
		body_size = command_customer.tellp();

		error = rpc_cli.invoke( command_customer.str().c_str(), body_size );
		if( 0 >= error ) {
			std::cout << "2) failed 2 invoke get_main_customer_properties, size = " << body_size << ", errorcode = " << error << std::endl;
		}

		char    buffer_2[1024*20] = { 0 };

		error = rpc_cli.receive( buffer_2, sizeof(buffer_2) );
		error = rpc_cli.receive( buffer_2, sizeof(buffer_2) );
		std::cout << buffer_2 << std::endl;
		std::cout << "2) get_main_customer_properties() " << error << std::endl;

		///< 3) get_property() //////////////////////////
		command_listing.clear();
		head["message_id"] = msg_id++;
		args[0] = listing_id;

		msgpack::type::tuple<std::map<std::string,int>, std::string, std::vector<int> > args_listing( head, "get_property", args );
		msgpack::pack( command_listing, args_listing );
		command_listing.seekp( 0, std::ios::end );
		body_size = command_listing.tellp();

		error = rpc_cli.invoke( command_listing.str().c_str(), body_size );
		if( 0 >= error ) {
			std::cout << "failed 2 invoke get_property, size = " << body_size << ", errorcode = " << error << std::endl;
		}

		char	buffer_property[1024*10] = { 0 };

		error = rpc_cli.receive( buffer_property, sizeof(buffer_property) );
		error = rpc_cli.receive( buffer_property, sizeof(buffer_property) );
		std::cout << buffer_property << std::endl;
		std::cout << "3) get_property() ===> " << error << std::endl;

		//break;
	}

	rpc_cli.disconnect();
	std::cout << "end.................\n" << std::endl;

	return 0;
}

