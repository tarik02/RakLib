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

#ifndef DATA_PACKET_H_
#define DATA_PACKET_H_

#include "../Network/Packet.h"
#include "InternalPacket.h"

namespace RakLib
{
	class DataPacket : public Packet
	{
	public:
		DataPacket(InternalPacket* pck)
		{
			this->buffer = pck->buff;
			this->length = pck->length;
			this->position = 0;
		}

		DataPacket(Packet* packet) : Packet(packet) {}

		DataPacket(uint32 size) : Packet(size) {}

		virtual void encode() { };
		virtual void decode() { };
	};
}
#endif