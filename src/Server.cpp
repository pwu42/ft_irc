#include "Server.hpp"

bool on = false;

Server::Server(int port, std::string pass):
	port(port),
	pass(pass),
	serverSock(-2),
	clientSock(-2)
{
	std::cerr << " o0o0o0o Server is starting o0o0o0o\n";
	// signal(SIGINT, handler);
	signal(SIGQUIT, handler);
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

int Server::readMessage(std::string & message)
{
	char buffer[BUF_SIZE + 1];
	ssize_t readCount;

	while (message.find('\n') == std::string::npos)
	{
		if ((readCount = recv(clientSock, buffer, BUF_SIZE, 0)) < 0)
			exit(true, "Error\nrecv()");
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
	{
		message.erase(510);
	}
	message += "\r\n";
	return 0;
}

void Server::exeMessage(SplitMsg & message)
{
	std::string command = message.getCommand();

}

void Server::run()
{
	std::cerr << "Waiting for client to connect ... ";
	if ((clientSock = accept(serverSock, reinterpret_cast<struct sockaddr *>(&address), &addrLength)) < 0)
		exit(true, "Error\naccept()");

	std::cerr << "Done\n";

	do
	{
		std::string message;
		if (readMessage(message) == 1)
			return;

		SplitMsg split(message);
		exeMessage(split);
		send(clientSock, message.c_str(), message.length(), 0);
	} while (on == true);
}

void Server::initSocket()
{
	int opt = 1;

	std::cerr << "Creating socket ... ";
	if ((serverSock = socket(AF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 6)) < 0)
		exit(true, "Error\nsocket()");
	if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		exit(true, "Error\nsetsockopt()");
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	addrLength = sizeof(address);
	if (bind(serverSock, reinterpret_cast<struct sockaddr *>(&address), addrLength) < 0)
		exit(true, "Error\nbind()");
	if (listen(serverSock, 4) < 0)
		exit(true, "Error\nlisten()");

	std::cerr << "Done\n";
}

void Server::exit(bool except, std::string msg)
{
	if (clientSock > 0)
		close(clientSock);
	if (serverSock > 0)
		close(serverSock);
	if (except == true)
		throw std::runtime_error(msg.c_str());
}