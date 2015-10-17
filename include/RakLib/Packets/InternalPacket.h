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

#ifndef INTERNAL_PACKET_H_
#define INTERNAL_PACKET_H_

#include <algorithm>
#include <iterator>
#include <vector>

#include "../Network/Packet.h"

namespace RakLib
{
	class InternalPacket 
	{
	public:
		uint8* buff;
		uint16 length;
		uint8 reliability = 0;
		bool hasSplit = false;
		uint32 messageIndex;
		uint32 orderIndex;
		uint8 orderChannel;
		uint32 splitCount;
		uint16 splitID;
		uint32 splitIndex;

	public:

		static std::vector<InternalPacket*> fromBinary(uint8* buffer, uint32 size);

		uint32 getLength();
		Packet* toBinary();
		void close();
	};

}
#endif