#include "Server.hpp"

static size_t findIndex(int fd, struct pollfd * fds, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		if (fds[i].fd == fd)
			return i;
	}
	return -1;
}

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
		// leaveAllChannels(sender);
		deleteClient(findIndex(target->getSock(), fds, fdCount), "QUIT :Killed (" + sender->getName() + " (" + message.getParams()[1] + "))\r\n");
	}
}
// quit all chan before
