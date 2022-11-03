#include "Server.hpp"

std::string Server::_cmdUser(Message msg)
{
	return (msg.getReply());
}
