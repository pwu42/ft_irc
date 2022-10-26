#pragma once

#include "ft_irc.hpp"

class Client
{
private:
	unsigned char status;
	std::string nickname;
	std::string username;

public:
	Client();
	~Client();

	void setPass();
	void setNick(std::string newNick);
	void setUser(std::string newUser);

	unsigned char getStatus() { return status; }
	std::string & getNick() { return nickname; }
	std::string & getUser() { return username; }
};
