#include "Client.hpp"

Client::Client(int fd, std::string nick):
	status(0),
	nickname(nick),
	username(""),
	sock(fd)
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

void Client::setSock(int fd)
{
	sock = fd;
}