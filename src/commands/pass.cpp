#include "Server.hpp"

void Server::cmdPass(Client * sender, SplitMsg & message)
{
	if (sender->getStatus() & CLIENT_HAS_PASS)
		message.addReply(':' + hostname + ' ' + ERR_ALREADYREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_ALREADYREGISTERED], sender);
	else if (message.getParams().size() < 1)
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
	else if (message.getParams()[0] != pass)
		message.addReply(':' + hostname + ' ' + ERR_PASSWDMISMATCH + ' ' + sender->getNick() + ' ' + replies[ERR_PASSWDMISMATCH], sender);
	else
		sender->setPass();
}