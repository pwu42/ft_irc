#include "Server.hpp"

Client * findNick(const std::string & nick, const std::map<int, Client *> & clients)
{
	for (std::map<int, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->getNick() == nick)
			return it->second;
	}
	return NULL;
}

void Server::cmdPrivmsg(Client * sender, SplitMsg & message)
{
	Client * target = NULL;
	if (message.getParams().size() < 1)
		message.addReply(':' + hostname + ' ' + ERR_NORECIPIENT + ' ' + sender->getNick() + ' ' + replies[ERR_NORECIPIENT], sender);
	else if ((target = findNick(message.getParams()[0], clients)) == NULL) // or channel not found
		message.addReply(':' + hostname + ' ' + ERR_NOSUCHNICK + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_NOSUCHNICK], sender);
	else if (message.getParams().size() < 2)
		message.addReply(':' + hostname + ' ' + ERR_NOTEXTTOSEND + ' ' + sender->getNick() + ' ' + replies[ERR_NOTEXTTOSEND], sender);
	else
		message.addReply(':' + sender->getFullName() + " PRIVMSG " + target->getNick() + " :" + message.getParams()[1] + "\r\n", target);
}