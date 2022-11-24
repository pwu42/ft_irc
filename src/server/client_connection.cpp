#include "Server.hpp"

void Server::clientDisconnect(Client * target)
{
	SplitMsg msg("QUIT :Connection lost\r\n");
	cmdQuit(target, msg);
	reply(msg);
}

void Server::pingClients()
{
	time_t t;

	time(&t);
	if (t - lastPing > POLL_TIMEOUT)
	{
		for (size_t i = 1; i < fdCount; i++)
		{
			if (clients[fds[i].fd]->getStatus() & CLIENT_PING)
				deleteClient(i);
			else
				clients[fds[i].fd]->ping(hostname);
		}
		lastPing = t;
	}
}