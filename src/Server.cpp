#include "../inc/Server.hpp"

bool serv_on = false;

Server::Server(int port, std::string pass):
	Port(port),
	Pass(pass),
	ServerSock(-2),
	ClientSock(-2)
{
	std::cerr << " o0o0o0o Server is starting o0o0o0o\n";
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	InitSocket();
	serv_on = true;
}

Server::~Server()
{
	Exit();
}

void handler(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
		serv_on = false;
}

void Server::Run()
{
	int ret;

	std::cerr << "Waiting for client to connect ... ";

	if ((ClientSock = accept(ServerSock, reinterpret_cast<struct sockaddr *>(&Address), &AddrLength)) < 0)
		Exit(true, "Error\naccept()");

	std::cerr << "Done\n";

	do
	{
		if ((ret = recv(ClientSock, Buffer, BUF_SIZE, 0)) < 0)
			Exit(true, "Error\nrecv()");
		if (ret <= 0)
		{
			std::cerr << "Client has left\n";
			break;
		}
		// parsing, replying, etc
		send(ClientSock, Buffer, strlen(Buffer), 0); // receive command here
	} while (serv_on == true);
}

void Server::InitSocket()
{
	int opt = 1;

	std::cerr << "Creating socket ... ";
	if ((ServerSock = socket(AF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 6)) < 0)
		Exit(true, "Error\nsocket()");
	if (setsockopt(ServerSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		Exit(true, "Error\nsetsockopt()");
	
	Address.sin_family = AF_INET;
	Address.sin_addr.s_addr = INADDR_ANY;
	Address.sin_port = htons(Port);
	AddrLength = sizeof(Address);
	if (bind(ServerSock, reinterpret_cast<struct sockaddr *>(&Address), AddrLength) < 0)
		Exit(true, "Error\nbind()");
	if (listen(ServerSock, 4) < 0)
		Exit(true, "Error\nlisten()");

	std::cerr << "Done\n";
}

void Server::Exit(bool ex, std::string msg)
{
	if (ServerSock > 0)
		close(ServerSock);
	if (ClientSock > 0)
		close(ClientSock);
	if (ex == true)
		throw std::runtime_error(msg.c_str());
}