#include "Server.hpp"

std::string Server::_cmdUser(Message msg)
{	if ((msg.getArgs()).empty())
		callReply(ERR_NEEDMOREPARAMS, msg);
	return (msg.getReply());
}
