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
		std::shared_ptr<UDPSocket> _socket;
		std::shared_ptr<SessionManager> _sessionManager;
		std::thread* _mainThread;

		std::string _ip;
		uint16 _port;

		bool _isRunning;

	public:
		RakLib(uint16 port);
		RakLib(const std::string& ip, uint16 port);
		RakLib(const std::string& ip, uint16 port, SessionManager* sessionManager);
		~RakLib();

		const std::string& getIP() const;
		uint16_t getPort() const;
		bool isRunning() const;

		void sendPacket(Packet* packet);

		void setSessionManager(SessionManager* sessionManager);

		std::string getPlayerIdentifier(const std::string& ip, uint16_t port);

		void start();
		void run();
		void stop();
	};
}

#endif