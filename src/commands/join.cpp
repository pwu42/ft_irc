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
	if (user.size() > 50 || std::strcspn(user.c_str(), "\7 ,:") != user.size())
	{
		return (false);
	}
	return (true);
}

void Server::cmdJoin(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
	{
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
		return ;
	}
	if (sender->isIn(message.getParams()[0]))
		return ;
	if (!isvalidchan(message.getParams()[0]))
	{
		message.addReply(':' + hostname + ' ' + ERR_BADCHANMASK + ' ' + message.getParams()[0] + ' ' + replies[ERR_BADCHANMASK], sender);
		return ;
	}
	if (!channelExist(_channels, message.getParams()[0]))
		addNewChannel(message.getParams()[0], sender);
	sender->addChannel(message.getParams()[0]);
	(_channels[strlower((message.getParams()[0]))])->addClient(sender);
	if (((_channels[strlower((message.getParams()[0]))])->getTopic()).empty())
		message.addReply(':' + hostname + ' ' + RPL_NOTOPIC + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[RPL_NOTOPIC], sender);
	else
	{
		message.addReply(':' + hostname + ' ' + RPL_TOPIC + ' ' + sender->getNick() + ' ' + message.getParams()[0] + " :" + ((_channels[strlower((message.getParams()[0]))])->getTopic()) + "\r\n", sender);
		message.addReply(':' + hostname + ' ' + RPL_TOPICWHOTIME + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + ((_channels[strlower((message.getParams()[0]))])->getTopicOps()) + ' ' + ((_channels[strlower((message.getParams()[0]))])->getTopicSetat()) + "\r\n", sender);
	}
	cmdNames(sender, message);
}
// sendall
