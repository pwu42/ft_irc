#include "User.hpp"

User::User()
{
	_sock = -1;
	_nick = "*";
	_addr = "";
	_username = "";
	_status = 0;
}
User::~User()
{
	if (_sock >= 0)
		close(_sock);
}
unsigned char User::getStatus() const
{
	return (_status);
}

std::string User::getUsername() const
{
	return (_username);
}

std::string User::getAddr() const
{
	return(_addr);
}

std::string User::getNick() const
{
	return(_nick);
}

int User::getSock() const
{
	return(_sock);
}

void User::addStatus(unsigned char status)
{
	_status |= status;
}

void User::removeStatus(unsigned char status)
{
	_status ^= status;
}


void User::setUser(std::string const &username)
{
	_username = username;
	_status |= CLIENT_HAS_USER;
}

void User::setNick(std::string const &nick)
{
	_nick = nick;
	_status |= CLIENT_HAS_NICK;
}

void User::setSock(int sock)
{
	_sock = sock;
}
