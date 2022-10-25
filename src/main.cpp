#include "../inc/ft_irc.hpp"

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
		return 1;
	}
	try
	{
		server->run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	delete server;
	return 0;
}