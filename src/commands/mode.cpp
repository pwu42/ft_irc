#include "Server.hpp"

void Server::channelMode(Client * sender, SplitMsg & message)
{
	Client *to_mode;
	if (!channelExist(_channels, message.getParams()[0]))
	{
		message.addReply(':' + hostname + ' ' + ERR_NOSUCHCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' '  + replies[ERR_NOSUCHCHANNEL], sender);
	}
	else if (message.getParams().size() == 1)
	{
		message.addReply(':' + hostname + ' ' + RPL_CHANNELMODEIS + ' ' + sender->getNick() + ' ' + message.getParams()[0] + " +-o O" + " userNick\r\n" , sender);
	}
	else if (message.getParams()[1] != "O")
	{
		if (!(_channels[strlower(message.getParams()[0])]->getCreator()))
			message.addReply(':' + hostname + ' ' + sender->getNick() + ' ' + message.getParams()[0] + " :Creator has leave the channel\r\n", sender);
		else
			message.addReply(':' + hostname + ' ' + sender->getNick() + ' ' + message.getParams()[0] + " :" + (_channels[strlower(message.getParams()[0])]->getCreator())->getNick() + "\r\n", sender);
	}
	else if (!(_channels[strlower(message.getParams()[0])]->clientIsOp(sender->getSock())))
		message.addReply(':' + hostname + ' ' + ERR_CHANOPRIVSNEEDED + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_CHANOPRIVSNEEDED], sender);
	else if (message.getParams().size() < 3)
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
	else if (message.getParams()[1] != "+o")
	{
		if (!(to_mode = _channels[strlower((message.getParams()[0]))]->isIn(message.getParams()[2])))
			message.addReply(':' + hostname + ' ' + ERR_USERNOTINCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_USERNOTINCHANNEL], sender);
		else
		{
			_channels[strlower((message.getParams()[0]))]->addOper(to_mode);
			_channels[strlower((message.getParams()[0]))]->sendMsg(':' + sender->getNick() + '!' + sender->getUser() + '@' + hostname + " MODE +o " + message.getParams()[2] + "\r\n");
		}
	}
	else if (message.getParams()[1] != "-o")
	{
		if (!(to_mode = _channels[strlower((message.getParams()[0]))]->isIn(message.getParams()[2])))
			message.addReply(':' + hostname + ' ' + ERR_USERNOTINCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_USERNOTINCHANNEL], sender);
		else
		{
			_channels[strlower((message.getParams()[0]))]->removeOper(to_mode);
			_channels[strlower((message.getParams()[0]))]->sendMsg(':' + sender->getNick() + '!' + sender->getUser() + '@' + hostname + " MODE -o " + message.getParams()[2] + "\r\n");
		}
	}
	else
		message.addReply(':' + hostname + ' ' + ERR_UMODEUNKNOWNFLAG + ' ' + sender->getNick() + ' ' + replies[ERR_UMODEUNKNOWNFLAG], sender);
	return ;

}

void Server::userMode(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() == 1)
		message.addReply(':' + hostname + ' ' + RPL_UMODEIS + ' ' + sender->getNick() + ' ' + sender->getMode() + "\r\n", sender);
	else if (message.getParams()[1] == "-o")
	{
		sender->removeStatus(CLIENT_OPERATOR);
		message.addReply("MODE " + sender->getNick() + " -o\r\n", sender);
	}
	else if (message.getParams()[1] != "+o")
		message.addReply(':' + hostname + ' ' + ERR_UMODEUNKNOWNFLAG + ' ' + sender->getNick() + ' ' + replies[ERR_UMODEUNKNOWNFLAG], sender);
}

void Server::cmdMode(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
	{
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
	}
	else if ((message.getParams()[0].find_first_not_of("&#+!", 0, 1)) != std::string::npos)
		channelMode(sender, message);
	else if (message.getParams()[0] == sender->getNick())
		userMode(sender, message);
	else
		message.addReply(':' + hostname + ' ' + ERR_USERSDONTMATCH + ' ' + sender->getNick() + ' ' + replies[ERR_USERSDONTMATCH], sender);
}
