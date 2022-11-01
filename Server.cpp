#include "Server.hpp"
#define NB_CLIENT 123
#define BUFF_SIZE 1024

Server::Server(std::string port, std::string pass) : _port(port) , _pass(pass)
{
	int enable = 1;

	_address.sin_family = AF_INET;
	_address.sin_port = htons(atoi(_port.c_str()));
	_address.sin_addr.s_addr = INADDR_ANY;
	_addrLenght = sizeof(_address);

	if ((_sock = socket(AF_INET, SOCK_STREAM, 6)) < 0)
	{
		std::cout << "Error : socket" << std::endl;
		return ;
	}

	if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
	{
		std::cout << "Error : setsockopt" << std::endl;
		return ;
	}
	if (bind(_sock, (struct sockaddr *) &_address, sizeof(_address)) < 0)
	{
		std::cout << "Error : bind" << std::endl;
		return ;
	}
	if (listen(_sock, NB_CLIENT) < 0)
	{
		std::cout << "Error : listen" << std::endl;
		return ;
	}

	std::cout << "Success creating server" << std::endl;
}

std::string CmdNick(Message msg)
{
	return (msg.getCommand());
}
void Server::ReceiveUser()
{
	_client.setSock(accept(_sock, (struct sockaddr *) &_address, &_addrLenght));
	if (_client.getSock() < 0)
		std::cout << "Error : accept" << std::endl;
}

std::string Server::usecmd(Message msg)
{
	std::string reply = _commands[msg.getCommand()](msg);
	return(reply);
}

User Server::getClient() const
{
	return(_client);
}

int Server::getClientSock() const
{
	return(_client.getSock());
}

Server::~Server()
{
	if (_sock >= 0)
		close(_sock);
}

int Server::getSock() const
{
	return(_sock);
}
