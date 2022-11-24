#include "Client.hpp"

Client::Client(int fd, const std::string & nick):
	status(0),
	nickname(nick),
	username(),
	fullname(),
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

void Client::setUser(const std::string & newUser, const std::string & hostname)
{
	username = newUser;
	fullname = '!' + username + '@' + hostname;
	status |= CLIENT_HAS_USER;
}

void Client::setOper()
{
	status |= CLIENT_OPERATOR;
}

void Client::removeOper()
{
	status ^= CLIENT_OPERATOR;
}

void Client::quit()
{
	status |= CLIENT_HAS_QUIT;
}

void Client::setSock(int fd)
{
	sock = fd;
}

void Client::addMessage(const std::string & msg)
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

void Client::ping(const std::string & token)
{
	std::string msg = "PING " + token + "\r\n";
	pingToken = token;
	status |= CLIENT_PING;
	send(sock, msg.c_str(), msg.length(), 0);
}

void Client::pong()
{
	status ^= CLIENT_PING;
}

void Client::sendMsg(const std::string & msg)
{
	send(sock, msg.c_str(), msg.length(), 0);
}