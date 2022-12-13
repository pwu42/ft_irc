#include "ft_irc.hpp"
#include "Bot.hpp"

bool bot_on = false;

void handler(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
	{
		std::cerr << "SignalInterrupt\n";
		bot_on = false;
	}
}

int checkArgs(int ac, char ** av)
{
	if (ac != 3)
	{
		std::cerr << "bot: usage: ./bot <port> <password>\n";
		return -1;
	}
	std::string port(av[1]);
	if (std::atoi(av[1]) > 65535 || std::atoi(av[1]) < 1 || port.find_first_not_of("0123456789") != std::string::npos)
	{
		std::cerr << "bot: invalid port number: " << av[1] << '\n';
		return -1;
	}
	std::string password(av[2]);
	if (password.length() > 128 || password.length() < 1 || password.find_first_not_of(PRINTABLE) != std::string::npos)
	{
		std::cerr << "bot: invalid password\n";
		return -1;
	}
	return 0;
}

int main(int ac, char ** av)
{
	Bot bot;

	int port;
	std::string password;

	if (checkArgs(ac, av) == -1)
		return 1;
	port = std::atoi(av[1]);
	password = av[2];

	signal(SIGQUIT, handler);
	signal(SIGINT, handler);

	try
	{
		bot.init(port, password);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	bot.run();
	return 0;
}