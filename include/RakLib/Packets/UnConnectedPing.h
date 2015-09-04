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

#ifndef UNCONNECTED_PING_H_
#define UNCONNECTED_PING_H_

#include "LoginPacket.h"

namespace RakLib
{
	class UnConnectedPing : public LoginPacket
	{
	public:
		long pingID;

	public:
		UnConnectedPing(Packet* pck);

		void decode();

	};
}
#endif