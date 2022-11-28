#pragma once

#include "ft_irc.hpp"
#include "IMsgTarget.hpp"

class Client: public IMsgTarget
{
private:
	unsigned int status;
	std::string nickname;
	std::string username;
	std::string fullname;

	int sock;
	std::string message;

	std::string pingToken;

public:
	Client(int fd, const std::string & nick = "*");
	virtual ~Client();

	void setPass();
	void setNick(const std::string & newNick);
	void setUser(const std::string & newUser, const std::string & hostname);
	void setOper();
	void removeOper();
	void quit();

	void setSock(int fd);
	void addMessage(const std::string & msg);
	void clearMessage();
	void signUp();

	void ping(const std::string & token);
	void pong();

	std::string & getName() { return getNick(); }
	virtual void sendMsg(const std::string & msg);

	unsigned int getStatus() { return status; }
	std::string & getNick() { return nickname; }
	std::string & getUser() { return username; }
	std::string getFullName() { return std::string(nickname + fullname); }
	int getSock() { return sock; }
	std::string & getMessage() { return message; }
	std::string getIsOper() { return (status & CLIENT_OPERATOR) ? "+O\r\n":"\r\n"; }
	std::string & getPingToken() { return pingToken; }
};
