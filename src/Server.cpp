#include "../inc/Server.hpp"

bool serv_on = false;

Server::Server(int port, std::string pass):
	_port(port),
	_pass(pass)
{
	int opt = 1;
	std::cerr << "Creating socket ... ";
	if ((_server_sock = socket(AF_INET, SOCK_STREAM, 6)) < 0)
		throw std::runtime_error("Error\nsocket()");
	if (setsockopt(_server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Error\nsetsockopt()");
	// if (fcntl(_server_sock, F_SETFL, O_NONBLOCK) < 0)
	// 	throw std::runtime_error("Error\nfcntl()");
	
	_address.sin_family = AF_INET;
	_address.sin_addr.s_addr = INADDR_ANY;
	_address.sin_port = htons(_port);
	_address_len = sizeof(_address);
	if (bind(_server_sock, reinterpret_cast<struct sockaddr *>(&_address), _address_len) < 0)
		throw std::runtime_error("Error\nbind()");
	if (listen(_server_sock, 4) < 0)
		throw std::runtime_error("Error\nlisten()");

	std::cout << "Done\n";

	if ((_client_sock = accept(_server_sock, reinterpret_cast<struct sockaddr *>(&_address), &_address_len)) < 0)
		throw std::runtime_error("Error\naccept()");
	serv_on = true;
}

Server::~Server()
{
	close(_client_sock);
	close(_server_sock);
}

void handler(int signo)
{
	if (signo == SIGINT)
		serv_on = false;
}

void Server::run()
{
	signal(SIGINT, handler);
	do
	{
		if (recv(_client_sock, _buffer, BUF_SIZE, 0) < 0)
			throw std::runtime_error("Error\nrecv()");
		// parsing, replying, etc
		send(_client_sock, "test\n", 5, 0); // receive command here
	} while (serv_on == true);
}