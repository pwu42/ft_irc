#pragma once

#include "ft_irc.hpp"

class IMsgTarget
{
public:
	IMsgTarget() {}
	virtual ~IMsgTarget() {}

	virtual std::string & getName() = 0;
	virtual void sendMsg(const std::string & message, IMsgTarget *exception = NULL) = 0;

};
