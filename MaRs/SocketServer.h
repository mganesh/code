/*
 *  SocketServer.h
 *  CacheServer
 *
 *  Created by Ganesh M on 2/19/13.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _SOCKET_SERVER_H
#define _SOCKET_SERVER_H

#include <stdint.h>
#include "Socket.h"

namespace CacheServer
{
	class SocketServer : public Socket {
	public:
		explicit SocketServer(uint16_t port);
		const struct sockaddr_in& getSockAddrInet() const { return addr_; }
		void init();
	private:
		uint16_t port_;
		struct sockaddr_in addr_;
		//Socket socket_;
	};
};
#endif