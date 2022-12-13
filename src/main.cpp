#include "ft_irc.hpp"
#include "Server.hpp"

void handler(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
	{
		std::cerr << "SignalInterrupt\n";
		on = false;
	}
}

int main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cerr << "ircserv: usage: ./ircserv <port> <password>\n";
		return 1;
	}
	if (std::atoi(av[1]) > 65535 || std::atoi(av[1]) < 1)
	{
		std::cerr << "ircserv: invalid port number: " << std::atoi(av[1]) << '\n';
		return 1;
	}
	if (std::string(av[2]).length() > 128 || std::string(av[2]).length() < 1)
	{
		std::cerr << "ircserv: invalid password\n";
		return 1;
	}
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
	Server server(std::atoi(av[1]), std::string(av[2]));
	try
	{
		server.init();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	server.run();
	return 0;
}
