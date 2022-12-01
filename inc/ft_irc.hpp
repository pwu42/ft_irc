#pragma once

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/resource.h>
#include <errno.h>

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>

enum clientStatus
{
	CLIENT_HAS_PASS = 1,
	CLIENT_HAS_NICK = 2,
	CLIENT_HAS_USER = 4,
	CLIENT_REGISTER = 8,
	CLIENT_OPERATOR = 16,
	CLIENT_HAS_QUIT = 32,
	CLIENT_PING = 64
};

#define OPER_NAME "admin"
#define OPER_PASS "00000000"

#define POLL_TIMEOUT 180

#define ALNUMSPHY "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-"
#define SPECIAL "[]\\`_^{|}"
#define NULSPCRLFAT "\0\r\n @"

#define RPL_WELCOME "001"
#define RPL_YOURHOST "002"
#define RPL_CREATED "003"
#define RPL_MYINFO "004"
#define RPL_UMODEIS "221"
#define RPL_NOTOPIC "331"
#define RPL_TOPIC "332"
#define RPL_TOPICWHOTIME "333"
#define RPL_NAMREPLY "353"
#define RPL_ENDOFNAMES "366"
#define RPL_YOUREOPER "381"
#define ERR_NOSUCHNICK "401"
#define ERR_NOSUCHSERVER "402"
#define ERR_NORECIPIENT "411"
#define ERR_NOTEXTTOSEND "412"
#define ERR_UNKNOWNCOMMAND "421"
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_ERRONEUSNICKNAME "432"
#define ERR_NICKNAMEINUSE "433"
#define ERR_NOTREGISTERED "451"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_ALREADYREGISTERED "462"
#define ERR_PASSWDMISMATCH "464"
#define ERR_BADCHANMASK "476"
#define ERR_NOPRIVILEGES "481"
#define ERR_NOOPERHOST "491"
#define ERR_UMODEUNKNOWNFLAG "501"
#define ERR_USERSDONTMATCH "502"
