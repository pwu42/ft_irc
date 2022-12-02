#include "Server.hpp"

void Server::init()
{
	std::cerr << "\n o0o0o0o Server is starting o0o0o0o\n\n";
	getHostInfo();
	getTime();
	getLimits();
	initCommands();
	initReplies();
	initSocket();
	on = true;
}

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

void Server::initCommands()
{
	commands["JOIN"] = &Server::cmdJoin;
	commands["CAP"] = &Server::cmdDoNothing;
	commands["kill"] = &Server::cmdKill;
	commands["KILL"] = &Server::cmdKill;
	commands["MODE"] = &Server::cmdMode;
	commands["NICK"] = &Server::cmdNick;
	commands["NOTICE"] = &Server::cmdPrivmsg;
	commands["OPER"] = &Server::cmdOper;
	commands["PART"] = &Server::cmdPart;
	commands["PASS"] = &Server::cmdPass;
	commands["PING"] = &Server::cmdPing;
	commands["PONG"] = &Server::cmdPong;
	commands["PRIVMSG"] = &Server::cmdPrivmsg;
	commands["QUIT"] = &Server::cmdQuit;
	commands["TOPIC"] = &Server::cmdTopic;
	commands["USER"] = &Server::cmdUser;

}

void Server::initReplies()
{
	replies[RPL_WELCOME] = ":Welcome to the Internet Relay Network ";
	replies[RPL_YOURHOST] = ":Your host is " + hostname + ", running version 0\r\n";
	replies[RPL_CREATED] = ":This server was created " + creationDate + "\r\n";
	replies[RPL_MYINFO] = ':' + hostname + " 0 o Oo\r\n";
	replies[RPL_NOTOPIC] = ":No topic is set\r\n";
	replies[RPL_YOUREOPER] = ":You are now an IRC operator\r\n";
	replies[ERR_NOSUCHNICK] = ":No such nick/channel\r\n";
	replies[ERR_NOSUCHSERVER] = ":No such server\r\n";
	replies[ERR_NOSUCHCHANNEL] = ":No such channel\r\n";
	replies[ERR_NORECIPIENT] = ":No recipient given\r\n";
	replies[ERR_NOTEXTTOSEND] = ":No text to send\r\n";
	replies[ERR_UNKNOWNCOMMAND] = ":Unknown command\r\n";
	replies[ERR_NONICKNAMEGIVEN] = ":No nickname given\r\n";
	replies[ERR_ERRONEUSNICKNAME] = ":Erroneous nickname\r\n";
	replies[ERR_NICKNAMEINUSE] = ":Nickname is already in use\r\n";
	replies[ERR_NOTONCHANNEL] = ":You're not on that channel\r\n";
	replies[ERR_NOTREGISTERED] = ":You have not registered\r\n";
	replies[ERR_NEEDMOREPARAMS] = ":Not enough parameters\r\n";
	replies[ERR_ALREADYREGISTERED] = ":Unauthorized command (already registered)\r\n";
	replies[ERR_PASSWDMISMATCH] = ":Password incorrect\r\n";
	replies[ERR_BADCHANMASK] = ":Bad Channel Mask\r\n";
	replies[ERR_NOPRIVILEGES] = ":Permission Denied- You're not an IRC operator\r\n";
	replies[ERR_NOOPERHOST] = ":No O-lines for your host\r\n";
	replies[ERR_UMODEUNKNOWNFLAG] = ":Unknown MODE flag\r\n";
	replies[ERR_USERSDONTMATCH] = ":Cannot change mode for other users\r\n";
}

void Server::initSocket()
{
	int opt = 1;
	fds = new struct pollfd[fdLimit];
	fds[0].fd = -2;
	fds[0].events = POLLIN;

	std::cerr << "Creating socket ... ";
	if ((fds[0].fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 6)) < 0)
		exit(true, "socket()");
	if (setsockopt(fds[0].fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		exit(true, "setsockopt()");
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	addrLength = sizeof(address);
	if (bind(fds[0].fd, reinterpret_cast<struct sockaddr *>(&address), addrLength) < 0)
		exit(true, "bind()");
	if (listen(fds[0].fd, 4) < 0)
		exit(true, "listen()");

	std::cerr << "Done\n";
}
