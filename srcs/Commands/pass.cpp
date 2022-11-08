# include "Server.hpp"

void Server::_cmdPass(Message &msg)
{
	// std::cout << "\"" <<(msg.getArgs())[0] << "\"" << '\n';
	// std::cout << "\"" << _pass << "\"" << '\n';
	//
	// std::cout << "\"" << (_pass != (msg.getArgs())[0]) << "\"" << '\n';
	if ((msg.getArgs()).empty())
		callReply(ERR_NEEDMOREPARAMS, msg);
	else if (_pass != (msg.getArgs())[0])
		callReply(ERR_PASSWDMISMATCH, msg);
	else if (_client.getStatus() & CLIENT_HAS_PASS)
		callReply(ERR_ALREADYREGISTERED, msg);
	else
	{
		msg.setReply("");
		_client.addStatus(CLIENT_HAS_PASS);
	}
}
