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

static std::string nickReply(Client * sender, const std::string & newNick, const std::string & hostname)
{
	std::string reply;

	if (sender->getStatus() & CLIENT_HAS_NICK)
	{
		reply += ":" + sender->getNick();
		if (sender->getStatus() & CLIENT_HAS_USER)
			reply += "!" + sender->getUser() + "@" + hostname;
		reply += " NICK " + newNick + "\r\n";
	}
	sender->setNick(newNick);
	return reply;
}

void Server::cmdNick(Client * sender, SplitMsg & message)
{
	if ((sender->getStatus() & CLIENT_HAS_PASS) == 0)
		message.setReply(':' + hostname + ' ' + ERR_NOTREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_NOTREGISTERED], TARGET_SENDER);
	else if (message.getParams().size() < 1)
		message.setReply(':' + hostname + ' ' + ERR_NONICKNAMEGIVEN + ' ' + sender->getNick() + ' ' + replies[ERR_NONICKNAMEGIVEN], TARGET_SENDER);
	else if (nickIsValid(message.getParams()[0]) == false)
		message.setReply(':' + hostname + ' ' + ERR_ERRONEUSNICKNAME + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_ERRONEUSNICKNAME], TARGET_SENDER);
	else if (nickExists(clients, message.getParams()[0]) == true)
		message.setReply(':' + hostname + ' ' + ERR_NICKNAMEINUSE + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_NICKNAMEINUSE], TARGET_SENDER);
	else
		message.setReply(nickReply(sender, message.getParams()[0], hostname), TARGET_ALL);
}
