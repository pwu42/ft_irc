#include "Server.hpp"

void Server::leaveAllChannels(Client *sender)
{
	std::list<std::string> chanNames = sender->getList();
	for (std::list<std::string>::const_iterator it = chanNames.begin(); it != chanNames.end(); it++)
	{
		_channels[strlower(*it)]->removeClient(sender);
		if (((_channels[strlower(*it)])->empty()))
			deleteChannel(strlower(*it));
	}
	sender->leaveAllChannels();
}


void Server::cmdQuit(Client * sender, SplitMsg & message)
{
	std::string reply = ':' + sender->getNick() + '!' + sender->getUser() + '@' + hostname + " QUIT :Quit: ";
	if (message.getParams().size() > 0)
		reply += message.getParams()[0];
	reply += "\r\n";
	message.addReply(reply, NULL);
	leaveAllChannels(sender);
	sender->addStatus(CLIENT_HAS_QUIT);
}

// when quit quit all chann
