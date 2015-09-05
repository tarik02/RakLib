#ifndef RAKLIB_H_
#define RAKLIB_H_

#include <string>
#include <memory>
#include <stdexcept>
#include <thread>

#include "Network/UDPSocket.h"
#include "SessionManager.h"

namespace RakLib
{
	class RakLib
	{
	private:
		UDPSocket* _socket;
		SessionManager* _sessionManager;
		std::thread* _mainThread;

		std::string _ip;
		uint16 _port;

		bool _isRunning;

	public:
		RakLib(std::string ip, uint16 port, SessionManager* sessionManager);
		~RakLib();

		inline const std::string& getIP() const { return this->_ip; };
		inline uint16_t getPort() const { return this->_port; };
		inline bool isRunning() const { return this->_isRunning; };

		void sendPacket(Packet* packet);

		std::string getPlayerIdentifier(const std::string& ip, uint16_t port);

		void start();
		void run();
		void stop();
	};
}

#endif