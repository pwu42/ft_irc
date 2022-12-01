#include "Server.hpp"

static bool isvalidchan(const std::string & user)
{
	if ((user.c_str())[0] != '!' &&
		(user.c_str())[0] != '+' &&
		(user.c_str())[0] != '#' &&
		(user.c_str())[0] != '&')
	{
		return (false);
	}
	if (std::strcspn(user.c_str(), "\7 ,:") != user.size())
	{
		return (false);
	}
	return (true);
}

static bool channelExist(const std::map<std::string , Channel *> & _channels, const std::string & channelName)
{
	for (std::map<std::string, Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); it++)
		if (caseInsensEqual(channelName, it->first))
			return true;
	return false;
}

void Server::cmdJoin(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
	{
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
		return ;
	}
	if (!isvalidchan(message.getParams()[0]))
	{
		message.addReply(':' + hostname + ' ' + ERR_BADCHANMASK + ' ' + message.getParams()[0] + ' ' + replies[ERR_BADCHANMASK], sender);
		return ;
	}
	if (!channelExist(_channels, message.getParams()[0]))
		addNewChannel(message.getParams()[0], sender);
	sender->addChannel(message.getParams()[0]);
	(_channels[(message.getParams()[0])])->addClient(sender);
	if (((_channels[(message.getParams()[0])])->getTopic()).empty())
		message.addReply(':' + hostname + ' ' + RPL_NOTOPIC + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[RPL_NOTOPIC], sender);
	else
	{
		message.addReply(':' + hostname + ' ' + RPL_TOPIC + ' ' + sender->getNick() + ' ' + message.getParams()[0] + " :" + ((_channels[(message.getParams()[0])])->getTopic()) + "\r\n", sender);
		// RPL_TOPIC (332)
		message.addReply(':' + hostname + ' ' + RPL_TOPICWHOTIME + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + ((_channels[(message.getParams()[0])])->getTopicOps()) + ' ' + ((_channels[(message.getParams()[0])])->getTopicSetat()) + "\r\n", sender);
		// RPL_TOPICWHOTIME (333)
	}
	// see like a call to names
	// RPL_NAMREPLY (353)
	// RPL_ENDOFNAMES (366)
}
