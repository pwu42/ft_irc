#include "Server.hpp"

static bool channelExist(const std::map<std::string , Channel *> & _channels, const std::string & channelName)
{
	for (std::map<std::string, Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); it++)
		if (caseInsensEqual(channelName, it->first))
			return true;
	return false;
}

void Server::cmdPart(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
	{
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
		return ;
	}
	if (!channelExist(_channels, message.getParams()[0]))
	{
		message.addReply(':' + hostname + ' ' + ERR_NOSUCHCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' '  + replies[ERR_NOSUCHCHANNEL], sender);
		return ;
	}
	if (!sender->isIn(message.getParams()[0]))
	{
		message.addReply(':' + hostname + ' ' + ERR_NOTONCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_NOTONCHANNEL], sender);
		return ;
	}
	sender->removeChannel(message.getParams()[0]);
	((_channels[(message.getParams()[0])])->removeClient(sender));
	if (((_channels[(message.getParams()[0])])->empty()))
		deleteChannel(message.getParams()[0]);
}
