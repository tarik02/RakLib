/**
* This program is free software: you can redistribute it and/|| modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, ||
* (at your option) any later version.
*
* @author InusualZ
*
*
*/
#include "RakLib\Packets\InternalPacket.h"

namespace RakLib
{

	std::vector<InternalPacket*> InternalPacket::fromBinary(uint8* buffer, uint32 size)
	{
		Packet* pck = new Packet(buffer, size);
		std::vector<InternalPacket*> packets;
		while (pck->getPosition() < pck->getLength())
		{
			InternalPacket* packet = new InternalPacket();
			uint8 flags = pck->getByte();
			packet->reliability = (flags & 0xE0) >> 5;
			packet->hasSplit = (flags & 0x10) > 0;

			packet->length = (uint32)ceil(pck->getShort() / 8);
			/*
			* From http://www.jenkinssoftware.com/raknet/manual/reliabilitytypes.html
			*
			* Default: 0b010 (2) || 0b011 (3)
			*
			* 0: UNRELIABLE
			* 1: UNRELIABLE_SEQUENCED
			* 2: RELIABLE
			* 3: RELIABLE_ORDERED
			* 4: RELIABLE_SEQUENCED
			* 5: UNRELIABLE_WITH_ACK_RECEIPT
			* 6: RELIABLE_WITH_ACK_RECEIPT
			* 7: RELIABLE_ORDERED_WITH_ACK_RECEIPT
			*/

			if (packet->reliability == 2 || packet->reliability == 3 || packet->reliability == 4 || packet->reliability == 6 || packet->reliability == 7)
			{
				packet->messageIndex = pck->getLTriad();
			}

			if (packet->reliability == 1 || packet->reliability == 3 || packet->reliability == 4 || packet->reliability == 7)
			{
				packet->orderIndex = pck->getLTriad();
				packet->orderChannel = pck->getByte();
			}

			if (packet->hasSplit) 
			{
				packet->splitCount = pck->getInt();
				packet->splitID = pck->getShort();
				packet->splitIndex = pck->getInt();
			}

			packet->buff = pck->getByte(packet->length);
			packets.push_back(packet);
		}

		return packets;
	}


	Packet* InternalPacket::toBinary(){
		Packet* packet = new Packet(getLength());
		packet->putByte((uint8)((this->reliability << 5) | (this->hasSplit ? true : false)));
		packet->putShort((short)(this->length << 3));
		if (this->reliability == 0x02 || this->reliability == 0x03 || this->reliability == 0x04 || this->reliability == 0x06 || this->reliability == 0x07)
		{
			packet->putLTriad(this->messageIndex);
		}

		if (this->reliability == 0x01 || this->reliability == 0x03 || this->reliability == 0x04 || this->reliability == 0x07)
		{
			packet->putLTriad(this->orderIndex);
			packet->putByte(this->orderChannel);
		}

		if (this->hasSplit)
		{
			packet->putInt(this->splitCount);
			packet->putShort(this->splitID);
			packet->putInt(this->splitIndex);
		}

		packet->putByte(this->buff, this->length);
		return packet;
	}

	uint32 InternalPacket::getLength(){
		return 3 + this->length + (this->messageIndex != -1 ? 3 : 0) + (this->orderIndex != -1 ? 4 : 0) + (this->hasSplit ? 10 : 0);
	}


	void InternalPacket::close()
	{
		free(this->buff);
		this->length = 0;
	}
}