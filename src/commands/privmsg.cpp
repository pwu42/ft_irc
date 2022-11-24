#include "Server.hpp"

static Client * findbyNick(const std::string & nick, const std::map<int, Client *> & clients)
{
	for (std::map<int, Client *>::const_iterator it = clients.begin(); it != clients.end(); it++)
	{
		if (it->second->getNick() == nick)
			return it->second;
	}
	return NULL;
}

static std::string getTargetClients(const std::string & msg, std::set<IMsgTarget *> & targets, const std::map<int, Client *> & clients)
{
	size_t start = 0, end;
	Client * client = NULL;

	while ((end = msg.find(',', start)) != std::string::npos)
	{
		if (!(client = findbyNick(msg.substr(start, end - start), clients)))
			return msg.substr(start, end - start);
		targets.insert(client);
		start = end + 1;
	}
	if (!(client = findbyNick(msg.substr(start), clients)))
		return msg.substr(start);
	targets.insert(client);
	return "";
}

void Server::cmdPrivmsg(Client * sender, SplitMsg & message)
{
	std::set<IMsgTarget *> targets;
	std::string err;

	if (message.getParams().size() < 1)
		message.addReply(':' + hostname + ' ' + ERR_NORECIPIENT + ' ' + sender->getNick() + ' ' + replies[ERR_NORECIPIENT], sender);
	else if (message.getParams().size() < 2)
		message.addReply(':' + hostname + ' ' + ERR_NOTEXTTOSEND + ' ' + sender->getNick() + ' ' + replies[ERR_NOTEXTTOSEND], sender);
	else if ((err = getTargetClients(message.getParams()[0], targets, clients)) != "") // or channel not found
		message.addReply(':' + hostname + ' ' + ERR_NOSUCHNICK + ' ' + sender->getNick() + ' ' + err + ' ' + replies[ERR_NOSUCHNICK], sender);
	else
		for (std::set<IMsgTarget *>::iterator it = targets.begin(); it != targets.end(); it++)
			message.addReply(':' + sender->getFullName() + " PRIVMSG " + (*it)->getName() + " :" + message.getParams()[1] + "\r\n", *it);
}