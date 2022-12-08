#include "Server.hpp"

void Server::channelMode(Client * sender, SplitMsg & message)
{
	(void)sender;
	(void)message;
	//implement +-o, ignore +-O
}

void Server::userMode(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() == 1)
		message.addReply(':' + hostname + ' ' + RPL_UMODEIS + ' ' + sender->getNick() + ' ' + sender->getMode() + "\r\n", sender);
	else if (message.getParams()[1] == "-o")
	{
		sender->removeStatus(CLIENT_OPERATOR);
		message.addReply("MODE " + sender->getNick() + " -o\r\n", sender);
	}
	else if (message.getParams()[1] != "+o")
		message.addReply(':' + hostname + ' ' + ERR_UMODEUNKNOWNFLAG + ' ' + sender->getNick() + ' ' + replies[ERR_UMODEUNKNOWNFLAG], sender);
}

void Server::cmdMode(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
	else if (message.getParams()[0].find("&#+!", 0) == 0)
		channelMode(sender, message);
	else if (message.getParams()[0] == sender->getNick())
		userMode(sender, message);
	else
		message.addReply(':' + hostname + ' ' + ERR_USERSDONTMATCH + ' ' + sender->getNick() + ' ' + replies[ERR_USERSDONTMATCH], sender);
}

// add mode 
