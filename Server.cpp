# include "Server.hpp"
# define NB_CLIENT 123
# define BUFF_SIZE 1024

void Server::_setCommands()
{
	_commands["NICK"] = &Server::_cmdNick;
	_commands["PASS"] = &Server::_cmdPass;
}

void Server::_setReply()
{
	_reply[RPL_WELCOME] = &Server::_rpl_welcome;
	_reply[ERR_NONICKNAMEGIVEN] = &Server::_err_noNicknameGiven;
	_reply[ERR_ERRONEUSNICKNAME] = &Server::_err_erroneusNickname;
	_reply[ERR_NICKNAMEINUSE] = &Server::_err_nicknameInUse;
	_reply[ERR_NEEDMOREPARAMS] = &Server::_err_needMoreParams;
	_reply[ERR_ALREADYREGISTERED] = &Server::_err_alreadyRegistered;
	_reply[ERR_PASSWDMISMATCH] = &Server::_err_passwdMisMatch;
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
	_setReply();
}


void Server::ReceiveUser()
{
	_client.setSock(accept(_sock, (struct sockaddr *) &_address, &_addrLenght));
	if (_client.getSock() < 0)
		std::cout << "Error : accept" << std::endl;
}

void Server::usecmd(Message &msg)
{

	if (_commands.count(msg.getCommand()) == 0)
		std::cout << "Command not found : " << msg.getCommand() << std::endl;
	else
		(this->*_commands[msg.getCommand()])(msg);
}

void Server::callReply(unsigned int rpl_number, Message &msg)
{
	if (_reply.count(rpl_number) == 0)
		std::cout << "Reply not found : " << rpl_number << std::endl;
	else
		(this->*_reply[rpl_number])(msg);
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
