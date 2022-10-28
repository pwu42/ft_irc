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

void Message::setCommand(std::string const &command)
{
	_command = command;
}

void Message::setArgs(std::string const &args)
{
	_args = args;
}

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
	char *buffer[BUFF_SIZE];
	if (recv(_socket, buffer, BUFF_SIZE, 0) < 0)
	{
		 std::cout << "Error : recv" << std::endl;
		 return (true);
	}
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

Message::~Message()
{
}
