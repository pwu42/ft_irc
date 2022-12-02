#pragma once

#include "ft_irc.hpp"
#include "SplitMsg.hpp"

extern bool bot_on;

class Bot
{
private:
	std::string pass;

	std::string ip;
	struct pollfd sock;
	struct sockaddr_in address;

	bool registered;
	std::string message;

public:
	Bot();
	~Bot();

	void init(int port, const std::string & password);
	void run();

private:
	void sendMsg(const std::string & msg);
	int recvMsg();
	int exeMsg();
};