#include "Server.hpp"

void Server::cmdNames(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
	{
		message.addReply(':' + hostname + ' ' + RPL_ENDOFNAMES + ' ' + sender->getNick() + ' ' + ' ' + replies[RPL_ENDOFNAMES], sender);
		return;
	}
	if (channelExist(_channels, message.getParams()[0]))
		message.addReply(':' + hostname + ' ' + RPL_NAMREPLY + ' ' + sender->getNick() + " = " + _channels[strlower(message.getParams()[0])]->clientsNames() + "\r\n", sender);
	message.addReply(':' + hostname + ' ' + RPL_ENDOFNAMES + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[RPL_ENDOFNAMES], sender);
}
