#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <csignal>
#include <cstdlib>
#include <cstring>

#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
# include <map>
# include <string>

class Message
{
	private :
		int _socket;
		std::string _command;
		std::string _args;
		std::string _message;
		std::string _reply;

	public :
		Message(int socket);

		std::string getCommand() const ;
		std::string getArgs() const ;
		std::string getMessage() const ;
		std::string getReply() const ;

		void setCommand(std::string const &command);
		void setArgs(std::string const &args);
		void setMessage(std::string const &message);
		void setReply(std::string const &reply);

		bool receiveMsg();
		bool sendMsg();
		
		~Message();
};

#endif
