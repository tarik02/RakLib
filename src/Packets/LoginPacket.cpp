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

#include "RakLib/Packets/LoginPacket.h"

namespace RakLib
{
	LoginPacket::LoginPacket() : Packet() {}

	LoginPacket::LoginPacket(Packet* pck) : Packet(pck) {}

	LoginPacket::LoginPacket(int size) : Packet(size) {}


	void LoginPacket::encode(){}
	void LoginPacket::decode(){}


	uint8* LoginPacket::getMagic()
	{
		return new uint8[16] { (uint8)0x00, (uint8)0xff, (uint8)0xff, (uint8)0x00, (uint8)0xfe, (uint8)0xfe, (uint8)0xfe, (uint8)0xfe, (uint8)0xfd, (uint8)0xfd, (uint8)0xfd, (uint8)0xfd, (uint8)0x12, (uint8)0x34, (uint8)0x56, (uint8)0x78 }; // 16 uint8_t
	}
}
