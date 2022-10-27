#pragma once

#include "ft_irc.hpp"

class Client
{
private:
	unsigned char status;
	std::string nickname;
	std::string username;

	int sock;

public:
	Client(int fd, std::string nick = "");
	~Client();

	void setPass();
	void setNick(std::string newNick);
	void setUser(std::string newUser);
	void setSock(int fd);

	unsigned char getStatus() { return status; }
	std::string & getNick() { return nickname; }
	std::string & getUser() { return username; }
	int getSock() { return sock; }
};
