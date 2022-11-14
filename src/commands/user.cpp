#include "Server.hpp"

bool userIsValid(const std::string & user)
{
	if (user.find_first_of(NULSPCRLFAT) != std::string::npos)
		return false;
	return true;
}

void Server::cmdUser(Client * sender, const std::vector<std::string> & params)
{
	if (!(sender->getStatus() & CLIENT_HAS_PASS))
		sendNumeric(sender, ERR_NOTREGISTERED);
	else if (sender->getStatus() & CLIENT_HAS_USER)
		sendNumeric(sender, ERR_ALREADYREGISTERED);
	else if (params.size() < 4 || params[0].length() < 1)
		sendNumeric(sender, ERR_NEEDMOREPARAMS);
	else if (userIsValid(params[0]) == false)
		sendNumeric(sender, ERR_ERRONEUSNICKNAME);
	else
		sender->setUser(params[0], params[3]);
	if (sender->getStatus() == 7)
		welcome(sender);
}