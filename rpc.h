#ifndef __TEST_RPC_H__
#define __TEST_RPC_H__


#include <zmq.h>
#include <string>
#include <msgpack.hpp>


class RpcClient
{
public:
	RpcClient( const char* endpoint
		, void* context_ptr = NULL );

	int			connect2server();

	void			disconnect();

	int			invoke( const char* data_ptr, unsigned int size );

	int			receive( char* buf_ptr, unsigned int size );

private:
	void*			m_socket_ptr;
	void*			m_context_ptr;
	std::string		m_server_addr;
};


#endif

