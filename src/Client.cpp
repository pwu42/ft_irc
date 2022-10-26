#include "Client.hpp"

Client::Client():
	status(0),
	nickname(""),
	username("")
{
}

Client::~Client()
{
}

void Client::setPass()
{
	status |= CLIENT_HAS_PASS;
}

void Client::setNick(std::string newNick)
{
	nickname = newNick;
	status |= CLIENT_HAS_NICK;
}

void Client::setUser(std::string newUser)
{
	username = newUser;
	status |= CLIENT_HAS_USER;
}
