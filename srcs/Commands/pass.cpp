# include "Server.hpp"

void Server::_cmdPass(Message &msg)
{
	// std::cout << "\"" <<(msg.getArgs())[0] << "\"" << '\n';
	// std::cout << "\"" << _pass << "\"" << '\n';
	//
	// std::cout << "\"" << (_pass != (msg.getArgs())[0]) << "\"" << '\n';
	if ((msg.getArgs()).empty() || _pass != (msg.getArgs())[0])
		msg.setReply("464 "+ _client.getNick() + " :Password incorrect.\r\n");
	else
		msg.setReply("");
}
