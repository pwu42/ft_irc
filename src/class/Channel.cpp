#include "Channel.hpp"

Channel::Channel(const std::string & channelName, Client *creator):
	_name(channelName), _creator(creator)
{
	(void)_creator;
}

Channel::~Channel()
{
}

std::string & Channel::getName()
{
	return(_name);
}

std::string Channel::getTopic() const
{
	return(_topic);
}

std::string Channel::getTopicOps() const
{
	return(_topicOps);
}

std::string Channel::getTopicSetat() const
{
	return(_topicSetat);
}

void Channel::setTopic(std::string topic, Client *ops)
{
	_topic = topic;
	_topicSetat = "AA";
	_topicOps = ops->getNick();
}

bool Channel::empty()
{
	if (_clients.empty())
		return true;
	return false;
}

void Channel::addClient(Client * to_add)
{
	_clients[to_add->getSock()] = to_add;
}

void Channel::removeClient(Client * to_rmv)
{
	_clients.erase(to_rmv->getSock());
}

void Channel::addOper(Client * to_add)
{
	_operators[to_add->getSock()] = to_add;
}

void Channel::removeOper(Client * to_rmv)
{
	_operators.erase(to_rmv->getSock());
}

void Channel::sendMsg(std::string & message)
{
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		send(it->first, message.c_str(), message.length(), 0);
	}
}

// void Channel::sendAll(std::string & message)
// {
// 	for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
// 	{
// 		send((*it)->getSock(), message.c_str(), message.length(), 0);
// 	}
// }
