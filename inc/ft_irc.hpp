#pragma once

#include <sys/socket.h>
#include <netdb.h>
#include <csignal>
#include <poll.h>
#include <unistd.h>
#include <fcntl.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "../inc/Server.hpp"

extern bool serv_on;