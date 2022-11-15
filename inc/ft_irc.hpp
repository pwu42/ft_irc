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
#include <map>
#include <algorithm>

enum clientStatus
{
	CLIENT_HAS_PASS = 1,
	CLIENT_HAS_NICK = 2,
	CLIENT_HAS_USER = 4,
	CLIENT_REGISTER = 8,
	CLIENT_OPERATOR = 16
};

#define ALNUMSPHY "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-"
#define SPECIAL "[]\\`_^{|}"
#define NULSPCRLFAT "\0\r\n @"

#define RPL_WELCOME "001"
#define RPL_YOURHOST "002"
#define RPL_CREATED "003"
#define RPL_MYINFO "004"
#define ERR_NOSUCHSERVER "402"
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_ERRONEUSNICKNAME "432"
#define ERR_NICKNAMEINUSE "433"
#define ERR_NOTREGISTERED "451"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_ALREADYREGISTERED "462"
#define ERR_PASSWDMISMATCH "464"