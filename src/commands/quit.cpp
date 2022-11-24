#include "Server.hpp"

void Server::cmdQuit(Client * sender, SplitMsg & message)
{
	std::string reply = ':' + sender->getNick() + '!' + sender->getUser() + '@' + hostname + " QUIT :Quit: ";
	if (message.getParams().size() > 0)
		reply += message.getParams()[0];
	reply += "\r\n";
	message.addReply(reply, NULL);
	sender->quit();
}
