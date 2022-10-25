#pragma once

#include "ft_irc.hpp"

class Command
{
private:
	std::vector<std::string> av;

public:
	Command(std::string message);
	~Command();
};
