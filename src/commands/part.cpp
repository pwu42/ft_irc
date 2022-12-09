#include "Server.hpp"

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
	((_channels[strlower((message.getParams()[0]))])->removeClient(sender));
	_channels[strlower((message.getParams()[0]))]->sendMsg(':' + sender->getFullName() + ' ' + message.getCommand() + " :" + message.getParams()[0] + "\r\n");
	if (((_channels[strlower((message.getParams()[0]))])->empty()))
		deleteChannel(message.getParams()[0]);
}
// sendMsg
