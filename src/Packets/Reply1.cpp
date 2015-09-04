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

#include "RakLib/Packets/Reply1.h"

namespace RakLib
{

	Reply1::Reply1(uint8 sec, long serverid, short mtu) : LoginPacket(28)
	{
		this->Security = sec;
		this->serverID = serverid;
		this->mtuSize = mtu;
	}

	void Reply1::encode()
	{
		this->putByte(Packets::CONNECTION_REPLY_1);
		this->putByte(this->getMagic(), 16);
		this->putLong(this->serverID);
		this->putByte(this->Security);
		this->putShort(this->mtuSize);
	}
}