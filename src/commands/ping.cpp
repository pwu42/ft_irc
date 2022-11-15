#include "Server.hpp"

void pingReply(int fd, const std::string & hostname)
{
	std::string reply = "PONG " + hostname + "\r\n";

	send(fd, reply.c_str(), reply.length(), 0);
}

void Server::cmdPing(Client * sender, const std::vector<std::string> & params)
{
	if (params.size() < 1)
		sendNumeric(sender, ERR_NEEDMOREPARAMS);
	else if (params[0] != hostname && params[0] != ip)
		sendNumeric(sender, ERR_NOSUCHSERVER, params[0]);
	else
		pingReply(sender->getSock(), hostname);
}