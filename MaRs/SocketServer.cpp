/*
 *  SocketServer.cpp
 *  CacheServer
 *
 *  Created by Ganesh M on 2/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#include <string.h>
#include <stdio.h>
#include <iostream>

#include "SocketServer.h"

using namespace CacheServer;

SocketServer::SocketServer(uint16_t port)
	: Socket(AF_INET, SOCK_STREAM, 0)
	, port_(port)
 
{
	
}

void SocketServer::init()
{
	char buffer[BUFSIZ];
	memset(&addr_, 0, sizeof(addr_));
	addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_.sin_port = htons(port_);
	
	setTcpNoDelay(true);
	setReuseAddr(true);
	setKeepAlive(true);
	
	bindAddress(addr_);
	listen();
	
	for (;;)
	{
		InetAddress peeraddr;
		int clientfd = accept(&peeraddr);
		if (clientfd < 0)
		{
			std::cerr << "accept error" << std::endl;
		}
		
		std::cout << "Accept OK!!" << std::endl;
		std::string msg = "Welcome to my server\n";
		
		int len = write(clientfd, msg.c_str(), msg.length());
		std::string readBuffer;
		
		do{
			int len = read(clientfd, buffer, sizeof buffer);
			if (len == 0)
			{
				// client it closed
				std::cout << "Client closed" << std::endl;
				break;
			}
			else if (len <0)
			{
				std::cout << "Some other error" << std::endl;
				break;
			}
			else if (len > 0)
			{
				readBuffer.append(buffer);
				std::cout << "Received: " << len << " bytes. " << readBuffer << std::endl;
			}
			
		}while(len == sizeof buffer);
		
		std::cout << "connection closed" << std::endl;
		//::close(clientfd);
	}
}



