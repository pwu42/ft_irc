#include "Server.hpp"

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
	if (!(_channels[strlower(message.getParams()[0])]->clientIsOp(sender->getSock())))
	{
		message.addReply(':' + hostname + ' ' + ERR_CHANOPRIVSNEEDED + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_CHANOPRIVSNEEDED], sender);
		return ;
	}
	if (!(to_kick = _channels[strlower((message.getParams()[0]))]->isIn(message.getParams()[1])))
	{
		message.addReply(':' + hostname + ' ' + ERR_USERNOTINCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_USERNOTINCHANNEL], sender);
		return ;
	}
	to_kick->removeChannel(message.getParams()[0]);
	_channels[strlower((message.getParams()[0]))]->removeClient(to_kick);
	if (message.getParams().size() < 3)
		message.addReply(':' + hostname + ' '  + sender->getNick() + ' ' + message.getParams()[0] + ' ' + "automatic message after kick\r\n", sender);
	else
		message.addReply(':' + hostname + ' ' + ERR_USERNOTINCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + message.getParams()[2] + "\r\n", sender);
}

// sendAll
