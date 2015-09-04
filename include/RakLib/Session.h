#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
//#include <map>

#include "Packets\DataPacket.h"
#include "Network\Packet.h"

namespace RakLib
{
	class Session
	{
	public:
		enum class State : uint8
		{
			UnConnected,
			Connecting,
			PreLogin,
			Logged
		};


		enum class QueuePriority
		{
			IMMEDIATE, // The packet is going to be sended immediately
			UPDATE, // The packet is going to be sended in the next update
			NORMAL, // The packet will be sended when the queue get full
		};

	protected:
		const std::string _ip;
		const uint16 _port;
		State _currentState;

		long _clientID;

	private:
		int _lastSequenceNum;
		int _sequenceNum;
		int _messageIndex;

	protected:
		uint16 _mtuSize;

	private:
		//CustomPacket* _queue;
		std::vector<uint32> _ACKQueue; // Received Packet Queue
		std::vector<uint32> _NACKQueue; // Not received packet queue
		//std::map<uint32, CustomPacket> _recoveryQueue; // Packet sent queue to be used if not received

	public:
		Session();
		Session(std::string ip, unsigned short port, long clientID, short mtu);

		Session& operator=(const Session&) { return *this; }

		virtual void receivePackets(Packet* packet);

		virtual void handleDataPacket(DataPacket* packet) = 0;

		virtual void addToQueue(DataPacket* packet, QueuePriority priority);
		virtual void sendPacket(Packet* packet) = 0; 
		
		inline const std::string& getIP() const { return this->_ip; };
		inline uint16 getPort() const { return this->_port; };
		inline State getState() const { return this->_currentState; };

	};
}

#endif