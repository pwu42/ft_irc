#include "Server.hpp"

void Server::cmdMode(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
	else if (message.getParams()[0] != sender->getNick())
		message.addReply(':' + hostname + ' ' + ERR_USERSDONTMATCH + ' ' + sender->getNick() + ' ' + replies[ERR_USERSDONTMATCH], sender);
	else if (message.getParams().size() == 1)
		message.addReply(':' + hostname + ' ' + RPL_UMODEIS + ' ' + sender->getNick() + ' ' + sender->getIsOper(), sender);
	else if (message.getParams()[1] == "-O")
	{
		sender->removeOper();
		message.addReply("MODE " + sender->getNick() + " -O\r\n", sender);
	}
	else if (message.getParams()[1] == "+O")
		;
	else
		message.addReply(':' + hostname + ' ' + ERR_UMODEUNKNOWNFLAG + ' ' + sender->getNick() + ' ' + replies[ERR_UMODEUNKNOWNFLAG], sender);
}
