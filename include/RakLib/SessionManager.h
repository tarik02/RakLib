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

#ifndef ISESSION_MANAGER_H_
#define ISESSION_MANAGER_H_

#include <string>

namespace RakLib
{
	class Session;

	class SessionManager
	{
	public:

		virtual bool addSession(std::string ip, unsigned short port, long clientID, unsigned short mtu) = 0;

		virtual bool removeSession(std::string ip, unsigned short port) = 0;

		virtual Session* getSession(std::string ip, unsigned short port) = 0;

	};
}

#endif