#include "Server.hpp"

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
	else if (!(_channels[strlower(message.getParams()[0])]->clientIsOp(sender->getSock())))
		message.addReply(':' + hostname + ' ' + ERR_CHANOPRIVSNEEDED + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_CHANOPRIVSNEEDED], sender);
	else
	{
		(_channels[strlower((message.getParams()[0]))])->setTopic((message.getParams()[1]), sender);
		_channels[strlower((message.getParams()[0]))]->sendMsg(':' + sender->getNick() + '!' + sender->getUser() + '@' + hostname + ' ' + message.getCommand() + ' ' + message.getParams()[0] + " :" + (message.getParams()[1]) + "\r\n");
	}
}
