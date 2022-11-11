#include "Client.hpp"

Client::Client(int fd, const std::string & nick):
	status(0),
	nickname(nick),
	sock(fd),
	message("")
{
}

Client::~Client()
{
}

void Client::setPass()
{
	status |= CLIENT_HAS_PASS;
}

void Client::setNick(const std::string & newNick)
{
	nickname = newNick;
	status |= CLIENT_HAS_NICK;
}

void Client::setUser(const std::string & newUser, const std::string & newFullName)
{
	username = newUser;
	fullname = newFullName;
	status |= CLIENT_HAS_USER;
}

void Client::setSock(int fd)
{
	sock = fd;
}

void Client::addMessage(std::string msg)
{
	message += msg;
}

void Client::clearMessage()
{
	message.clear();
}

void Client::signUp()
{
	status |= CLIENT_REGISTER;
}