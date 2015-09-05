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

#ifndef _PACKET_H_
#define _PACKET_H_

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include <algorithm>

#include "../CommonTypes.h"

namespace RakLib
{

	class Packet
	{
	public:
		std::string ip;
		uint16 port;

	protected:
		uint32 length; // Since the length can't be negative
		uint32 position; // Since the position can't be negative
		uint8* buffer;

	public:
		Packet();
		Packet(uint32 size);
		Packet(uint8* buff, uint32 size);
		Packet(Packet* other);
		virtual ~Packet();

		//Write Methods
		void putByte(uint8 v);
		void putByte(uint8* v, int size);
		void putChar(char c);
		void putShort(short v);
		void putTriad(int v);
		void putLTriad(int v);
		void putInt(int v);
		void putFloat(float v);
		void putLong(long v);
		void putDouble(double v);
		void putString(std::string str);

		uint8 getByte();
		uint8* getByte(uint32 size);

		char getChar();

		short getShort();
		uint16 getUShort();

		int getTriad();
		int getLTriad();

		int getInt();
		uint32 getUInt();

		float getFloat();

		long getLong();
		uint64 getULong();

		double getDouble();

		std::string getString();

		const uint8& operator[] (uint32 index);

		//Properties
		virtual uint32 getLength() const;
		uint8* getBuffer();

		void setPosition(uint32);
		uint32 getPosition() const;

		void resize(size_t);
		void print();
		void clear();
		void close();

	};
}
#endif
