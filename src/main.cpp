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
		std::cerr << "usage: ./ircserv <port> <password>\n";
		return 1;
	}
	// signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	Server server(atoi(av[1]), std::string(av[2]));
	server.run();
	return 0;
}