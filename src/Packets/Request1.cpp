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

#include "RakLib/Packets/Request1.h"

namespace RakLib
{

	Request1::Request1(Packet* packet) : LoginPacket(packet) {}

	void Request1::decode() {
		this->position += 17; // Skip Raknet Magic AND Packet ID
		this->version = this->getByte();
		this->mtuSize = (short)(this->length - this->position);
	}

}