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

#include "RakLib/Packets/Request2.h"

namespace RakLib
{

	Request2::Request2(Packet* packet) : LoginPacket(packet) {}


	void Request2::decode()
	{
		this->position += 17;
		this->Security = this->getByte();
		this->Cookie = this->getInt();
		this->Port = (uint16)this->getShort();
		this->mtuSize = (uint16)this->getShort();
		this->clientID = this->getLong();
	}
}