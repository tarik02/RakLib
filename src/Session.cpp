#include "RakLib/Packets/Acknowledge.h"
#include "RakLib/Session.h"

namespace RakLib
{
	Session::Session(std::string ip, unsigned short port, long clientID, short mtu) : _ip(ip), _port(port) {
		this->_clientID = clientID;
		this->_mtuSize = mtu;

		this->_normalQueue = new CustomPacket(nullptr, 0);
		this->_updateQueue = new CustomPacket(nullptr, 0);
	}

	//This method should be called often but not too often. 
	void Session::update() {
		if (!this->_updateQueue->packets.empty()) {
			this->_updateQueue->packetID = 0x80;
			this->_updateQueue->sequenceNumber = this->_sequenceNum++;
			this->_updateQueue->encode();

			this->sendPacket(this->_updateQueue);
			this->_recoveryQueue[this->_updateQueue->sequenceNumber] = this->_updateQueue;

			this->_updateQueue = new CustomPacket(nullptr, 0);
		}

		if (!this->_ACKQueue.empty()) {
			Acknowledge ack(0xC0, this->_ACKQueue);
			ack.encode();
			this->sendPacket(&ack);
			this->_ACKQueue.clear();
		}

		if (!this->_NACKQueue.empty()) {
			Acknowledge nack(0xA0, this->_NACKQueue);
			nack.encode();
			this->sendPacket(&nack);
		}
	}


	//This method should only be called from RakLib
	void Session::receivePacket(Packet* packet) {
		uint8 packetID = packet->getBuffer()[0];
		if (packetID == 0xC0) { // ACK
			Acknowledge ack(packet);
			ack.decode();

			for (uint32 i : ack.sequenceNumbers) {
				if (this->_recoveryQueue[i] != nullptr) {
					delete this->_recoveryQueue[i];
				}
			}

		} else if (packetID == 0xA0) { // NACK
			Acknowledge nack(packet);
			nack.decode();

			for (uint32 i : nack.sequenceNumbers) {
				if (this->_recoveryQueue[i] != nullptr) {
					this->sendPacket(this->_recoveryQueue[i]);
				}
			}
		} else if (packetID >= 0x80 && packetID <= 0x8F) {  // Custom Packets Range
			CustomPacket customPacket(packet);
			customPacket.decode();

			this->_ACKQueue.push_back(customPacket.sequenceNumber);

			//If this `if` is false then the custom packet was a lost packet
			if (this->_sequenceNum < customPacket.sequenceNumber) {
				this->_lastSequenceNum = this->_sequenceNum;
				this->_sequenceNum = customPacket.sequenceNumber;

				if (customPacket.sequenceNumber - this->_lastSequenceNum > 1) {
					for (uint32 i = this->_lastSequenceNum + 1; i < this->_sequenceNum; i++) {
						this->_NACKQueue.push_back(i);
					}
				}
			} else {
				for (uint32 i = 0; i < this->_NACKQueue.size(); i++) {
					if (this->_NACKQueue[i] == customPacket.sequenceNumber) {
						this->_NACKQueue.erase(this->_NACKQueue.begin() + i);
					}
				}
			}

			for (InternalPacket* internalPacket : customPacket.packets) {
				//TODO: Handle splitted packets
				DataPacket dataPacket(internalPacket);
				this->handleDataPacket(&dataPacket);

				internalPacket->close();
				delete internalPacket;
			}
			customPacket.packets.clear();
		} else {
			printf("Unknown Packet: 0x%02X", packetID);
		}
	}

	//You need to encode the data packet before using this function.
	void Session::addToQueue(DataPacket* packet, QueuePriority priority) {
		//TODO: Split packet if length > MTU
		InternalPacket* internalPacket = new InternalPacket();
		internalPacket->reliability = 2;
		internalPacket->messageIndex = this->_messageIndex++;
		internalPacket->buff = packet->getBuffer();
		internalPacket->length = packet->getLength();

		if (priority == QueuePriority::IMMEDIATE) {
			CustomPacket* customPacket = new CustomPacket(nullptr, 0);
			customPacket->packetID = 0x80;
			customPacket->sequenceNumber = this->_sequenceNum++;
			
			//Add the data packet
			customPacket->packets.push_back(internalPacket); 
			customPacket->encode();

			this->sendPacket(customPacket);
			this->_recoveryQueue[customPacket->sequenceNumber] = customPacket; // When we receive a notification that this packet have been received, the packet will be destroyed.
		} else if (priority == QueuePriority::UPDATE) {
			this->_updateQueue->packets.push_back(internalPacket);
		} else if (priority == QueuePriority::FULLQ) {
			this->_normalQueue->packets.push_back(internalPacket);
			if (this->_normalQueue->getLength() > this->_mtuSize) {
				this->_normalQueue->packetID = 0x80;
				this->_normalQueue->sequenceNumber = this->_sequenceNum++;
				this->_normalQueue->encode();

				this->sendPacket(this->_normalQueue);
				this->_recoveryQueue[this->_normalQueue->sequenceNumber] = this->_normalQueue; // When we receive a notification that this packet have been received, the packet will be destroyed.

				this->_normalQueue = new CustomPacket(nullptr, 0);
			}

		}
	}
}
