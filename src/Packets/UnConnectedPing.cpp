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

#include "RakLib/Packets/UnconnectedPing.h"

namespace RakLib
{

	UnConnectedPing::UnConnectedPing(Packet* pck) : LoginPacket(pck) {}

	void UnConnectedPing::decode() {
		this->position += 1; // Skip ID
		this->pingID = this->getLong();
	}
}