/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* @author InusualZ
*
*
*/

#include "RakLib/Network/Packet.h"

namespace RakLib
{

	Packet::Packet() {
		this->buffer = (uint8*)malloc(1024);
		memset(this->buffer, 0x00, 1024);

		this->position = 0;
		this->length = 1024;
	}


	Packet::Packet(uint32 size) {
		this->buffer = (uint8*)malloc(size);
		memset(this->buffer, 0x00, size);

		this->position = 0;
		this->length = size;
	}


	Packet::Packet(uint8* buff, uint32 size) {
		this->buffer = (uint8*)malloc(size);
		memcpy(this->buffer, buff, size);

		this->position = 0;
		this->length = size;
	}

	Packet::Packet(Packet* other) {
		this->buffer = (uint8*)malloc(other->getLength());
		memcpy(this->buffer, other->getBuffer(), other->getLength());

		this->position = 0;
		this->length = other->getLength();

		this->ip = other->ip;
		this->port = other->port;
	}

	void Packet::putByte(uint8 v) {
		if (this->position > this->length) {
			throw std::exception("BufferOverflow");
		}

		this->buffer[this->position++] = v;
	}

	void Packet::putByte(uint8* v, uint32 size) {
		if (this->position + size > this->length) {
			throw std::exception("BufferOverflow");
		}

		memcpy((this->buffer + this->position), v, size);
		this->position += size;
	}

	void Packet::putChar(char c) {
		if (this->position > this->length) {
			throw std::exception("BufferOverflow");
		}

		this->buffer[this->position++] = c;
	}

