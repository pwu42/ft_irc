// #include <string>
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
#include "Server.hpp"
#include "User.hpp"
#include "Message.hpp"
#include "Commands.hpp"

#define BUFF_SIZE 1024

int main(int argc, char **argv)
{
	bool error = false;
	std::map<std::string, FPTR> commands;

	if (argc != 3)
		return 0;
	Server mine(argv[1], argv[2]);

	mine.ReceiveUser();
	Message newmsg(mine.getClientSock());
	while (error == false)
	{
		error = newmsg.receiveMsg();
		if (!error)
		{
			// newmsg.setReply(mine.usecmd(newmsg));
			error = newmsg.sendMsg();
		}
	}
}
// nc localhost 1667

// ./proxy.sh 4243 irc.ircube.org 6667
// /connect localhost 4243
