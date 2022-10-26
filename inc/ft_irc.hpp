#pragma once

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
#include <vector>
#include <map>

#define CLIENT_HAS_PASS 1
#define CLIENT_HAS_NICK 2
#define CLIENT_HAS_USER 4