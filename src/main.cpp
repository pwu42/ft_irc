#include "ft_irc.hpp"
#include "Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "usage: ./ircserv <port> <password>\n";
		return 1;
	}
	Server server(atoi(av[1]), std::string(av[2]));
	server.run();
	return 0;
}