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

	int serverSock;
	struct sockaddr_in address;
	socklen_t addrLength;

	int clientSock;
	Client client;

public:
	Server(int port, std::string pass);
	~Server();

	void run();

private:
	void initSocket();

	int readMessage(std::string & message);
	void exeMessage(SplitMsg & message);

	void exit(bool ex = false, std::string msg = "");
};

void handler(int signo);