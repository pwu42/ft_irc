#ifndef COMMANDS_HPP
#define COMMANDS_HPP
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
#include "User.hpp"
#include "Message.hpp"

typedef std::string (*FPTR)(Message, User &);

std::string rpl_welcome(Message msg, User &client);
std::string cmdNick(Message msg, User &client);
std::string cmdPass(Message msg, User &client);
void setCommands();

#endif
