#include "Server.hpp"

IMsgTarget * Server::findTarget(const std::string & nick)
{
	for (std::map<int, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (caseInsensEqual(nick, it->second->getName()))
			return it->second;
	}
	for (std::map<std::string, Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		if (caseInsensEqual(nick, it->first))
			return it->second;
	}
	return NULL;
}