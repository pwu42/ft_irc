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

enum e_rpl
{
	RPL_WELCOME = 001,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,
	ERR_NEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTERED = 462,
	ERR_PASSWDMISMATCH = 464
};

// typedef void (Server::FPTR)(Message);
class Server
{
	// std::map<int sock, User *> _users;
	// typedef void (Server::*Fonct)(Message);
private:
	const std::string _port;
	const std::string _pass;

	int _sock;
	struct sockaddr_in _address;
	socklen_t _addrLenght;

	void _rpl_welcome(Message &msg);

	void _err_noNicknameGiven(Message &msg);
	void _err_erroneusNickname(Message &msg);
	void _err_nicknameInUse(Message &msg);
	void _err_needMoreParams(Message &msg);
	void _err_alreadyRegistered(Message &msg);
	void _err_passwdMisMatch(Message &msg);

	std::map<std::string, void (Server::*)(Message &)> _commands;
	std::map<unsigned int, void (Server::*)(Message &)> _reply;
	User _client;

	void _cmdNick(Message &msg);
	void _cmdPass(Message &msg);
	void _cmdPing(Message &msg);
	void _cmdPong(Message &msg);

	void callReply(unsigned int rpl_number, Message &msg);
	void _setCommands();
	void _setReply();

public:
	Server(std::string port, std::string pass);
	void usecmd(Message &msg);
	void ReceiveUser();
	int getSock() const;
	User getClient() const;
	int getClientSock() const;
	~Server();

	// std::string usecmd(Message &msg, User &user);
};

#endif
