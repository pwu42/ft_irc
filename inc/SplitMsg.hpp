#pragma once

#include "ft_irc.hpp"

class SplitMsg
{
private:
	std::string command;
	std::vector<std::string> params;

	std::string reply;
	unsigned char target;

public:
	SplitMsg(const std::string & message);
	~SplitMsg();

	std::string & getCommand() { return command; }
	std::vector<std::string> & getParams() { return params; }
	unsigned char getTarget() { return target; }
	std::string & getReply() { return reply; }

	void setReply(const std::string & rpl, unsigned char msgTarget = TARGET_NOBODY);
};