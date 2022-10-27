#include "Server.hpp"

void Server::cmdPass(Client * sender, std::vector<std::string> & params)
{
	if (sender->getStatus() & CLIENT_HAS_PASS)
		sendNumeric(sender->getSock(), ERR_ALREADYREGISTERED);
	else if (params.size() < 1)
		sendNumeric(sender->getSock(), ERR_NEEDMOREPARAMS, "PASS ");
	else if (params[0] != std::string(pass))
		sendNumeric(sender->getSock(), ERR_PASSWDMISMATCH);
	else
		sender->setPass();
}