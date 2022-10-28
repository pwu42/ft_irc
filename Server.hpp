#ifndef SERVER_HPP
#include <csignal>
#include <cstdlib>
#include <cstring>

#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include "User.hpp"

class Server
{
private:
	const std::string _port;
	const std::string _pass;

	int _sock;
	struct sockaddr_in _address;
	socklen_t _addrLenght;
	// std::map<std::string, User *> _users;
	User _client;

public:
	Server(std::string port, std::string pass);

	void ReceiveUser();
	int getSock() const;
	User getClient() const;
	int getClientSock() const;

	~Server();

};

#endif
