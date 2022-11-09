#include "Server.hpp"

bool on = false;

bool caseInsensEqual(const std::string & a, const std::string & b)
{
	size_t size = a.size();
	if (size != b.size())
		return false;
	for (size_t i = 0; i < size; i++)
		if (std::tolower(a[i]) != std::tolower(b[i]))
			return false;
	return true;
}

Server::Server(int port, const std::string & pass):
	port(port),
	pass(pass),
	serverSock(-2),
	fdCount(1)
{
	std::cerr << "\n o0o0o0o Server is starting o0o0o0o\n\n";
	getHostInfo();
	getTime();
	getLimits();
	initReplies();
	initSocket();
	// signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	on = true;
}

Server::~Server()
{
	exit();
	for (size_t i = 0; i < fdCount; i++)
	{
		delete clients[fds[i].fd];
		if (fds[i].fd >= 3)
			close(fds[i].fd);
	}
	delete [] fds;
}

void handler(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
	{
		std::cerr << "SignalInterrupt\n";
		on = false;
	}
}

void Server::addNewClient()
{
	int fd;

	std::cerr << "Reading server socket\n";
	do
	{
		if ((fd = accept(serverSock, reinterpret_cast<struct sockaddr *>(&address), &addrLength)) < 0)
		{
			if (errno != EAGAIN && errno != EWOULDBLOCK)
			{
				std::cerr << "Error: accept()\n";
				on = false;
			}
			break;
		}
		std::cerr << "New connection on socket " << fd << '\n';
		fds[fdCount].fd = fd;
		fds[fdCount].events = POLLIN;
		++fdCount;
		clients[fd] = new Client(fd);
	} while (fd != -1);
}

int Server::readMessage(int fd, std::string & message)
{
	char buffer[BUF_SIZE + 1];
	ssize_t readCount;

	do
	{
		readCount = recv(fd, buffer, BUF_SIZE, 0);
		if (readCount < 0)
		{
			if (errno != EAGAIN && errno != EWOULDBLOCK)
				std::cerr << "Error: recv()\n";
			return 1;
		}
		if (readCount == 0)
		{
			std::cerr << "Client " << fd << " has left\n";
			return 1;
		}
		buffer[readCount] = 0;
		message += buffer;
	} while (message.find('\n') == std::string::npos);

	message.erase(message.find('\n'));
	if (message.length() > 510)
		message.erase(510);
	message += "\r\n";
	return 0;
}

void Server::exeMessage(Client * sender, std::string & message)
{
	SplitMsg split(message);
	
	if (split.getParams().size() > 15)
		return;

	const std::string & command = split.getCommand();

	if (caseInsensEqual(command, "pass"))
		cmdPass(sender, split.getParams());
	else if (caseInsensEqual(command, "nick"))
		cmdNick(sender, split.getParams());
	else if (caseInsensEqual(command, "user"))
		cmdUser(sender, split.getParams());
}

void Server::run()
{
	int ret;
	size_t currentSize;
	bool closeClient;

	do
	{
		std::cerr << "Waiting for client to connect ... \n";
		if ((ret = poll(fds, fdCount, -1)) < 0)
		{
			if (on == true)
				std::cerr << "Error: poll()\n";
			break;
		}
		currentSize = fdCount;
		for (size_t i = 0; i < currentSize; i++)
		{
			if (fds[i].revents == 0)
				continue;
			if (fds[i].revents != POLLIN)
			{
				std::cerr << "Fatal error: revents = " << fds[i].revents << '\n';
				on = false;
			}
			if (fds[i].fd == serverSock)
				addNewClient();
			else
			{
				std::cerr << "Reading client socket " << fds[i].fd << '\n';
				std::string message;
				closeClient = false;
				if (readMessage(fds[i].fd, message) == 1)
					closeClient = true;
				else
					exeMessage(clients[fds[i].fd], message);
				if (closeClient)
				{
					delete clients[fds[i].fd];
					clients.erase(fds[i].fd);
					close(fds[i].fd);
					fds[i].fd = fds[fdCount - 1].fd;
					--fdCount;
				}
			}
		}
	} while (on);
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

	std::cerr << "Retrieving additional info ... ";
	time(&t);
	timeinfo = localtime(&t);
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
	replies[RPL_WELCOME] = "\r\n";
	replies[RPL_YOURHOST] = ":Your host is " + hostname + ", running version 0\r\n";
	replies[RPL_CREATED] = ":This server was created " + creationDate + "\r\n";
	replies[RPL_MYINFO] = ':' + hostname + " 0 o ov\r\n";
	replies[ERR_NONICKNAMEGIVEN] = ":No nickname given\r\n";
	replies[ERR_ERRONEUSNICKNAME] = ":Erroneous nickname\r\n";
	replies[ERR_NICKNAMEINUSE] = ":Nickname is already in use\r\n";
	replies[ERR_NOTREGISTERED] = ":You have not registered\r\n";
	replies[ERR_NEEDMOREPARAMS] = ":Not enough parameters\r\n";
	replies[ERR_ALREADYREGISTERED] = ":Unauthorized command (already registered)\r\n";
	replies[ERR_PASSWDMISMATCH] = ":Password incorrect\r\n";
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

ssize_t Server::sendNumeric(Client * target, const std::string & numeric, const std::string & param1, const std::string & param2)
{
	std::string reply = ":" + hostname + " " + numeric + " " + target->getNick() + " " + param1 + param2 + replies[numeric];
	return send(target->getSock(), reply.c_str(), std::min(size_t(512),reply.length()), 0);
}

void Server::welcome(Client * target)
{
	sendNumeric(target, RPL_WELCOME, ":Welcome to the Internet Relay Network " + target->getNick() + "!" + target->getUser() + "@" + hostname);
	sendNumeric(target, RPL_YOURHOST);
	sendNumeric(target, RPL_CREATED);
	sendNumeric(target, RPL_MYINFO);

	target->signUp();
}

void Server::exit(bool except, const std::string & msg)
{
	if (except == true)
	{
		std::cerr << "Error\n";
		throw std::runtime_error(msg.c_str());
	}
}