#pragma once

#include <csignal>
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

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define CLIENT_HAS_PASS 1
#define CLIENT_HAS_NICK 2
#define CLIENT_HAS_USER 4
#define CLIENT_REGISTER 8

#define ALNUMSPHY "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-"
#define SPECIAL "[]\\`_^{|}"

#define ERR_NONICKNAMEGIVEN "431"
#define ERR_ERRONEUSNICKNAME "432"
#define ERR_NICKNAMEINUSE "433"
#define ERR_NOTREGISTERED "451"
#define ERR_NEEDMOREPARAMS "461"
#define ERR_ALREADYREGISTERED "462"
#define ERR_PASSWDMISMATCH "464"