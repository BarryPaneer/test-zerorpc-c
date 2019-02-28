#include "rpc.h"
#include <string>
#include <iostream>


RpcClient::RpcClient( const char* endpoint
		, void* context_ptr )
 : m_context_ptr( context_ptr )
 , m_socket_ptr( NULL ), m_server_addr( endpoint )
{
	if( NULL == context_ptr ) {
		m_context_ptr = ::zmq_ctx_new();
	} else {
		m_context_ptr = context_ptr;
	}

	m_socket_ptr = ::zmq_socket( m_context_ptr, ZMQ_XREQ );
	if( m_socket_ptr ) {
		int	val = 10;
		if( 0 != ::zmq_setsockopt( m_socket_ptr, ZMQ_LINGER, &val, sizeof val )) {
			std::cout << "get an error in zmq_setsockopt()..." << std::endl;
		}
	}
}

int RpcClient::invoke( const char* data_ptr, unsigned int size )
{
	return ::zmq_send( m_socket_ptr, data_ptr, size, 0 );
}

int RpcClient::receive( char* buf_ptr, unsigned int size ) {
	return ::zmq_recv( m_socket_ptr, buf_ptr, size, 0 );
}

void RpcClient::disconnect()
{
	if( m_socket_ptr ) {
		::zmq_close( m_socket_ptr );
	}

	if( m_context_ptr ) {
		::zmq_ctx_destroy( m_context_ptr );
	}
}

int RpcClient::connect2server()
{
	if( NULL == m_socket_ptr || NULL == m_context_ptr ) {
		std::cout << "invalid handle..." << std::endl;
		return -1024;
	}

	return ::zmq_connect( m_socket_ptr, m_server_addr.c_str() );
}

