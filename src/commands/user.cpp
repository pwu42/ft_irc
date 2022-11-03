#include "Server.hpp"

void Server::cmdUser(Client * sender, std::vector<std::string> & params)
{
	if ((sender->getStatus() & CLIENT_HAS_PASS) == 0)
		sendNumeric(sender, ERR_NOTREGISTERED);
	else if ((sender->getStatus() & 7) == 7)
		sendNumeric(sender, ERR_ALREADYREGISTERED);
	else if (params.size() < 4 || params[0].size() == 0)
		sendNumeric(sender, ERR_NEEDMOREPARAMS);
	else
		sender->setUser(params[0], params[3]);
	if (sender->getStatus() == 7)
		welcome(sender);
}