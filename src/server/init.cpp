#include "Server.hpp"

void Server::getHostInfo()
{
	char host[256];
	char *ip_buffer;
	struct hostent *host_entry;
	int host_name;

	std::cerr << "Retrieving host info ... ";
	if ((host_name = gethostname(host, sizeof(host))) < 0)
		exit(true, "gethostname()");
	if ((host_entry = gethostbyname(host)) == NULL)
		exit(true, "gethostbyname()");
	ip_buffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));

	hostname = host;
	ip = ip_buffer;
	if (hostname.length() > 63)
		hostname = ip;

	std::cerr << "Done\n Host:\t" << hostname << "\n IP:\t" << ip << '\n';
}

void Server::getTime()
{
	struct tm * timeinfo;

	std::cerr << "Retrieving additional info ... ";
	time(&lastPing);
	timeinfo = localtime(&lastPing);
	creationDate = asctime(timeinfo);
	creationDate.erase(creationDate.end() - 1);
}

void Server::getLimits()
{
	struct rlimit limits;

	if (getrlimit(RLIMIT_NOFILE, &limits) < 0)
		exit(true, "getrlimit()");
	fdLimit = limits.rlim_cur;

	std::cerr << "Done\n";
}

void Server::initReplies()
{
	replies[RPL_WELCOME] = ":Welcome to the Internet Relay Network ";
	replies[RPL_YOURHOST] = ":Your host is " + hostname + ", running version 0\r\n";
	replies[RPL_CREATED] = ":This server was created " + creationDate + "\r\n";
	replies[RPL_MYINFO] = ':' + hostname + " 0 O Oo\r\n";
	replies[RPL_YOUREOPER] = ":You are now an IRC operator\r\n";
	replies[ERR_NOSUCHNICK] = ":No such nick/channel\r\n";
	replies[ERR_NOSUCHSERVER] = ":No such server\r\n";
	replies[ERR_NORECIPIENT] = ":No recipient given\r\n";
	replies[ERR_NOTEXTTOSEND] = ":No text to send\r\n";
	replies[ERR_NONICKNAMEGIVEN] = ":No nickname given\r\n";
	replies[ERR_ERRONEUSNICKNAME] = ":Erroneous nickname\r\n";
	replies[ERR_NICKNAMEINUSE] = ":Nickname is already in use\r\n";
	replies[ERR_NOTREGISTERED] = ":You have not registered\r\n";
	replies[ERR_NEEDMOREPARAMS] = ":Not enough parameters\r\n";
	replies[ERR_ALREADYREGISTERED] = ":Unauthorized command (already registered)\r\n";
	replies[ERR_PASSWDMISMATCH] = ":Password incorrect\r\n";
	replies[ERR_NOOPERHOST] = ":No O-lines for your host\r\n";
	replies[ERR_UMODEUNKNOWNFLAG] = ":Unknown MODE flag\r\n";
	replies[ERR_USERSDONTMATCH] = ":Cannot change mode for other users\r\n";
}

void Server::initSocket()
{
	int opt = 1;

	std::cerr << "Creating socket ... ";
	if ((serverSock = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 6)) < 0)
		exit(true, "socket()");
	if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		exit(true, "setsockopt()");
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	addrLength = sizeof(address);
	if (bind(serverSock, reinterpret_cast<struct sockaddr *>(&address), addrLength) < 0)
		exit(true, "bind()");
	if (listen(serverSock, 4) < 0)
		exit(true, "listen()");

	fds = new struct pollfd[fdLimit];
	fds[0].fd = serverSock;
	fds[0].events = POLLIN;

	std::cerr << "Done\n";
}