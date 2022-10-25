#pragma once

/* includes */

#include "ft_irc.hpp"
#include "Client.hpp"

/* defines */

#define BUF_SIZE 8192

extern bool on;

class Server
{
private:
	const int port;
	const std::string pass;

	char buffer[BUF_SIZE + 1];
	std::string message;

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

	int readMessage();
	void parseMessage();

	void exit(bool ex = false, std::string msg = "");
};

void handler(int signo);