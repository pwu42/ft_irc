#include "Server.hpp"

static bool isValidNick(std::string)
{
	return (true);
}

// repasse a l'opt msg +user
void Server::_cmdNick(Message &msg)
{
	if (!isValidNick(msg.getArgs()))
	{
		msg.setReply("433 " + _client.getNick() + " " + msg.getArgs() + " :Nickname is already in use.\r\n");
		return;
	}
	_client.setNick(msg.getArgs());
	msg.setReply("");
}

// ERR_NONICKNAMEGIVEN (431)
// ERR_ERRONEUSNICKNAME (432)
// ERR_NICKNAMEINUSE (433)
// change nick possible
// impossible Dan et dan
