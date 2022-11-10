# include "Server.hpp"

void Server::_cmdPing(Message &msg)
{
	if ((msg.getArgs()).empty())
		callReply(ERR_NEEDMOREPARAMS, msg);
	else
		msg.setReply("PONG " + (msg.getArgs())[0] + "\r\n");
}
// done
