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

#include "RakLib/Packets/UnConnectedPong.h"

namespace RakLib
{
	UnConnectedPong::UnConnectedPong(long serverID, long pingID, const std::string& title) : LoginPacket(35 + title.length())
	{
		this->serverID = serverID;
		this->pingID = pingID;
		this->str = title; //MCPE;ServerName;MCPEProtocol;MCPEVersion;Players;MaxPlayer
	}

	void UnConnectedPong::encode()
	{
		this->putByte(Packets::UNCONNECTED_PING);
		this->putLong(this->pingID);
		this->putLong(this->serverID);
		this->putByte(this->getMagic(), 16);
		this->putString(this->str);

	}
}