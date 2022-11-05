#include "Message.hpp"
#define BUFF_SIZE 1024

Message::Message(int socket) : _socket(socket) , _reply("Salut vous \r\n")
{
}

std::string Message::getCommand() const
{
	return (_command);
}

std::string Message::getArgs() const
{
	return (_args);
}

std::string Message::getMessage() const
{
	return (_message);
}

std::string Message::getReply() const
{
	return (_reply);
}

// void Message::setCommand(std::string const &command)
// {
// 	_command = command;
// }

// void Message::setArgs(std::string const &args)
// {
// 	_args = args;
// }

void Message::setMessage(std::string const &message)
{
	_message = message;
}

void Message::setReply(std::string const &reply)
{
	_reply = reply;
}

bool Message::receiveMsg()
{
	char buffer[BUFF_SIZE];
	int cmdlen;
	bzero(buffer, BUFF_SIZE);
	if ((cmdlen = recv(_socket, buffer, BUFF_SIZE, 0)) < 0)
	{
		 std::cout << "Error : recv" << std::endl;
		 return (true);
	}
	_message = buffer;
	_parseReceive();
	return (false);
}

bool Message::sendMsg()
{
	if (send(_socket, _reply.c_str(), _reply.size(), MSG_DONTWAIT) < 0)
	{
		std::cout << "Error : send" << std::endl;
		return (true);
	}
	return (false);
}

void Message::_parseReceive()
{
	char *tmp;
	char *str = (char *)_message.c_str();

	// _args = "";
	_command = std::strtok(str, " ");
	while ((tmp = std::strtok(NULL, " ")) && !(tmp[0] == ':'))
	{
		std::cout << tmp << '\n';
		_args += tmp; //vector ou untruc ta vue
	}
 	if (tmp)
		_message = tmp;
	else
		_message = "";

	std::cout << "--------------------------------" << _message << "-----------------------------------------------------"<< std::endl;

	std::cout << "Command == "<< _command << std::endl;
	std::cout << "Args == "<< _args << std::endl;
	std::cout << "Message == "<< _message << std::endl;
}

Message::~Message()
{
}
