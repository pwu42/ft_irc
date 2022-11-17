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
	for (size_t i = 0; i < fdCount; i++)
	{
		if (i > 0)
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
				perror("accept()");
			break;
		}
		if (fd == int(fdLimit - 1))
		{
			close(fd);
			std::cerr << "Error: Too many connections\n";
			break;
		}
		std::cerr << "New connection on socket " << fd << '\n';
		fds[fdCount].fd = fd;
		fds[fdCount].events = POLLIN;
		++fdCount;
		clients[fd] = new Client(fd);
	} while (fd != -1);
}

int Server::recvMessage(Client * sender)
{
	char buffer[BUF_SIZE + 1];
	ssize_t readCount;

	readCount = recv(sender->getSock(), buffer, BUF_SIZE, 0);
	if (readCount < 0)
	{
		if (errno != EAGAIN && errno != EWOULDBLOCK)
			perror("recv()");
		return 1;
	}
	if (readCount == 0)
	{
		std::cerr << "Client " << sender->getSock() << " has left\n";
		return 1;
	}
	buffer[readCount] = 0;
	std::cerr << "buffer = [" << buffer << "]\n";
	sender->addMessage(buffer);
	return 0;
}

void Server::exeMessage(Client * sender)
{
	while (sender->getMessage().find('\n') != std::string::npos)
	{
		std::string msg = sender->getMessage().substr(0, sender->getMessage().find('\n')) + "\r\n";
		SplitMsg split(msg);

		if (msg.length() < 512 && split.getParams().size() < 15)
		{
			if (caseInsensEqual(split.getCommand(), "pass"))
				cmdPass(sender, split);
			else if (caseInsensEqual(split.getCommand(), "nick"))
				cmdNick(sender, split);
			else if (caseInsensEqual(split.getCommand(), "user"))
				cmdUser(sender, split);
			if (sender->getStatus() & CLIENT_REGISTER)
			{
				if (caseInsensEqual(split.getCommand(), "ping"))
					cmdPing(sender, split);
				if (caseInsensEqual(split.getCommand(), "oper"))
					cmdOper(sender, split);
				// other commands
			}
			sendReply(sender, split);
		}
		sender->getMessage().erase(0, sender->getMessage().find('\n') + 1);
	}
}

void Server::run()
{
	int ret;
	size_t currentSize;
	bool closeClient;

	do
	{
		std::cerr << "Polling ... \n";
		if ((ret = poll(fds, fdCount, -1)) < 0) // ping all on timeout
		{
			if (on == true)
				perror("poll()");
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
				closeClient = false;
				if (recvMessage(clients[fds[i].fd]) == 1)
					closeClient = true;
				else
					exeMessage(clients[fds[i].fd]);
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

void Server::exit(bool except, const std::string & msg)
{
	if (except == true)
	{
		std::cerr << "Error\n";
		throw std::runtime_error(msg.c_str());
	}
}