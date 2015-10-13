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

#ifndef LOGIN_PACKET_H_
#define LOGIN_PACKET_H_

#include "../Info.h"
#include "../Network/Packet.h"

namespace RakLib
{
	class LoginPacket : public Packet 
	{

	public:
		LoginPacket();
		LoginPacket(Packet* pck);
		LoginPacket(uint32 size);

		virtual void decode();
		virtual void encode();

		uint8* getMagic();
	};
}
#endif