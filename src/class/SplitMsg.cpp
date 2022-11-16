#include "SplitMsg.hpp"

SplitMsg::SplitMsg(const std::string & message):
	command(),
	params(),
	reply(""),
	target(TARGET_NOBODY)
{
	size_t start = message.find_first_not_of(" ");
	size_t end = message.find_first_of(" \r\n", start);
	command = message.substr(start, end - start);
	
	std::cerr << "command: [" << command << "]\n";

	while ((start = message.find_first_not_of(" \r\n", end)) != std::string::npos)
	{
		if (message[start] == ':')
		{
			end = message.find_first_of("\r\n", start);
			params.push_back(message.substr(start, end - start));
			break;
		}
		end = message.find_first_of(" \r\n", start);
		params.push_back(message.substr(start, end - start));
	}

	std::cerr << "params:" << params.size() << " [ ";
	for (std::vector<std::string>::iterator it = params.begin(); it < params.end(); it++)
	{
		std::cerr << *it << ' ';
	}
	std::cerr << "]\n";
}

SplitMsg::~SplitMsg()
{
}

void SplitMsg::setReply(const std::string & rpl, unsigned char msgTarget)
{
	reply = rpl;
	target = msgTarget;
}