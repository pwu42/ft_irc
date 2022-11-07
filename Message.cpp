# include "Message.hpp"
# define BUFF_SIZE 1024

Message::Message(int socket) : _socket(socket) , _reply("Salut vous \r\n")
{
}

std::string Message::getCommand() const
{
	return (_command);
}

std::vector<std::string> Message::getArgs() const
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
	std::cout << "Message is :   " << _message << std::endl;
	char *tmp;
	char *tmp2;
	std::string cpy(_message.c_str());
	char *str = (char *)cpy.c_str();
// find \r\n ou \n et mettre dans str _message str jusqua \r\n
	if (cpy.size())
	{
		if ((tmp2 = std::strtok(str, " \r\n")))
			_command = tmp2;
	}

	if (!_args.empty())
		_args.clear();
	while ((tmp = std::strtok(NULL, " \r\n")) && !(tmp[0] == ':'))
		_args.push_back(tmp);
 	if (tmp)
	{
		_message = _message.substr(_message.find(" :")  + 2, _message.size() - 1);
	}
	else
		_message = "";

	// std::cout << "Command == "<< _command << std::endl;
	// // std::cout << "Args == "<< _args << std::endl;
	// for (int i = 0; i < _args.size(); i++) {
	//    std::cout << "Args == "<< _args.at(i) << std::endl;
   // }
	// std::cout << "Message == "<< _message << std::endl;
}

Message::~Message()
{
}
