#include "Server.hpp"

void Server::_cmdPass(Message msg)
{
	if (_pass != msg.getArgs())
		msg.setReply("464 "+ _client.getNick() + " :Password incorrect.\r\n");
	msg.setReply("");
}
