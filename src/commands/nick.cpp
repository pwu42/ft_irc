#include "Server.hpp"

bool nickIsValid(const std::string & nick)
{
	if (nick.length() > 9 || nick.length() < 1
		|| (!isalpha(nick[0]) && nick.find_first_not_of(SPECIAL, 0, 1) != std::string::npos)
		|| nick.find_first_not_of(ALNUMSPHY, 1) != std::string::npos)
		return false;
	return true;
}

bool nickExists(const std::map<int, Client *> & clients, const std::string & nick)
{
	for (std::map<int, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++)
		if (caseInsensEqual(nick, it->second->getNick()))
			return true;
	return false;
}

void nickReply(Client * sender, const std::string & newNick, const std::string & hostname)
{
	std::string reply;

	if (sender->getStatus() & CLIENT_HAS_NICK)
	{
		reply += ":" + sender->getNick();
		if (sender->getStatus() & CLIENT_HAS_USER)
			reply += "!" + sender->getUser() + "@" + hostname;
		reply += " NICK " + newNick + "\r\n";
		send(sender->getSock(), reply.c_str(), reply.length(), 0);
	}
	sender->setNick(newNick);
}

void Server::cmdNick(Client * sender, const std::vector<std::string> & params)
{
	if ((sender->getStatus() & CLIENT_HAS_PASS) == 0)
		sendNumeric(sender, ERR_NOTREGISTERED);
	else if (params.size() < 1)
		sendNumeric(sender, ERR_NONICKNAMEGIVEN);
	else if (nickIsValid(params[0]) == false)
		sendNumeric(sender, ERR_ERRONEUSNICKNAME, params[0] + " ");
	else if (nickExists(clients, params[0]) == true)
		sendNumeric(sender, ERR_NICKNAMEINUSE, params[0] + " ");
	else
		nickReply(sender, params[0], hostname);
	if (sender->getStatus() == 7)
		welcome(sender);
}
