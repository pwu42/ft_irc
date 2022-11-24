#include "Server.hpp"

static bool userIsValid(const std::string & user)
{
	if (user.find_first_of(NULSPCRLFAT) != std::string::npos)
		return false;
	return true;
}

void Server::cmdUser(Client * sender, SplitMsg & message)
{
	if (!(sender->getStatus() & CLIENT_HAS_PASS))
		message.addReply(':' + hostname + ' ' + ERR_NOTREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_NOTREGISTERED], sender);
	else if (sender->getStatus() & CLIENT_HAS_USER)
		message.addReply(':' + hostname + ' ' + ERR_ALREADYREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_ALREADYREGISTERED], sender);
	else if (message.getParams().size() < 4 || message.getParams()[0].length() < 1)
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
	else if (userIsValid(message.getParams()[0]) == false)
		message.addReply(':' + hostname + ' ' + ERR_ERRONEUSNICKNAME + ' ' + sender->getNick() + ' ' + replies[ERR_ERRONEUSNICKNAME], sender);
	else
		sender->setUser(message.getParams()[0], hostname);
	if (sender->getStatus() == 7)
		welcome(sender, message);
}