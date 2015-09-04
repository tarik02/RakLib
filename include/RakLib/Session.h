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
		const std::string ip;
		const uint16 port;
		State currentState;

		int CID;

	private:
		int lastSequenceNum;
		int sequenceNum;
		int messageIndex;

	protected:
		uint16 mtuSize;

	private:
		//CustomPacket* queue;
		std::vector<uint32> ACKQueue; // Received Packet Queue
		std::vector<uint32> NACKQueue; // Not received packet queue
		//std::map<uint32, CustomPacket> recoveryQueue; // Packet sent queue to be used if not received

	public:
		Session(std::string ip, unsigned short port, long clientID, short mtu);

		virtual void receivePackets(Packet* packet);

		virtual void handleDataPacket(DataPacket* packet) = 0;

		virtual void addToQueue(DataPacket* packet, QueuePriority priority);
		virtual void sendPacket(Packet* packet) = 0; 
		
		const std::string& getIP() const;
		uint16 getPort() const;
		State getState() const;

	};
}

#endif