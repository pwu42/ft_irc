#include "Server.hpp"

void Server::cmdPass(Client * sender, SplitMsg & message)
{
	if (sender->getStatus() & CLIENT_HAS_PASS)
		message.setReply(':' + hostname + ' ' + ERR_ALREADYREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_ALREADYREGISTERED], TARGET_SENDER);
	else if (message.getParams().size() < 1)
		message.setReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], TARGET_SENDER);
	else if (message.getParams()[0] != pass)
		message.setReply(':' + hostname + ' ' + ERR_PASSWDMISMATCH + ' ' + sender->getNick() + ' ' + replies[ERR_PASSWDMISMATCH], TARGET_SENDER);
	else
		sender->setPass();
}