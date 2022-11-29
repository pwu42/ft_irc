#include "Server.hpp"

size_t findIndex(int fd, struct pollfd * fds, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		if (fds[i].fd == fd)
			return i;
	}
	return -1;
}

Client * findbyNick(const std::string & nick, const std::map<int, Client *> & clients)
{
	for (std::map<int, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->getNick() == nick)
			return it->second;
	}
	return NULL;
}