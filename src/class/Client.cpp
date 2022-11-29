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

void Client::addStatus(unsigned char to_add)
{
	status |= to_add;
}

void Client::removeStatus(unsigned char to_rmv)
{
	status ^= to_rmv;
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
	send(sock, msg.c_str(), msg.length(), MSG_NOSIGNAL);
}

void Client::pong(const std::string & token)
{
	if ((status & CLIENT_PING) && token == pingToken)
		status ^= CLIENT_PING;
}

void Client::sendMsg(const std::string & msg)
{
	send(sock, msg.c_str(), msg.length(), MSG_NOSIGNAL);
}
