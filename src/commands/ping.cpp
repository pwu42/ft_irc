#include "Server.hpp"

void Server::cmdPing(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
	else
		message.addReply("PONG " + hostname + ' ' + message.getParams()[0] + "\r\n", sender);
}