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
	void readClient(size_t index);
	int recvMessage(Client * sender);
	void exeMessage(Client * sender);

	void cmdPass(Client * sender, const std::vector<std::string> & params);
	void cmdNick(Client * sender, const std::vector<std::string> & params);
	void cmdUser(Client * sender, const std::vector<std::string> & params);
	void cmdPing(Client * sender, const std::vector<std::string> & params);

	ssize_t sendNumeric(Client * target, const std::string & numeric, const std::string & param1 = "", const std::string & param2 = "");
	void welcome(Client * target);
	void exit(bool ex = false, const std::string & msg = "");
};

void handler(int signo);
bool caseInsensEqual(const std::string & a, const std::string & b);