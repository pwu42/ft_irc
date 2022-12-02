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
	if (atoi(av[1]) > 65535 || atoi(av[1]) < 1)
	{
		std::cerr << "ircserv: invalid port number: " << atoi(av[1]) << '\n';
		return 1;
	}
	signal(SIGQUIT, handler);
	Server server(atoi(av[1]), std::string(av[2]));
	// signal(SIGINT, handler);
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
