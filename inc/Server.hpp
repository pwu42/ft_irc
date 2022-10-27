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
	Server(Server const & x);

	void getHostInfo();
	void initSocket();

	int readMessage(Client * sender, std::string & message);
	void exeMessage(Client * sender, SplitMsg & message);

	void cmdPass(Client * sender, std::vector<std::string> & params);
	void cmdNick(Client * sender, std::vector<std::string> & params);
	void nickReply(Client * sender, std::string & newNick);
	void cmdUser(Client * sender, std::vector<std::string> & params);

	void exit(bool ex = false, std::string msg = "");
};

void handler(int signo);
ssize_t sendNumeric(int fd, std::string reply, std::string param1 = "", std::string param2 = "");