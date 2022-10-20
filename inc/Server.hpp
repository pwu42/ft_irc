#pragma once

/* includes */

#include "ft_irc.hpp"

/* defines */

#define BUF_SIZE 512

/* utils */

void handler(int signo);

/* Server class */

class Server
{
private:
	const int _port;
	const std::string _pass;
	char _buffer[BUF_SIZE];

	int _server_sock;
	struct sockaddr_in _address;
	socklen_t _address_len;

	int _client_sock;

public:
	Server(int port, std::string pass);
	~Server();

	void run();
};