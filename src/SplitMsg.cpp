#include "SplitMsg.hpp"

SplitMsg::SplitMsg(std::string message):
	command(),
	params()
{
	message.erase(0, message.find_first_not_of(" "));
	size_t pos = message.find_first_of(" \r\n");

	command = message.substr(0, pos);
	std::cerr << "command: [" << command << "]\n";

	pos = message.find_first_not_of(" \r\n", pos);
	if (pos == std::string::npos)
		return;
	setParams(message.substr(pos));

	std::cerr << "params:" << params.size() << "\n";
	for (std::vector<std::string>::iterator it = params.begin(); it < params.end(); it++)
	{
		std::cout << *it << '\n';
	}
}

SplitMsg::~SplitMsg()
{
}

void SplitMsg::setParams(std::string message)
{
	while (message.size())
	{
		if (message[0] == ':')
		{
			params.push_back(message);
			break;
		}
		size_t pos = message.find_first_of(" \r\n");
		params.push_back(message.substr(0, pos));
		message.erase(0, message.find_first_not_of(" \r\n", pos));
	}
}