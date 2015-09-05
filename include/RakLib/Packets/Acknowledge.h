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
#ifndef ACKNOWLEDGE_H_
#define ACKNOWLEDGE_H_

#include "../Network/Packet.h"
#include <vector>
#include <algorithm>

namespace RakLib
{

	class Acknowledge : public Packet
	{
	public:
		std::vector<uint32> sequenceNumbers;
		uint8 pid; // ACK || NACK

	public:
		Acknowledge(uint8 pid, std::vector<uint32> sequenzeNum);
		Acknowledge(Packet* pck);

		void decode();
		void encode();

	};
}
#endif