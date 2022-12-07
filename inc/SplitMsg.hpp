#pragma once

#include "ft_irc.hpp"
#include "IMsgTarget.hpp"

class SplitMsg
{
private:
	std::string prefix;
	std::string command;
	std::vector<std::string> params;

	std::map<IMsgTarget *, std::string> replies;

public:
	SplitMsg(const std::string & message);
	~SplitMsg();

	std::string & getCommand() { return command; }
	std::string & getPrefix() { return prefix; }
	std::vector<std::string> & getParams() { return params; }
	std::map<IMsgTarget *, std::string> & getReplies() { return replies; }

	void addReply(const std::string & rpl, IMsgTarget * msgTarget);
};
