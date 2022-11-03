#include "ft_irc.hpp"
#include "Server.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "usage: ./ircserv port password\n";
		return 1;
	}
	try
	{
		Server server(atoi(av[1]), std::string(av[2]));
		server.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}