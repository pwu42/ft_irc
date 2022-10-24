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
// int main(int argc, char **argv)
// {
// 	if (argc != 3)
// 		return 0;
// 	std::string port = argv[1];
// 	std::string password = argv[2];
	// parse port compris entre u_short max 65535 et 0
	// if (port != "6667" || password != "sonic")
// 		return 0;
//
// 	return 1;
// }

int main()
{
	int fd = -2;
	int enable = 1;
	struct sockaddr_in addr; // in for internet
	socklen_t addr_len;

	if ((fd = socket(AF_INET, SOCK_STREAM, 6)) < 0)
		return (std::cout << "Error : socket" << std::endl, 1);
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
		return (std::cout << "Error : setsockopt" << std::endl, 1);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(1667);
	addr.sin_addr.s_addr = INADDR_ANY;
	addr_len = sizeof(addr);
	if (bind(fd, (struct sockaddr *) &addr, addr_len) < 0)
		return (std::cout << "Error : bind" << std::endl, 1);
	if (listen(fd, 123) < 0)
		return (std::cout << "Error : listen" << std::endl, 1);
	int client;
	if ((client = accept(fd, (struct sockaddr *) &addr, &addr_len)) < 0)
		return (std::cout << "Error : listen" << std::endl, 1);
		// accept

	close(fd);
	// loop
	// close
}
