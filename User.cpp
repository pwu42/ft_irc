#include "User.hpp"

User::User()
{
	_sock = -1;
	_nick = "";
	_addr = "";
	_username = "";
}
User::~User()
{
	if (_sock >= 0)
		close(_sock);
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

void User::setUser(std::string const &username)
{
	_username = username;
}

void User::setNick(std::string const &nick)
{
	_nick = nick;
}

void User::setSock(int sock)
{
	_sock = sock;
}
