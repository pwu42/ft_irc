#include "SplitMsg.hpp"

SplitMsg::SplitMsg(const std::string & message)
{
	size_t cmdstart = 0;
	if (message[0] == ':')
		cmdstart += (prefix = message.substr(1, message.find_first_of(" 	") - 1)).length() + 1;
	size_t start = message.find_first_not_of(" 	", cmdstart);
	size_t end = message.find_first_of(" 	\r\n", start);
	command = message.substr(start, end - start);
	
	// std::cerr << "prefix: [" << prefix << "]\n";
	// std::cerr << "command: [" << command << "]\n";

	while ((start = message.find_first_not_of(" 	\r\n", end)) != std::string::npos)
	{
		if (message[start] == ':')
		{
			end = message.find_first_of("\r\n", start);
			params.push_back(message.substr(start + 1, end - start - 1));
			break;
		}
		end = message.find_first_of(" 	\r\n", start);
		params.push_back(message.substr(start, end - start));
	}

	// std::cerr << "params:" << params.size() << " [ ";
	// for (std::vector<std::string>::iterator it = params.begin(); it < params.end(); it++)
	// {
	// 	std::cerr << *it << ' ';
	// }
	// std::cerr << "]\n";
}

SplitMsg::~SplitMsg()
{
}

void SplitMsg::addReply(const std::string & rpl, IMsgTarget * msgTarget)
{
	replies[msgTarget] += rpl;
}