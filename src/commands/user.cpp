#include "Server.hpp"

void Server::cmdUser(Client * sender, std::vector<std::string> & params)
{
	if ((sender->getStatus() & CLIENT_HAS_PASS) == 0)
		sendNumeric(sender, ERR_NOTREGISTERED);
	else if ((sender->getStatus() & CLIENT_HAS_USER) != 0)
		sendNumeric(sender, ERR_ALREADYREGISTERED);
	else if (params.size() < 1 || params[0].size() == 0)
		sendNumeric(sender, ERR_NEEDMOREPARAMS);
}