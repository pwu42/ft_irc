#include "Server.hpp"

void Server::cmdKill(Client * sender, SplitMsg & message)
{
	Client * target = NULL;

	if ((sender->getStatus() & CLIENT_OPERATOR) == 0)
		message.addReply(':' + hostname + ' ' + ERR_NOPRIVILEGES + ' ' + sender->getNick() + ' ' + replies[ERR_NOPRIVILEGES], sender);
	else if (message.getParams().size() < 2)
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
	else if (!(target = dynamic_cast<Client *>(findTarget(message.getParams()[0]))))
		message.addReply(':' + hostname + ' ' + ERR_NOSUCHNICK + ' ' + sender->getNick() + ' ' + replies[ERR_NOSUCHNICK], sender);
	else if (!(target->getStatus() & CLIENT_OPERATOR))
	{
		message.getParams()[0] = "Killed (" + sender->getName() + " (" + message.getParams()[1] + "))\r\n";
		cmdQuit(sender, message);
	}
}