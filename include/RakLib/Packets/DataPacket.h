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

#include "InternalPacket.h"
#include "../Network/Packet.h"

namespace RakLib
{
	class DataPacket : public Packet
	{
	public:
		DataPacket(InternalPacket* pck) : Packet(pck->buff, pck->length) {}

		DataPacket(Packet* packet) : Packet(packet) {}

		DataPacket(uint32 size) : Packet(size) {}

		virtual void encode() { };
		virtual void decode() { };
	};
}
#endif