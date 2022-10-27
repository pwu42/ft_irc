#include "ft_irc.hpp"

ssize_t sendNumeric(int fd, std::string numeric, std::string param1, std::string param2)
{
	std::string reply = param1 + param2 + numeric;
	return send(fd, reply.c_str(), reply.length(), 0);
}