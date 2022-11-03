#include "Server.hpp"

bool on = false;

Server::Server(int port, std::string pass):
	port(port),
	pass(pass),
	serverSock(-2)
{
	std::cerr << "\n o0o0o0o Server is starting o0o0o0o\n\n";
	initReplies();
	getHostInfo();
	getTime();
	getLimits();
	initSocket();
	on = true;
}

Server::~Server()
{
	exit();
}

void handler(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
		on = false;
}

int Server::readMessage(Client * sender, std::string & message)
{
	char buffer[BUF_SIZE + 1];
	ssize_t readCount;

	while (message.find('\n') == std::string::npos)
	{
		if ((readCount = recv(sender->getSock(), buffer, BUF_SIZE, 0)) < 0)
			exit(true, "recv()");
		buffer[readCount] = 0;
		message += buffer;
		if (readCount == 0)
		{
			std::cerr << "Client has left\n";
			return 1;
		}
	}
	message.erase(message.find('\n'));
	if (message.length() > 510)
		message.erase(510);
	message += "\r\n";
	return 0;
}

void Server::exeMessage(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() > 15)
		return;

	std::string command = message.getCommand();

	if (command == std::string("PASS"))
		cmdPass(sender, message.getParams());
	else if (command == std::string("NICK"))
		cmdNick(sender, message.getParams());
	else if (command == std::string("USER"))
		cmdUser(sender, message.getParams());
}

void Server::run()
{
	int clientSock;

	std::cerr << "Waiting for client to connect ... ";
	if ((clientSock = accept(serverSock, reinterpret_cast<struct sockaddr *>(&address), &addrLength)) < 0)
		exit(true, "accept()");
	Client client(clientSock);
	clients.insert(std::make_pair(clientSock, &client));

	std::cerr << "Done\n";

	do
	{
		std::string message;
		if (readMessage(clients[clientSock], message) == 1)
			return;

		SplitMsg split(message);
		exeMessage(clients[clientSock], split);
	} while (on == true);
}

void Server::initReplies()
{
	replies.insert(std::make_pair("431", ":No nickname given\r\n"));
	replies.insert(std::make_pair("432", ":Erroneous nickname\r\n"));
	replies.insert(std::make_pair("433", ":Nickname is already in use\r\n"));
	replies.insert(std::make_pair("451", ":You have not registered\r\n"));
	replies.insert(std::make_pair("461", ":Not enough parameters\r\n"));
	replies.insert(std::make_pair("462", ":Unauthorized command (already registered)\r\n"));
	replies.insert(std::make_pair("464", ":Password incorrect\r\n"));
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
	time_t t;
	struct tm * timeinfo;

	time(&t);
	timeinfo = localtime(&t);
	creationDate = asctime(timeinfo);
	creationDate.erase(creationDate.end() - 1);
}

void Server::getLimits()
{
	struct rlimit limits;

	std::cerr << "Retrieving additional info ... ";
	if (getrlimit(RLIMIT_NOFILE, &limits) < 0)
		exit(true, "getrlimit()");
	fdLimit = limits.rlim_cur;

	std::cerr << "Done\n";
}

void Server::initSocket()
{
	int opt = 1;

	std::cerr << "Creating socket ... ";
	if ((serverSock = socket(AF_INET, SOCK_STREAM/*  | SOCK_NONBLOCK */, 6)) < 0)
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

	std::cerr << "Done\n";
}

ssize_t Server::sendNumeric(Client * target, std::string numeric, std::string param1, std::string param2)
{
	std::string reply = ":" + hostname + " " + numeric + " " + target->getNick() + " " + param1 + param2 + replies[numeric];
	return send(target->getSock(), reply.c_str(), std::min(size_t(512),reply.length()), 0);
}

void Server::welcome(Client * target)
{
	std::string reply = "Welcome to the Internet Relay Network " + target->getNick() + "!" + target->getUser() + "@" + hostname + "\r\n";
	send(target->getSock(), reply.c_str(), std::min(size_t(512), reply.length()), 0);

	reply = "Your host is " + hostname + ", running version 0\r\n";
	send(target->getSock(), reply.c_str(), std::min(size_t(512), reply.length()), 0);

	reply = "This server was created " + creationDate + "\r\n";
	send(target->getSock(), reply.c_str(), std::min(size_t(512), reply.length()), 0);

	reply = hostname + " 0 o ov\r\n";
	send(target->getSock(), reply.c_str(), std::min(size_t(512), reply.length()), 0);

	target->signUp();
}

void Server::exit(bool except, std::string msg)
{
	for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); it++)
		if (it->first > 0)
			close(it->first);
	if (serverSock > 0)
		close(serverSock);
	if (except == true)
	{
		std::cerr << "Error\n";
		throw std::runtime_error(msg.c_str());
	}
}