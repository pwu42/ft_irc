#include "Commands.hpp"

std::string cmdPass(Message msg, User &client)
{
	if (_password != msg.getArgs())
		return ("464 "+ client.getNick() + " :Password incorrect.\r\n");
	return ("");
}
