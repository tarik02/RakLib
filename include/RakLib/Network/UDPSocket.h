/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* @author InusualZ
*
*
*/

#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <exception>
#include <mutex>

#ifdef __unix__
#   include <errno.h>
#   include <sys/types.h>
#   include <sys/socket.h>
#   include <sys/un.h>
#   include <netinet/in.h>
#   include <netdb.h>
#   include <arpa/inet.h>
#   include <unistd.h>
#define INVALID_SOCKET -1
#else
#   include <winsock2.h>
#   include <Ws2tcpip.h>
#   include <windows.h>
#	ifdef _MSC_VER
#   	pragma comment( lib, "Ws2_32.lib")
#	endif
#endif

#define DEFAULT_PORT 19132
#define BUFFER_SIZE 1048 * 2

#include "Packet.h"

namespace RakLib
{
	class UDPSocket
	{
	private:
		bool isStarted;

	#ifdef WIN32
		SOCKET sock;
		WSAData data;
	#else
		int sock;
	#endif

	public:
		bool isRuning;

	public:
		UDPSocket();
		UDPSocket(short port);
		UDPSocket(std::string ip);
		UDPSocket(std::string ip, short port);
		~UDPSocket();

		bool bind(std::string ip, short port);

		Packet* receive();
		int send(Packet*);

		void close();

	};
}
#endif