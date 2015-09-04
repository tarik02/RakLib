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

#ifndef REQUEST_2_H_
#define REQUEST_2_H_

#include "LoginPacket.h"

namespace RakLib 
{
	class Request2 : public LoginPacket
	{
	public:
		uint8 Security;
		int Cookie;
		uint16 Port;
		uint16 mtuSize;
		long clientID;

	public:
		Request2(Packet* packet);

		void decode();
	};
}
#endif