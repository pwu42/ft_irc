#include "Server.hpp"

void Server::cmdList(Client * sender, SplitMsg & message)
{
	message.addReply(':' + hostname + ' ' + RPL_LISTSTART + ' ' + sender->getNick() + ' ' + replies[RPL_LISTSTART], sender);
	if (message.getParams().size() < 1)
	{
		for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
		{
			message.addReply(':' + hostname + ' ' + RPL_LIST + ' ' + sender->getNick() + ' ' + it->first + ' ' + (it->second)->getNumberOfClient() + " :"+ (it->second)->getTopic() + "\r\n", sender);
		}
	}
	else
		message.addReply(':' + hostname + ' ' + RPL_LIST + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' +_channels[strlower(message.getParams()[0])]->getNumberOfClient() + " :" + _channels[strlower(message.getParams()[0])]->getTopic() + "\r\n", sender);

	message.addReply(':' + hostname + ' ' + RPL_LISTEND + ' ' + sender->getNick() + ' ' + replies[RPL_LISTEND], sender);
}
