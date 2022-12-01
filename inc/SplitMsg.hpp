#pragma once

#include "ft_irc.hpp"
#include "IMsgTarget.hpp"

class SplitMsg
{
private:
	std::string command;
	std::vector<std::string> params;

	std::vector<std::pair<std::string, IMsgTarget *> > replies; //c'est quoi ?

public:
	SplitMsg(const std::string & message);
	~SplitMsg();

	std::string & getCommand() { return command; }
	std::vector<std::string> & getParams() { return params; }
	std::vector<std::pair<std::string, IMsgTarget *> > & getReplyVector() { return replies; }

	void addReply(const std::string & rpl, IMsgTarget * msgTarget);
};