	void Packet::putShort(short v) {
		if (this->position + 2 > this->length) {
			throw std::exception("BufferOverflow");
		}

		this->buffer[this->position++] = ((uint8)((v >> 8) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v     ) & 0xFF));
	}

	void Packet::putInt(int v) {
		if (this->position + 4 > this->length) {
			throw std::exception("BufferOverflow");
		}

		this->buffer[this->position++] = ((uint8)((v >> 24) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >> 16) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >>  8) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v      ) & 0xFF));
	}

	void Packet::putTriad(int v) {
		if (this->position + 3 > this->length) {
			throw std::exception("BufferOverflow");
		}

		this->buffer[this->position++] = ((uint8)((v >> 16) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >>  8) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v      ) & 0xFF));
	}

	void Packet::putLTriad(int v) {
		if (this->position + 3 > this->length) {
			throw std::exception("BufferOverflow");
		}

		this->buffer[this->position++] = ((uint8)((v      ) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >>  8) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >> 16) & 0xFF));
	}


	void Packet::putFloat(float v) {
		this->putInt((int)v);
	}

	void Packet::putLong(long v) {
		if (this->position + 8 > this->length) {
			throw std::exception("BufferOverflow");
		}

		this->buffer[this->position++] = ((uint8)((v >> 56) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >> 48) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >> 40) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >> 32) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >> 24) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >> 16) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v >>  8) & 0xFF));
		this->buffer[this->position++] = ((uint8)((v      ) & 0xFF));
	}

	void Packet::putDouble(double v) {
		this->putLong((long)v);
	}

	void Packet::putString(std::string str) {
		if (this->position + (str.size() + 2) > this->length) {
			throw std::exception("BufferOverflow");
		}

		this->putShort((short)str.length());
		for (uint32 i = 0; i < str.length(); i++) {
			this->buffer[this->position++] = str[i];
		}
	}

	//Get Methods
	uint8 Packet::getByte() {
		if (this->position > this->length)
			throw std::exception("BufferOverflow");

		return (uint8) this->buffer[this->position++];
	}

	uint8* Packet::getByte(uint32 size) {
		if (this->position + size > this->length) {
			throw std::exception("BufferOverflow");
		}

		uint8* temp = (uint8*)malloc(size);
		memcpy(temp, (this->buffer + this->position), size);
		this->position += size;
		return temp;
	}

	char Packet::getChar() {
		if (this->position > this->length) {
			throw std::exception("BufferOverflow");
		}

		return (char)(this->buffer[this->position++] & 0xFF);
	}


	std::string Packet::getString() {
		short size = getShort();
		if (size <= 0 || this->position + size > this->length) {
			throw std::exception("Size not valid!");
		}

		std::string temp = "";
		for (short i = 0; i < size; i++) {
			temp += (char)this->buffer[this->position++];
		}
		return temp;
	}

	short Packet::getShort() {
		if (this->position + 2 > this->length) {
			throw std::exception("BufferOverflow");
		}

		//WHY I CAN'T JUST DO: return (short) (((this->buffer[this->position++] << 8) & 0xFF) | (this->buffer[this->position++] & 0xFF)); 
		//WTF??
		this->position += 2;
		return (short) (((this->buffer[this->position - 2] << 8) & 0xFF) | (this->buffer[this->position - 1] & 0xFF));
	}

	int Packet::getTriad() {
		if (this->position + 3 > this->length) {
			throw std::exception("BufferOverflow");
		}

		return (
			((this->buffer[this->position++] << 16) & 0xFF) |
			((this->buffer[this->position++] <<  8) & 0xFF) |
			 (this->buffer[this->position++]        & 0xFF)
			);
	}

	int Packet::getLTriad() {
		if (this->position + 3 > this->length) {
			throw std::exception("BufferOverflow");
		}

		return (
			 (this->buffer[this->position++]        & 0xFF) |
			((this->buffer[this->position++] <<  8) & 0xFF) |
			((this->buffer[this->position++] << 16) & 0xFF)
			);
	}

	int Packet::getInt() {
		if (this->position + 4 > this->length) {
			throw std::exception("BufferOverflow");
		}

		return (
			((this->buffer[this->position++] << 24) & 0xFF) |
			((this->buffer[this->position++] << 16) & 0xFF) |
			((this->buffer[this->position++] <<  8) & 0xFF) |
			 (this->buffer[this->position++]        & 0xFF));
	}

	float Packet::getFloat() {
		return (float)(getInt());
	}

	long Packet::getLong() {
		if (this->position + 8 > this->length) {
			throw std::exception("BufferOverflow");
		}

		return (long)(
			(((long)this->buffer[this->position++] << 56) & 0xFF) |
			(((long)this->buffer[this->position++] << 48) & 0xFF) |
			(((long)this->buffer[this->position++] << 40) & 0xFF) |
			(((long)this->buffer[this->position++] << 32) & 0xFF) |
			(((long)this->buffer[this->position++] << 24) & 0xFF) |
			(((long)this->buffer[this->position++] << 16) & 0xFF) |
			(((long)this->buffer[this->position++] <<  8) & 0xFF) |
			 ((long)this->buffer[this->position++]        & 0xFF));
	}

	uint64 Packet::getULong() {
		if (this->position + 8 > this->length) {
			throw std::exception("BufferOverflow");
		}

		return (uint64)(
			((uint64)this->buffer[this->position++] << 56) |
			((uint64)this->buffer[this->position++] << 48) |
			((uint64)this->buffer[this->position++] << 40) |
			((uint64)this->buffer[this->position++] << 32) |
			((uint64)this->buffer[this->position++] << 24) |
			((uint64)this->buffer[this->position++] << 16) |
			((uint64)this->buffer[this->position++] <<  8) |
			((uint64)this->buffer[this->position++]      )
			);
	}

	double Packet::getDouble() {
		return (double)(this->getLong());
	}


	const uint8& Packet::operator[] (uint32 index) {
		if (index > this->length) {
			throw std::exception("IndexOutOfBound");
		}

		return this->buffer[index];
	}



	uint32 Packet::getLength() const {
		return this->length;
	}

	uint32 Packet::getPosition() const {
		return this->position;
	}

	uint8* Packet::getBuffer() {
		return this->buffer;
	}

	void Packet::setPosition(uint32 v) {
		this->position = v;
	}

	void Packet::resize(size_t size) {
		uint8* newBuffer = (uint8*)malloc(size);
		memset(newBuffer, 0x00, size);

		size_t newSize = (size > this->length) ? this->length : size;

		memcpy(newBuffer, this->buffer, newSize);
		free(this->buffer);

		this->buffer = newBuffer;
		this->position = ((this->position > newSize) ? newSize : this->position);
		this->length = size;
	}

	void Packet::print() {
		for (uint32 i = 0; i < this->length; i++) {
			printf("%02X ", this->buffer[i]);
			if ((i + 1) % 8 == 0 || (i + 1) == this->length) {
				printf("\n");
			}
		}
	}

	void Packet::clear() {
		free(this->buffer);
		this->buffer = (uint8*)malloc(this->length);
		memset(this->buffer, 0x00, this->length);

		this->position = 0;
	}

	void Packet::close() {
		free(this->buffer);
		this->length = 0;
		this->position = 0;
	}

	Packet::~Packet() {
		this->close();
	}
}