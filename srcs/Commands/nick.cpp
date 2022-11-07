# include "Server.hpp"

//  booucle de find
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
		msg.setReply("431 " + _client.getNick() + " :No nickname given.\r\n");
		return;
	}
	else if (!isValidNick((msg.getArgs())[0]))
	{
		msg.setReply("432 " + _client.getNick() + " " + (msg.getArgs())[0] + "  :Erroneous nickname.\r\n");
		return;
	}
	_client.setNick((msg.getArgs())[0]);
	msg.setReply("");
}

// ERR_NONICKNAMEGIVEN (431)
// ERR_ERRONEUSNICKNAME (432)
// ERR_NICKNAMEINUSE (433)
// change nick possible
// impossible Dan et dan
