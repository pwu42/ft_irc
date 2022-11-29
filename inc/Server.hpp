#pragma once



/* includes */

#include "ft_irc.hpp"
#include "Client.hpp"
#include "SplitMsg.hpp"

/* defines */

#define BUF_SIZE 8192

/* global */

extern bool on;

class Server
{
private:
	const int port;
	const std::string pass;

	std::map<std::string, void(Server::*)(Client *, SplitMsg &)> commands;
	std::string hostname;
	std::string ip;
	std::string creationDate;
	time_t lastPing;
	size_t fdLimit;

	std::map<std::string, std::string> replies;

	struct sockaddr_in address;
	socklen_t addrLength;
	struct pollfd * fds;
	size_t fdCount;

	std::map<int, Client *> clients;

public:
	Server(int port, const std::string & pass);
	~Server();

	void init();
	void run();

private:
	Server();
	Server(const Server & x);

	void initCommands();
	void initReplies();
	void getHostInfo();
	void getTime();
	void getLimits();
	void initSocket();

	void addNewClient();
	void deleteClient(int index, const std::string & quitMsg = "QUIT :Connection lost\r\n");
	int recvMessage(Client * sender);
	int exeMessage(Client * sender);

	void cmdPass(Client * sender, SplitMsg & message);
	void cmdNick(Client * sender, SplitMsg & message);
	void cmdUser(Client * sender, SplitMsg & message);
	void cmdPing(Client * sender, SplitMsg & message);
	void cmdPong(Client * sender, SplitMsg & message);
	void cmdOper(Client * sender, SplitMsg & message);
	void cmdMode(Client * sender, SplitMsg & message);
	void cmdQuit(Client * sender, SplitMsg & message);
	void cmdPrivmsg(Client * sender, SplitMsg & message);
	void cmdKill(Client * sender, SplitMsg & message);
	void cmdDoNothing(Client * sender, SplitMsg & message);

	void pingClients();
	void clientDisconnect(Client * target, const std::string & quitMsg);
	void reply(Client * sender, SplitMsg & message);
	void welcome(Client * target, SplitMsg & message);

	void exit(bool ex = false, const std::string & msg = "");
};

bool caseInsensEqual(const std::string & a, const std::string & b);
size_t findIndex(int fd, struct pollfd * fds, size_t count);
Client * findbyNick(const std::string & nick, const std::map<int, Client *> & clients);
