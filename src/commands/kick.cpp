#include "Server.hpp"

static bool channelExist(const std::map<std::string , Channel *> & _channels, const std::string & channelName)
{
	for (std::map<std::string, Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); it++)
		if (caseInsensEqual(channelName, it->first))
			return true;
	return false;
}

void Server::cmdKick(Client * sender, SplitMsg & message)
{
	Client *to_kick = NULL;
	if (message.getParams().size() < 2)
	{
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
		return ;
	}
	else if (!channelExist(_channels, message.getParams()[0]))
	{
		message.addReply(':' + hostname + ' ' + ERR_NOSUCHCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' '  + replies[ERR_NOSUCHCHANNEL], sender);
		return ;
	}
	else if (!sender->isIn(message.getParams()[0]))
	{
		message.addReply(':' + hostname + ' ' + ERR_NOTONCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_NOTONCHANNEL], sender);
		return ;
	}
	if (!(_channels[strlower((message.getParams()[0]))])->clientIsOp(sender->getSock())))
	{
		message.addReply(':' + hostname + ' ' + ERR_CHANOPRIVSNEEDED + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_CHANOPRIVSNEEDED], sender);
		return ;
	}
	if (!(to_kick = _channels[strlower((message.getParams()[0]))]->isIn(message.getParams()[1])))
	{
		// if () pas param 1 dans chan alors return ERR_USERNOTINCHANNEL
		message.addReply(':' + hostname + ' ' + ERR_USERNOTINCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_USERNOTINCHANNEL], sender);
		return ;
	}
	// remove chan param 1  et remove client de chan ;
	to_kick->removeChannel(message.getParams()[0]);
	_channels[strlower((message.getParams()[0]))]->removeClient(to_kick);
	if (message.getParams().size() < 3) ;
		// message.addReply(':' + hostname + ' ' + ERR_USERNOTINCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_USERNOTINCHANNEL], sender);
	else ;
		// message.addReply(':' + hostname + ' ' + ERR_USERNOTINCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_USERNOTINCHANNEL], sender);
	// sendAll
}
