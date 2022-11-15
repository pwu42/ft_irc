#pragma once

#include "ft_irc.hpp"
#include "Client.hpp"

class Channel
{
private:
	std::string name; // start with "&#+!", max length 50, case insens, no "\7 ,:"
	std::vector<Client *> clients;

	Client * creator;
	std::vector<Client *> operators;


	void sendAll(std::string & message);

public:
	Channel(const std::string & channelName);
	~Channel();
};

Channel::Channel(const std::string & channelName):
	name(channelName)
{
}

Channel::~Channel()
{
}

void Channel::sendAll(std::string & message)
{
	for (std::vector<Client *>::iterator it = clients.begin(); it != clients.end(); it++)
	{
		send((*it)->getSock(), message.c_str(), message.length(), 0);
	}
}