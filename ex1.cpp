#include "ex1.hpp"

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

void User::setUser(std::string const &nick)
{
}

void User::setNick(std::string const &nick)
{
}

void Channel::addUser(User *user, std::string nick)
{
}

void Channel::deleteUser(std::string nick)
{
}
