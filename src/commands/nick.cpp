#include "Server.hpp"

static bool nickIsValid(const std::string & nick)
{
	if (nick.length() > 9 || nick.length() < 1
		|| (!isalpha(nick[0]) && nick.find_first_not_of(SPECIAL, 0, 1) != std::string::npos)
		|| nick.find_first_not_of(ALNUMSPHY, 1) != std::string::npos)
		return false;
	return true;
}

static bool nickExists(const std::map<int, Client *> & clients, const std::string & nick)
{
	for (std::map<int, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++)
		if (caseInsensEqual(nick, it->second->getNick()))
			return true;
	return false;
}

static std::string nickReply(Client * sender, const std::string & newNick)
{
	std::string reply;

	if (sender->getStatus() & CLIENT_HAS_NICK)
		reply += ":" + sender->getFullName() + " NICK " + newNick + "\r\n";
	sender->setNick(newNick);
	return reply;
}

void Server::cmdNick(Client * sender, SplitMsg & message)
{
	if ((sender->getStatus() & CLIENT_HAS_PASS) == 0)
		message.addReply(':' + hostname + ' ' + ERR_NOTREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_NOTREGISTERED], sender);
	else if (message.getParams().size() < 1)
		message.addReply(':' + hostname + ' ' + ERR_NONICKNAMEGIVEN + ' ' + sender->getNick() + ' ' + replies[ERR_NONICKNAMEGIVEN], sender);
	else if (nickIsValid(message.getParams()[0]) == false)
		message.addReply(':' + hostname + ' ' + ERR_ERRONEUSNICKNAME + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_ERRONEUSNICKNAME], sender);
	else if (nickExists(clients, message.getParams()[0]) == true)
		message.addReply(':' + hostname + ' ' + ERR_NICKNAMEINUSE + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_NICKNAMEINUSE], sender);
	else
		message.addReply(nickReply(sender, message.getParams()[0]), NULL);
	if (sender->getStatus() == 7)
		welcome(sender, message);
}
