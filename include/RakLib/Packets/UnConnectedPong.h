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

#ifndef UNCONNECTED_PONG_H_
#define UNCONNECTED_PONG_H_

#include "LoginPacket.h"

namespace RakLib
{
	class UnConnectedPong : public LoginPacket
	{
	public:
		long serverID;
		long pingID;
		std::string str;

		UnConnectedPong(long serverID, long pingID, const std::string& title);

		void encode();
	};
}
#endif
