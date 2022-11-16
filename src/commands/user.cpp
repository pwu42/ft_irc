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
		message.setReply(':' + hostname + ' ' + ERR_NOTREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_NOTREGISTERED], TARGET_SENDER);
	else if (sender->getStatus() & CLIENT_HAS_USER)
		message.setReply(':' + hostname + ' ' + ERR_ALREADYREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_ALREADYREGISTERED], TARGET_SENDER);
	else if (message.getParams().size() < 4 || message.getParams()[0].length() < 1)
		message.setReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], TARGET_SENDER);
	else if (userIsValid(message.getParams()[0]) == false)
		message.setReply(':' + hostname + ' ' + ERR_ERRONEUSNICKNAME + ' ' + sender->getNick() + ' ' + replies[ERR_ERRONEUSNICKNAME], TARGET_SENDER);
	else
		sender->setUser(message.getParams()[0], message.getParams()[3]);
}