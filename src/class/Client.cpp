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
	addStatus(CLIENT_HAS_NICK);
}

void Client::setUser(const std::string & newUser, const std::string & hostname)
{
	username = newUser;
	fullname = '!' + username + '@' + hostname;
	addStatus(CLIENT_HAS_USER);
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

void Client::addChannel(const std::string & channelName)
{
	for (std::list<std::string>::iterator it = _channels.begin(); it != _channels.end() && caseInsensEqual(channelName, *it); it++)
		if (caseInsensEqual(channelName, *it))
			return;
	_channels.push_back(channelName);
}

void Client::removeChannel(const std::string & channelName)
{
	for (std::list<std::string>::iterator it = _channels.begin(); it != _channels.end(); it++)
		if (caseInsensEqual(channelName, *it))
		{
			_channels.erase(it);
			break;
		}
}

bool Client::isIn(const std::string & channelName)
{
	for (std::list<std::string>::const_iterator it = _channels.begin(); it != _channels.end(); it++)
		if (caseInsensEqual(channelName, *it))
			return true;
	return false;
}

void Client::ping(const std::string & token)
{
	std::string pingMsg = "PING " + token + "\r\n";
	pingToken = token;
	addStatus(CLIENT_PING);
	sendMsg(pingMsg);
}

void Client::pong(const std::string & token)
{
	if ((status & CLIENT_PING) && token == pingToken)
		removeStatus(CLIENT_PING);
}
std::list<std::string> Client::getList() const
{
	return (_channels);
}


void Client::leaveAllChannels()
{
	_channels.clear();
}


void Client::sendMsg(const std::string & message, IMsgTarget *exception)
{
	(void)exception;
	send(sock, message.c_str(), message.length(), MSG_NOSIGNAL);
}
