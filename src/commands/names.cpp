#include "Server.hpp"

static bool channelExist(const std::map<std::string , Channel *> & _channels, const std::string & channelName)
{
	for (std::map<std::string, Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); it++)
		if (caseInsensEqual(channelName, it->first))
			return true;
	return false;
}

void Server::cmdNames(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
	{
		message.addReply(':' + hostname + ' ' + RPL_ENDOFNAMES + ' ' + sender->getNick() + ' ' + + ' ' + replies[RPL_ENDOFNAMES], sender);
		return;
	}
	if (channelExist(_channels, message.getParams()[0]))
		message.addReply(':' + hostname + ' ' + RPL_NAMREPLY + ' ' + sender->getNick() + " = " + _channels[strtolower(message.getParams()[0])]->clientsNames(), sender);
	message.addReply(':' + hostname + ' ' + RPL_ENDOFNAMES + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[RPL_ENDOFNAMES], sender);

}
