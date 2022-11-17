#pragma once

#include "ft_irc.hpp"

class SplitMsg
{
private:
	std::string command;
	std::vector<std::string> params;

	std::vector<std::pair<std::string, unsigned char> > replies;

public:
	SplitMsg(const std::string & message);
	~SplitMsg();

	std::string & getCommand() { return command; }
	std::vector<std::string> & getParams() { return params; }
	std::vector<std::pair<std::string, unsigned char> > & getReplyVector() { return replies; }

	void addReply(const std::string & rpl, unsigned char msgTarget = TARGET_NOBODY);
};