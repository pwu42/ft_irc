#include "Server.hpp"

void Server::cmdPass(Client * sender, std::vector<std::string> & params)
{
	if (sender->getStatus() & CLIENT_HAS_PASS)
		sendNumeric(sender, ERR_ALREADYREGISTERED);
	else if (params.size() < 1 || params[0] != std::string(pass))
		sendNumeric(sender, ERR_PASSWDMISMATCH);
	else
		sender->setPass();
}