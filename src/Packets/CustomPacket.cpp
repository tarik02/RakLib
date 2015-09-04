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
	CustomPacket::CustomPacket(Packet* packet) : Packet(packet)
	{}

	CustomPacket::CustomPacket(uint32 seqNumber) : sequenceNumber(seqNumber)
	{}

	CustomPacket::~CustomPacket()
	{
		for (Packet* packet : this->packets) {
			delete packet;
		}
		this->packets.clear();
	}


	// TODO: Handle the reliability
	void CustomPacket::encode()
	{
		this->putByte(0x80); // The packet id can be 0x80-0x8F
		this->putLTriad(this->sequenceNumber);
		for (Packet* packet : this->packets)
		{
			this->putByte(0x00); //set the flag. reliability and has split
			this->putShort(packet->getLength() * 8); // Length in bits
			this->putByte(packet->getBuffer(), this->getLength());
		}
	}

	// TODO: Handle the reliability
	void CustomPacket::decode()
	{
		uint8 id = this->getByte();
		if (id < 0x80 || id > 0x8f)
			throw std::runtime_error("Invalid Packet ID"); // This SHOULD never happen

		this->sequenceNumber = this->getLTriad();

		while (this->position < this->length) {
			uint8 flag = this->getByte();
			uint8 reliability = (flag & 0xE0) >> 5;
			bool hasSplit = (flag & 0x10);

			uint16 length = ((this->getShort() + 7) >> 3); // The Length is in bits, so Bits to Bytes conversion

			if (reliability == 2 || reliability == 3 || reliability == 4 || reliability == 6 || reliability == 7) {
				this->getLTriad(); // Message Index
			}

			if (reliability == 1 || reliability == 3 || reliability == 4 || reliability == 7) {
				this->getLTriad(); // Order Index
				this->getByte(); // Order Channel
			}

			if (hasSplit) {
				this->getInt(); // Split Count
				this->getShort(); // Split ID
				this->getInt(); // Split Index
			}

			this->packets.push_back(new Packet(this->getByte(length), length));
		}
	}
}