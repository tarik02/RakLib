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

#ifndef DATAPACKET_H_
#define DATAPACKET_H_

#include "../Network/Packet.h"

namespace RakLib
{
	class DataPacket : public Packet
	{
	public:
		DataPacket(uint32 size) : Packet(size) {}
		DataPacket(uint8* buffer, uint32 size) : Packet(buffer, size) {}
		DataPacket(Packet* packet) : Packet(packet) {}


		virtual void encode() = 0;
		virtual void decode() = 0;
	};
}
#endif