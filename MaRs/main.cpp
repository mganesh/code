#include <iostream>
#include "SocketServer.h"

int main (int argc, char * const argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
	
	CacheServer::SocketServer Server(1234);
	Server.init();
	std::cout << "Bye !!" << std::endl;
    return 0;
}
