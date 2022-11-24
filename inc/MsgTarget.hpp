#pragma once

#include "ft_irc.hpp"

class MsgTarget
{
public:
	MsgTarget() {}
	~MsgTarget() {}

	virtual void sendMsg(const std::string & msg) = 0;
};