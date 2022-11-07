#pragma once

#include "ft_irc.hpp"

class Client
{
private:
	unsigned char status;
	std::string nickname;
	std::string username;
	std::string fullname;

	int sock;

public:
	Client(int fd, const std::string & nick = "*");
	~Client();

	void setPass();
	void setNick(const std::string & newNick);
	void setUser(const std::string & newUser, const std::string & fullName);
	void setSock(int fd);
	void signUp();

	unsigned char getStatus() { return status; }
	std::string & getNick() { return nickname; }
	std::string & getUser() { return username; }
	int getSock() { return sock; }
};
