#pragma once

/* includes */

#include "ft_irc.hpp"

/* defines */

#define BUF_SIZE 8192

extern bool serv_on;

class Server
{
private:
	const int Port;
	const std::string Pass;
	char Buffer[BUF_SIZE];

	int ServerSock;
	struct sockaddr_in Address;
	socklen_t AddrLength;

	int ClientSock;

public:
	Server(int port, std::string pass);
	~Server();

	void Run();

private:
	void InitSocket();
	void Exit(bool ex = false, std::string msg = "");
};

void handler(int signo);