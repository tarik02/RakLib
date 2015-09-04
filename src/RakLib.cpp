#include "RakLib/RakLib.h"
#include "RakLib/Info.h"
#include "RakLib/Packets/Reply1.h"
#include "RakLib/Packets/Reply2.h"
#include "RakLib/Packets/Request1.h"
#include "RakLib/Packets/Request2.h"
#include "RakLib/Packets/UnConnectedPing.h"
#include "RakLib/Packets/UnConnectedPong.h"
#include "RakLib/Session.h"

namespace RakLib
{
	RakLib::RakLib(uint16 port) : RakLib("0.0.0.0", port) {}

	RakLib::RakLib(const std::string& ip, uint16 port)
	{
		this->_ip = ip;
		this->_port = port;
		this->_isRunning = false;
	}

	RakLib::RakLib(const std::string& ip, uint16 port, SessionManager* sessionManager) : RakLib(ip, port)
	{
		this->_sessionManager = std::make_shared<SessionManager>(&sessionManager);
	}

	const std::string& RakLib::getIP() const
	{
		return this->_ip;
	}

	unsigned short RakLib::getPort() const
	{
		return this->_port;
	}

	bool RakLib::isRunning() const
	{
		return this->_isRunning;
	}

	std::string RakLib::getPlayerIdentifier(const std::string& ip, uint16 port)
	{
		std::string retval(ip.c_str());
		return retval.append(":" + port);
	}

	void RakLib::setSessionManager(SessionManager* sessionManager)
	{
		this->_sessionManager = std::make_shared<SessionManager>(&sessionManager);
	}

	void RakLib::start()
	{
		if (this->_isRunning)
			throw std::runtime_error("RakLib already running!");

		if (!this->_sessionManager)
			throw std::runtime_error("There is no sessions manager!");

		this->_isRunning = true;
		this->_socket = std::make_shared<UDPSocket>(UDPSocket(this->_ip, (uint16) this->_port));
		this->_mainThread = new std::thread(&RakLib::run, this);
	}

	void RakLib::run()
	{
		while (this->_isRunning && this->_sessionManager)
		{
			Packet* pck = this->_socket->receive();
			uint8 pid = pck->getBuffer()[0];

			switch (pid)
			{
			case Packets::UNCONNECTED_PONG:
			case Packets::UNCONNECTED_PONG_2:
			{
				UnConnectedPing ping(pck);
				ping.decode();


				UnConnectedPong pong(123456789, ping.pingID, "Minecraft Server!");
				pong.encode();

				pong.ip = pck->ip;
				pong.port = pck->port;

				this->_socket->send(&pong);
			}
			break;

			case Packets::CONNECTION_REQUEST_1:
			{
				Request1 request(pck);
				request.decode();

				Reply1 reply(0x00, 123456789, request.mtuSize);
				reply.encode();

				reply.ip = pck->ip;
				reply.port = pck->port;

				this->_socket->send(&reply); // Send the packet
			}
			break;

			case Packets::CONNECTION_REQUEST_2:
			{
				Request2 request(pck);
				request.decode();

				Reply2 reply(123456789L, pck->port, request.mtuSize, request.Security);
				reply.encode();

				reply.ip = pck->ip;
				reply.port = pck->port;

				this->_socket->send(&reply);
				this->_sessionManager->addSession(pck->ip, pck->port, request.clientID, reply.mtuSize);

			}
			break;
			}

			delete pck;
		}
	}

	void RakLib::sendPacket(Packet* packet)
	{
		this->_socket->send(packet);
	}

	void RakLib::stop()
	{
		if (!this->_isRunning)
			throw std::runtime_error("RakLib is not running!");

		this->_isRunning = false;
		this->_mainThread->join();

		delete this->_mainThread;
	}
}