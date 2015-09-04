#ifndef PACKETS_H_
#define PACKETS_H_

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

namespace RakLib
{
	enum Packets
	{
		PING = 0x00,
		PONG = 0x03,

		UNCONNECTED_PONG = 0x01,
		UNCONNECTED_PONG_2 = 0x02,

		UNCONNECTED_PING = 0x1C,

		CONNECTION_REQUEST_1 = 0x05,
		CONNECTION_REQUEST_2 = 0x07,

		CONNECTION_REPLY_1 = 0x06,
		CONNECTION_REPLY_2 = 0x08,

		CLIENT_CONNECT = 0x09,
		SERVER_HANDSHAKE = 0x10,

		CLIENT_HANDSHAKE = 0x13,

		SERVER_FULL = 0x14,
		DISCONNECT = 0x15,

		BANNED = 0x17

	};
}
#endif