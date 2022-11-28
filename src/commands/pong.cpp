#include "Server.hpp"

void Server::cmdPong(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() > 0)
		sender->pong(message.getParams()[0]);
}