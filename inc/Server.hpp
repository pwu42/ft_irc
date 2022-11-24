#pragma once

/* includes */

#include "ft_irc.hpp"
#include "Client.hpp"
#include "SplitMsg.hpp"

/* defines */

#define BUF_SIZE 8192

/* global */

extern bool on;

class Server
{
private:
	const int port;
	const std::string pass;

	std::string hostname;
	std::string ip;
	std::string creationDate;
	time_t lastPing;
	size_t fdLimit;

	std::map<std::string, std::string> replies;

	int serverSock;
	struct sockaddr_in address;
	socklen_t addrLength;
	struct pollfd * fds;
	size_t fdCount;

	std::map<int, Client *> clients;

public:
	Server(int port, const std::string & pass);
	~Server();

	void run();

private:
	Server();
	Server(const Server & x);

	void initReplies();
	void getHostInfo();
	void getTime();
	void getLimits();
	void initSocket();

	void addNewClient();
	void deleteClient(int index);
	int recvMessage(Client * sender);
	int exeMessage(Client * sender);

	void cmdPass(Client * sender, SplitMsg & message);
	void cmdNick(Client * sender, SplitMsg & message);
	void cmdUser(Client * sender, SplitMsg & message);
	void cmdPing(Client * sender, SplitMsg & message);
	void cmdPong(Client * sender, SplitMsg & message);
	void cmdOper(Client * sender, SplitMsg & message);
	void cmdMode(Client * sender, SplitMsg & message);
	void cmdQuit(Client * sender, SplitMsg & message);
	void cmdPrivmsg(Client * sender, SplitMsg & message);

	void pingClients();
	void clientDisconnect(Client * target);
	void reply(SplitMsg & message);
	void welcome(Client * target, SplitMsg & message);
	
	void exit(bool ex = false, const std::string & msg = "");
};

bool caseInsensEqual(const std::string & a, const std::string & b);