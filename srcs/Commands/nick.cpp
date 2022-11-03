#include "Commands.hpp"

static bool isValidNick(std::string)
{

}

// repasse a l'opt msg +user
std::string cmdNick(Message msg, User &client)
{
	if (!isValidNick(msg.getArgs()))
		return ("433 " + client.getNick() + " " + msg.getArgs() + " :Nickname is already in use.\r\n");
	client.setNick(msg.getArgs());
	return ("");
}

// ERR_NONICKNAMEGIVEN (431)
// ERR_ERRONEUSNICKNAME (432)
// ERR_NICKNAMEINUSE (433)
// change nick possible
// impossible Dan et dan
