#pragma once

/* includes */

#include "ft_irc.hpp"
#include "Client.hpp"
#include "SplitMsg.hpp"

/* defines */

#define BUF_SIZE 8192

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

	std::map<int, Client *> clients;

public:
	Server(int port, std::string pass);
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

	int readMessage(Client * sender, std::string & message);
	void exeMessage(Client * sender, SplitMsg & message);

	void cmdPass(Client * sender, std::vector<std::string> & params);
	void cmdNick(Client * sender, std::vector<std::string> & params);
	void cmdUser(Client * sender, std::vector<std::string> & params);

	ssize_t sendNumeric(Client * target, std::string reply, std::string param1 = "", std::string param2 = "");
	void welcome(Client * target);
	void exit(bool ex = false, std::string msg = "");
};

void handler(int signo);