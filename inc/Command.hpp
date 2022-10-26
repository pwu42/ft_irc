#pragma once

#include "ft_irc.hpp"

class Command
{
private:
	std::string command;
	std::vector<std::string> params;

public:
	Command(std::string message);
	~Command();

private:
	void findParams(std::string message);
};
