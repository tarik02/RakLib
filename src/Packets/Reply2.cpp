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
#include "RakLib/Packets/Reply2.h"

namespace RakLib
{

	Reply2::Reply2(long serverid, short port, short mtu, uint8 security) : LoginPacket(30) {
		this->serverID = serverid;
		this->Port = port;
		this->mtuSize = mtu;
		this->Security = security;
	}

	void Reply2::encode() {
		this->putByte(Packets::CONNECTION_REPLY_2);
		this->putByte(this->getMagic(), 16);
		this->putLong(this->serverID);
		this->putShort(this->Port);
		this->putShort(this->mtuSize);
		this->putByte(this->Security);
	}
}