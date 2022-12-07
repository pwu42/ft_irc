#include "Server.hpp"

static bool channelExist(const std::map<std::string , Channel *> & _channels, const std::string & channelName)
{
	for (std::map<std::string, Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); it++)
		if (caseInsensEqual(channelName, it->first))
			return true;
	return false;
}

void Server::cmdTopic(Client * sender, SplitMsg & message)
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

	if (message.getParams().size() == 1)
	{
		if (((_channels[strlower((message.getParams()[0]))])->getTopic()).empty())
			message.addReply(':' + hostname + ' ' + RPL_NOTOPIC + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[RPL_NOTOPIC], sender);
		else
		{
			message.addReply(':' + hostname + ' ' + RPL_TOPIC + ' ' + sender->getNick() + ' ' + message.getParams()[0] + " :" + ((_channels[strlower((message.getParams()[0]))])->getTopic()) + "\r\n", sender);
			message.addReply(':' + hostname + ' ' + RPL_TOPICWHOTIME + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + ((_channels[strlower((message.getParams()[0]))])->getTopicOps()) + ' ' + ((_channels[strlower((message.getParams()[0]))])->getTopicSetat()) + "\r\n", sender);
		}
	}
	else
	{
		(_channels[strlower((message.getParams()[0]))])->setTopic((message.getParams()[1]), sender);
		// sendall
		message.addReply(':' + sender->getNick() + ' ' + message.getCommand() + ' ' + message.getParams()[0] + " :" + ((_channels[(message.getParams()[0])])->getTopic()) + "\r\n", sender);
	}

}
