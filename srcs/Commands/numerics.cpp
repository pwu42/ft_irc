#include "Commands.hpp"

std::string rpl_welcome(Message msg, User &client) // 001
{
	(void)msg;
	return ("001 " + client.getNick() + " :Welcome to the bIRCher Network, " + client.getNick() + "\r\n");
}
