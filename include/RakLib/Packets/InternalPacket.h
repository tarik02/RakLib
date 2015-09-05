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

#include <vector>
#include <algorithm>
#include <iterator>

#include "../Network/Packet.h"

namespace RakLib
{
	class InternalPacket 
	{
	public:
		uint8* buff;
		uint32 length;
		uint8 reliability = -1;
		bool hasSplit = false;
		int messageIndex = -1;
		int orderIndex = -1;
		uint8 orderChannel = (uint8)0xff;
		int splitCount = -1;
		short splitID = -1;
		int splitIndex = -1;

	public:

		static std::vector<InternalPacket*> fromBinary(uint8* buffer, uint32 size);

		uint32 getLength();
		Packet* toBinary();
		void close();
	};

}
#endif