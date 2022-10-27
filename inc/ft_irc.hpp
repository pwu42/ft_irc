#pragma once

#include <csignal>
#include <cstdlib>
#include <cstring>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>

#define CLIENT_HAS_PASS 1
#define CLIENT_HAS_NICK 2
#define CLIENT_HAS_USER 4
#define CLIENT_REGISTERED 7

#define ALNUMSPHY "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]\\`_^{|}-"
#define SPECIAL "[]\\`_^{|}"

#define ERR_ALREADYREGISTERED ":Unauthorized command (already registered)\r\n"
#define ERR_NEEDMOREPARAMS ":Not enough parameters\r\n"
#define ERR_PASSWDMISMATCH ":Password incorrect\r\n"
#define ERR_NOTREGISTERED ":You have not registered\r\n"
#define ERR_NONICKNAMEGIVEN ":No nickname given\r\n"
#define ERR_ERRONEUSNICKNAME ":Erroneous nickname\r\n"
#define ERR_NICKNAMEINUSE ":Nickname is already in use\r\n"