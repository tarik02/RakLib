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

#ifndef CUSTOMPACKET_H_
#define CUSTOMPACKET_H_

#include "../Network/Packet.h"
#include "DataPacket.h"

#include <list>

namespace RakLib
{
	enum Reliability
	{
		UNRELIABLE,
		UNRELIABLE_SEQUENCED,
		RELIABLE,
		RELIABLE_ORDERED,
		RELIABLE_SEQUENCED,
		UNRELIABLE_WITH_ACK_RECEIPT,
		RELIABLE_WITH_ACK_RECEIPT,
		RELIABLE_ORDERED_WITH_ACK_RECEIPT
	};

	class CustomPacket : public Packet
	{
	public:
		uint32 sequenceNumber;
		std::list<Packet*> packets;


		CustomPacket(Packet* packet);
		CustomPacket(uint32 seqNumber);
		~CustomPacket();

		void encode();
		void decode();
	};
}
#endif