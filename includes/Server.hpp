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
// class Server;

// typedef void (Server::FPTR)(Message);
class Server
{
	// std::map<std::string, User *> _users;
	// typedef void (Server::*Fonct)(Message);
private:
	const std::string _port;
	const std::string _pass;

	int _sock;
	struct sockaddr_in _address;
	socklen_t _addrLenght;
	std::map<std::string, void (Server::*)(Message &)> _commands;
	User _client;
	void _rpl_welcome(Message &msg);
	void _cmdNick(Message &msg);
	void _cmdPass(Message &msg);
	void _setCommands();

public:
	Server(std::string port, std::string pass);
	void usecmd(Message &msg);
	void ReceiveUser();
	int getSock() const;
	User getClient() const;
	int getClientSock() const;
	~Server();

	// std::string usecmd(Message msg, User &user);
};

#endif
