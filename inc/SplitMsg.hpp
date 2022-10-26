#pragma once

#include "ft_irc.hpp"

class SplitMsg
{
private:
	std::string command;
	std::vector<std::string> params;

public:
	SplitMsg(std::string message);
	~SplitMsg();

	std::string & getCommand() { return command; }
	std::vector<std::string> & getParams() { return params; }

private:
	void setParams(std::string message);
};
