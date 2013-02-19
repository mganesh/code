/*
 *  Socket.cpp
 *  CacheServer
 *
 *  Created by Ganesh M on 2/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include "Socket.h"
#include <iostream>
#include <errno.h>
#include <netinet/tcp.h>
using namespace CacheServer;

Socket::Socket(int family, int stream, int type)
: sockfd_(-1)
{
	sockfd_ = socket(family, stream, type);
	if (sockfd_ < 0)
	{
		// raise exception
	}
}

Socket::~Socket()
{
	close();
}

void Socket::bindAddress(const InetAddress& addr)
{
	int ret = ::bind(sockfd_, (struct sockaddr*)&addr, sizeof addr);
	if (ret < 0)
	{
		// TODO
		std::cerr << "bind failed !!" << std::endl;
		return;
	}
}

void Socket::listen(int backlog)
{
	int ret = ::listen(sockfd_, backlog);
	if (ret < 0)
	{
		// TODO
		std::cerr << "Listen failed !!" << std::endl;
		return;
	}
}

int Socket::accept(InetAddress* addr)
{
	socklen_t len = sizeof *addr;
	int connfd = ::accept(sockfd_, (struct sockaddr*)&addr, &len);
	if (connfd < 0)
	{
		int savedErrno = errno;
		switch (savedErrno)
		{   
			case EAGAIN:
			case ECONNABORTED:
			case EINTR:
			case EPROTO: // ???
			case EPERM:
			case EMFILE: // per-process lmit of open file desctiptor ???
				// expected errors
				errno = savedErrno;
				break;
			case EBADF:
			case EFAULT:
			case EINVAL:
			case ENFILE:
			case ENOBUFS:
			case ENOMEM:
			case ENOTSOCK:
			case EOPNOTSUPP:
				// unexpected errors
				std::cerr << "unexpected error of ::accept " << savedErrno << std::endl;
				break;
			default:
				std::cerr << "unknown error of ::accept " << savedErrno << std::endl;
				break;
		}   
	}
	else {
		std::cout << "Socket::accept() - Success" << std::endl;
	}

	return connfd;
}

void Socket::close()
{
	if (sockfd_)
		::close(sockfd_);
}

void Socket::setTcpNoDelay(bool on) 
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, IPPROTO_TCP, TCP_NODELAY,
				 &optval, sizeof optval);
	// FIXME CHECK
}

void Socket::setReuseAddr(bool on) 
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR,
				 &optval, sizeof optval);
	// FIXME CHECK
}

void Socket::setKeepAlive(bool on) 
{
	int optval = on ? 1 : 0;
	::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE,
				 &optval, sizeof optval);
	// FIXME CHECK
}



