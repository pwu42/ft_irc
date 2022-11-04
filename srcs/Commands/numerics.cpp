#include "Server.hpp"

void Server::_rpl_welcome(Message msg) // 001
{
	(void)msg;
	msg.setReply("001 " + _client.getNick() + " :Welcome to the bIRCher Network, " + _client.getNick() + "\r\n");
}
