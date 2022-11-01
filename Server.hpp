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
#include "Message.hpp"

class Server
{
	// std::map<std::string, User *> _users;
	// typedef std::string (*FPTR)(Message, User &);
private:
	const std::string _port;
	const std::string _pass;

	int _sock;
	struct sockaddr_in _address;
	socklen_t _addrLenght;
	typedef std::string (*FPTR)(Message);
	std::map<std::string, FPTR> _commands;
	User _client;

public:
	Server(std::string port, std::string pass);
	std::string usecmd(Message msg);
	void ReceiveUser();
	int getSock() const;
	User getClient() const;
	int getClientSock() const;

	~Server();

	// std::string usecmd(Message msg, User &user);
};

#endif
