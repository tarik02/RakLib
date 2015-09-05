#include "RakLib/Session.h"

#include "RakLib/Packets/Acknowledge.h"

namespace RakLib
{
	Session::Session(std::string ip, unsigned short port, long clientID, short mtu) : _ip(ip), _port(port)
	{
		this->_clientID = clientID;
		this->_mtuSize = mtu;

		this->_normalQueue = new CustomPacket(nullptr, 0);
		this->_updateQueue = new CustomPacket(nullptr, 0);
	}

	//This method should be called often but not too often
	void Session::update()
	{
		if (!this->_updateQueue->packets.empty())
		{
			this->_updateQueue->packetID = 0x80;
			this->_updateQueue->sequenceNumber = this->_sequenceNum++;
			this->_updateQueue->encode();
			this->sendPacket(this->_updateQueue);
		}

		if (!this->_ACKQueue.empty())
		{
			Acknowledge ack(0xC0, this->_ACKQueue);
			ack.encode();
			this->sendPacket(&ack);
		}

		if (!this->_NACKQueue.empty())
		{
			Acknowledge nack(0xA0, this->_NACKQueue);
			nack.encode();
			this->sendPacket(&nack);
		}
	}

	void Session::receivePacket(Packet* packet)
	{

		uint8 packetID = packet->getBuffer()[0];
		if (packetID == 0xC0 || packetID == 0xA0) // ACK and NACK
		{
			//TODO: Handle ACK and NACK
			printf("Acknowledge packet: 0x%02X", packetID);
		}
		else if (packetID >= 0x80 || packetID <= 0x8F) // Custom Packets Range
		{
			printf("CustomPacket Received: 0x%02X", packetID);
			CustomPacket customPacket(packet);
			customPacket.decode();
			for (InternalPacket* internalPacket : customPacket.packets)
			{
				//TODO: Handle splitted packets
				DataPacket dataPacket(internalPacket);
				this->handleDataPacket(&dataPacket);
			}
		}
		else
		{
			printf("Unknown Packet: 0x%02X", packetID);
		}
	}

	//You need to encode the data packet before using this function.
	void Session::addToQueue(DataPacket* packet, Session::QueuePriority priority)
	{
		//TODO: Split packet if length > MTU
		InternalPacket* internalPacket = new InternalPacket();
		internalPacket->reliability = 2;
		internalPacket->messageIndex = this->_messageIndex++;
		internalPacket->buff = packet->getBuffer();
		internalPacket->length = packet->getLength();

		if (priority == Session::QueuePriority::IMMEDIATE)
		{
			CustomPacket customPacket(nullptr, 0); 
			customPacket.packetID = 0x80;
			customPacket.sequenceNumber = this->_sequenceNum++;
			
			//Add the data packet
			customPacket.packets.push_back(internalPacket); 
			customPacket.encode();

			this->sendPacket(&customPacket);

			internalPacket->close();
			delete internalPacket;
		}
		else if (priority == Session::QueuePriority::UPDATE)
		{
			this->_updateQueue->packets.push_back(internalPacket);
		}
		else if (priority == Session::QueuePriority::FULLQ)
		{
			this->_normalQueue->packets.push_back(internalPacket);
			if (this->_normalQueue->getLength() > this->_mtuSize)
			{
				this->_normalQueue->packetID = 0x80;
				this->_normalQueue->sequenceNumber = this->_sequenceNum++;
				this->_normalQueue->encode();
				this->sendPacket(this->_normalQueue);

				for (InternalPacket* inPacket : this->_normalQueue->packets)
				{
					inPacket->close();
					delete inPacket;
				}
				this->_normalQueue->packets.clear();
			}

		}
	}
}
