#include "Server.hpp"

void Server::clientDisconnect(Client * target, const std::string & quitMsg)
{
	SplitMsg msg(quitMsg);
	cmdQuit(target, msg);
	reply(target, msg);
}

void Server::pingClients()
{
	time_t t;

	time(&t);
	if (t - lastPing > POLL_TIMEOUT)
	{
		for (size_t i = 1; i < fdCount; i++)
		{
			if ((clients[fds[i].fd]->getStatus() & CLIENT_PING) || !(clients[fds[i].fd]->getStatus() & CLIENT_REGISTER))
				deleteClient(i, "QUIT :Connection timeout\r\n");
			else
				clients[fds[i].fd]->ping(hostname);
		}
		lastPing = t;
	}
}