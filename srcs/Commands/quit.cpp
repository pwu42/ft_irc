# include "Server.hpp"

// in progress check post multi client


void Server::_cmdQuit(Message &msg)
{
	if ((msg.getArgs()).empty())
		msg.setReply("Quit :");
	else
		msg.setReply("Quit : " + (msg.getArgs())[0]);
	_client.addStatus(CLIENT_HAS_LEFT);
	close(_client.getSock());
	_client.setSock(-1);
}
