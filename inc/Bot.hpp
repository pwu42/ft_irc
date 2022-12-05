#pragma once

#include "ft_irc.hpp"
#include "SplitMsg.hpp"

extern bool bot_on;

class Bot
{
private:
	std::string pass;

	std::map<std::string, void(Bot::*)(SplitMsg &)> commands;
	std::string ip;
	struct pollfd sock;
	struct sockaddr_in address;

	std::string nick;
	std::string message;

public:
	Bot();
	~Bot();

	void init(int port, const std::string & password);
	void initCommands();
	void run();

private:
	void sendMsg(const std::string & msg);
	int recvMsg();
	int exeMsg();

	void cmdNickInUse(SplitMsg & msg);
	void cmdWrongPass(SplitMsg & msg);
	void cmdPing(SplitMsg & msg);
	void cmdPrivmsg(SplitMsg & msg);
};
std::string roll(int max);