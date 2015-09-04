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

#ifndef REPLY_2_H_
#define REPLY_2_H_

#include "LoginPacket.h"

namespace RakLib
{
	class Reply2 : public LoginPacket
	{
	public:
		long serverID;
		short Port;
		short mtuSize;
		uint8 Security;

	public:
		Reply2(long serverid, short port, short mtu, uint8 security);

		void encode();

	};
}
#endif