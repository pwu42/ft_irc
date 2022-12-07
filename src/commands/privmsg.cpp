#include "Server.hpp"

void Server::cmdPrivmsg(Client * sender, SplitMsg & message)
{
	IMsgTarget * target;

	if (message.getParams().size() < 1)
		message.addReply(':' + hostname + ' ' + ERR_NORECIPIENT + ' ' + sender->getNick() + ' ' + replies[ERR_NORECIPIENT], sender);
	else if (message.getParams().size() < 2)
		message.addReply(':' + hostname + ' ' + ERR_NOTEXTTOSEND + ' ' + sender->getNick() + ' ' + replies[ERR_NOTEXTTOSEND], sender);
	else if (!(target = findTarget(message.getParams()[0])))
		message.addReply(':' + hostname + ' ' + ERR_NOSUCHNICK + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_NOSUCHNICK], sender);
	else // send to client/channel
		message.addReply(':' + sender->getFullName() + ' ' + message.getCommand() + ' ' + target->getName() + " :" + message.getParams()[1] + "\r\n", target);
}