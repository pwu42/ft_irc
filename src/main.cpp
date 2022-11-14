#include "ft_irc.hpp"
#include "Server.hpp"

int main(int ac, char **av)
{
	Server * server = NULL;
	if (ac != 3)
	{
		std::cerr << "usage: ./ircserv port password\n";
		return 1;
	}
	try
	{
		server = new Server(atoi(av[1]), std::string(av[2]));
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	server->run();
	delete server;
	return 0;
}