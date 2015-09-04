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

#ifndef REPLY_1_H_
#define REPLY_1_H_

#include "LoginPacket.h"

namespace RakLib
{
	class Reply1 : public LoginPacket
	{
	public:
		uint8 Security;
		long serverID;
		short mtuSize;

	public:
		Reply1(uint8 sec, long serverid, short mtu);

		void encode();
	};
}
#endif