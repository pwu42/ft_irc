#include "Server.hpp"
#define NB_CLIENT 123
#define BUFF_SIZE 1024

void Server::_setCommands()
{

	_commands["001"] = &Server::_rpl_welcome;
	_commands["NICK"] = &Server::_cmdNick;
	_commands["PASS"] = &Server::_cmdPass;
}

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
	_setCommands();
}


void Server::ReceiveUser()
{
	_client.setSock(accept(_sock, (struct sockaddr *) &_address, &_addrLenght));
	if (_client.getSock() < 0)
		std::cout << "Error : accept" << std::endl;
}

void Server::usecmd(Message msg)
{
	std::cout << _commands["001"] << std::endl;
	std::cout << &Server::_rpl_welcome << std::endl;
	std::cout << _commands["PASS"] << std::endl;
	std::cout << &Server::_cmdPass << std::endl;
	std::cout << _commands["NICK"] << std::endl;
	std::cout << &Server::_cmdNick << std::endl;
	// this->_commands[msg.getCommand()](msg);
	// _commands["001"](msg);
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
