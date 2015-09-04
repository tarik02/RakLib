#ifndef ISESSION_MANAGER_H_
#define ISESSION_MANAGER_H_

#include <string>

namespace RakLib
{
	class Session;

	class SessionManager
	{
	public:

		virtual bool addSession(const std::string& ip, uint16_t port, long clientID, short mtu) = 0;

		virtual bool removeSession(const std::string& ip, uint16_t port) = 0;

		virtual Session* getSession(const std::string& ip, uint16_t port) = 0;

	};
}

#endif