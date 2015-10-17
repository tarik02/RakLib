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
#include "RakLib\Packets\CustomPacket.h"

namespace RakLib
{

	CustomPacket::CustomPacket(Packet* packet) : Packet(packet) {}

	CustomPacket::CustomPacket(uint8* data, uint32 size) : Packet(data, size) {}

	CustomPacket::CustomPacket() {
		this->packetID = 0x84;
	}

	CustomPacket::~CustomPacket() {
		for (InternalPacket* pck : this->packets) {
			pck->close();
			delete pck;
		}
		this->packets.clear();
	}

	uint32 CustomPacket::getLength() {
		uint32 length = 4; // PacketID + sequence number(Triad)
		for (InternalPacket* pck : this->packets) {
			length += pck->getLength();
		}
		return length;
	}

	void CustomPacket::decode() {
		this->packetID = this->getByte();
		this->sequenceNumber = (uint32)this->getTriad();
		this->packets = InternalPacket::fromBinary(this->buffer + this->position, this->length - 4);
	}

	void CustomPacket::encode() {
		this->buffer = new uint8[this->getLength()];
		this->putByte(this->packetID);
		this->putLTriad((int)this->sequenceNumber);
		for (InternalPacket* pck : packets) {
			Packet temp = pck->toBinary();
			this->putByte(temp.getBuffer(), temp.getLength());
			temp.close();
		}
	}
}