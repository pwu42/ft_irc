#include "Server.hpp"

void Server::cmdPong(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() > 0 && message.getParams()[0] == sender->getPingToken())
		sender->pong();
}