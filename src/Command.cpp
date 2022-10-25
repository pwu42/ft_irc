#include "../inc/Command.hpp"

Command::Command(std::string message)
{
	av.push_back(message.substr(message.find(' ')));
}

Command::~Command()
{
}
