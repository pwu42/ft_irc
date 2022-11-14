#pragma once

#include "ft_irc.hpp"

class Client
{
private:
	unsigned int status;
	std::string nickname;
	std::string username;
	std::string fullname;

	int sock;
	std::string message;

public:
	Client(int fd, const std::string & nick = "*");
	~Client();

	void setPass();
	void setNick(const std::string & newNick);
	void setUser(const std::string & newUser, const std::string & fullName);
	void setSock(int fd);
	void addMessage(const std::string & msg);
	void clearMessage();
	void signUp();

	unsigned int getStatus() { return status; }
	std::string & getNick() { return nickname; }
	std::string & getUser() { return username; }
	int getSock() { return sock; }
	std::string & getMessage() { return message; }
};
