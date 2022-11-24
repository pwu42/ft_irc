#pragma once

#include "ft_irc.hpp"
#include "MsgTarget.hpp"

class SplitMsg
{
private:
	std::string command;
	std::vector<std::string> params;

	std::vector<std::pair<std::string, MsgTarget *> > replies;

public:
	SplitMsg(const std::string & message);
	~SplitMsg();

	std::string & getCommand() { return command; }
	std::vector<std::string> & getParams() { return params; }
	std::vector<std::pair<std::string, MsgTarget *> > & getReplyVector() { return replies; }

	void addReply(const std::string & rpl, MsgTarget * msgTarget);
};