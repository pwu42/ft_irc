# include "Server.hpp"
// impossible Dan et dan
// change nick possible

// static bool isValidNick(std::string nickname, char *tofind)
static bool isValidNick(std::string nickname)
{
	if ((nickname.c_str())[0] == '$' ||
		(nickname.c_str())[0] == ':' ||
		(nickname.c_str())[0] == '#' ||
		(nickname.c_str())[0] == '&')
	{
		return (false);
	}
	if (std::strcspn(nickname.c_str(), " ,.?!@*") != nickname.size())
	{
		return (false);
	}
	return (true);
}

// repasse a l'opt msg +user
void Server::_cmdNick(Message &msg)
{
	if ((msg.getArgs()).empty() == true)
	{
		callReply(ERR_NONICKNAMEGIVEN, msg);
		return;
	}
	else if (!isValidNick((msg.getArgs())[0]))
	{
		callReply(ERR_ERRONEUSNICKNAME, msg);
		return;
	}
	_client.setNick((msg.getArgs())[0]);
	msg.setReply("");
	if ((_client.getStatus()) & CLIENT_HAS_NICK & CLIENT_HAS_USER & CLIENT_HAS_PASS)
		callReply(RPL_WELCOME, msg);
}
