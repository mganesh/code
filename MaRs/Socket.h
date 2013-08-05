/*
 *  Socket.h
 *  CacheServer
 *
 *  Created by Ganesh M on 2/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

namespace CacheServer
{
	typedef struct sockaddr_in InetAddress;
	
	class Socket
	{
	public:
		Socket(int family, int stream, int type);
		
		~Socket();
		
		int fd() const { return sockfd_; }
		void bindAddress(const InetAddress& localaddr);
		void listen(int backlog=5);
		
		int accept(InetAddress* peeraddr);
		void close();
		
		//void shutdownWrite();
		void setTcpNoDelay(bool on);
		void setReuseAddr(bool on);
		void setKeepAlive(bool on);
		
	private:
		int sockfd_;
	};
};

#endif