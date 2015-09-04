#include "RakLib/Session.h"

namespace RakLib
{
	Session::Session() : _ip("0.0.0.0"), _port(0)
	{
		this->_clientID = 0;
		this->_mtuSize = 0;
	}

	Session::Session(std::string ip, unsigned short port, long clientID, short mtu) : _ip(ip), _port(port)
	{ 
		this->_clientID = clientID;
		this->_mtuSize = mtu;
	}


	//TODO
	void Session::receivePackets(Packet* packet)
	{}

	//TODO
	void addToQueue(DataPacket* packet, Session::QueuePriority priority)
	{}
}
