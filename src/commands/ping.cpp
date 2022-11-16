#include "Server.hpp"

void Server::cmdPing(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
		message.setReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], TARGET_SENDER);
	else if (message.getParams()[0] != hostname && message.getParams()[0] != ip)
		message.setReply(':' + hostname + ' ' + ERR_NOSUCHSERVER + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_NOSUCHSERVER], TARGET_SENDER);
	else
		message.setReply("PONG " + hostname + "\r\n", TARGET_SENDER);
}