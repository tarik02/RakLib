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

#include "RakLib/Network/UDPSocket.h" 

namespace RakLib
{

	UDPSocket::UDPSocket() : UDPSocket("", DEFAULT_PORT){}

	UDPSocket::UDPSocket(short port) : UDPSocket("", port) {}

	UDPSocket::UDPSocket(std::string ip) : UDPSocket(ip, DEFAULT_PORT) {}

	UDPSocket::UDPSocket(std::string ip, short port)
	{
		this->_mut = new std::mutex();

		this->isRuning = false;

#ifdef WIN32 
		if (WSAStartup(MAKEWORD(2, 2), &this->data) != 0)
			return;
#endif 

		if (this->sock = socket(AF_INET, SOCK_DGRAM, 0) == INVALID_SOCKET)
		{
			std::string error = "Could not create the socket!";
#ifdef WIN32 
			error.assign("Error Code: " + WSAGetLastError());
			WSACleanup();
#else 
			error.assign("Error Code: -1");
#endif 

			throw std::runtime_error(error.c_str());
		}

		this->isStarted = true;
		this->bind(ip.c_str(), port) == 0 ? this->isRuning = true : this->isRuning = false;
	}

	int UDPSocket::bind(std::string ip, short port)
	{
		struct sockaddr_in addr;
		memset(&addr, 0, sizeof(addr));

		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);

		if (!ip.empty())
			inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);
		else
			addr.sin_addr.s_addr = htonl(INADDR_ANY);

		if (::bind(this->sock, (struct sockaddr*) &addr, sizeof(struct sockaddr_in)) == -1)
		{
			std::string error = "Could not create the socket!";
#ifdef WIN32 
			error.assign("Error Code: " + WSAGetLastError());
			WSACleanup();
#else 
			error.assign("Error Code: -1");
#endif 

			throw std::runtime_error(error.c_str());
		}
		return 0;
	}

	Packet* UDPSocket::receive()
	{
		this->_mut->lock();

		struct sockaddr_in recv;
		this->buffer = (unsigned char*)malloc(BUFFER_SIZE);

		int sie = sizeof(struct sockaddr_in);
		socklen_t size = recvfrom(this->sock, (char*)this->buffer, BUFFER_SIZE, 0, (struct sockaddr*)&recv, (socklen_t*)&sie);

		if (size == -1)
		{
			std::string error = std::string("[SOCKET][ERROR] Could not be sended the Packet!");
#ifdef WIN32 
			error.append(" Error Code: " + WSAGetLastError());
#else
			error.append(" Error Code: " + size);
#endif 
			std::runtime_error(error.c_str());

			this->_mut->unlock();
			this->close();
			return nullptr;
		}


		char ip[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &recv.sin_addr, ip, INET_ADDRSTRLEN);

		Packet* pck = new Packet(buffer, (short)size);
		pck->ip.assign(ip);
		pck->port = (uint16_t)recv.sin_port;

		this->_mut->unlock();
		return pck;
	}

	int UDPSocket::send(Packet* pck)
	{
		this->_mut->lock();

		struct sockaddr_in sendaddr;
		sendaddr.sin_family = AF_INET;
		sendaddr.sin_port = pck->port;
		inet_pton(AF_INET, pck->ip.c_str(), &sendaddr.sin_addr);

		int size = sendto(this->sock, (char*)pck->getBuffer(), pck->getLength(), 0, (struct sockaddr*)&sendaddr, sizeof(struct sockaddr_in));
		if (size == -1)
		{
			std::string error = std::string("[SOCKET][ERROR] Could not be sended the Packet!");

#ifdef WIN32 
			error.append(" Error Code: " + WSAGetLastError());
#else
			error.append(" Error Code: " + size);
#endif 
			std::runtime_error(error.c_str());

			this->_mut->unlock();
			this->close();
			return size;
		}

		this->_mut->unlock();
		return size;
	}

	bool UDPSocket::close()
	{
#ifdef __unix__
		close(this->sock);
#elif defined(_WIN32)
		closesocket(this->sock);
		WSACleanup();
#endif

		free(this->buffer);
		this->isRuning = false;
		this->isStarted = false;
		return true;
	}

	UDPSocket::~UDPSocket()
	{
		this->close();
	}
}