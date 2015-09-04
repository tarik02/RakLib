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

#ifndef REQUEST_1_H_
#define REQUEST_1_H_

#include "LoginPacket.h"

namespace RakLib
{
	class Request1 : public LoginPacket
	{
	public:
		uint8 version;
		short mtuSize;

	public:
		Request1(Packet* packet);

		void decode();
	};
}
#endif