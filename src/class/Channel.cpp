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

std::string Channel::getNumberOfClient() const
{

	std::stringstream sstream;
	sstream << _clients.size();
	std::string str = sstream.str();
	return(str);
}

void Channel::setTopic(std::string topic, Client *ops)
{
	time_t tmp;
	struct tm * timeinfo;

	_topic = topic;
	time(&tmp);
	timeinfo = localtime(&tmp);
	_topicSetat = asctime(timeinfo);
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
	if (clientIsOp(to_rmv->getSock()))
		removeOper(to_rmv);
}

void Channel::addOper(Client * to_add)
{
	_operators[to_add->getSock()] = to_add;
}

void Channel::removeOper(Client * to_rmv)
{
	_operators.erase(to_rmv->getSock());
}

std::string Channel::clientsNames()
{
	std::string ret;
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		ret = " " + it->second->getNick();
	}
	return ret;
}


void Channel::sendMsg(const std::string & message)
{
	for (std::map<int, Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		send(it->first, message.c_str(), message.length(), 0);
	}
}

bool Channel::clientIsOp(int sock) const
{
	if (_operators.count(sock) > 0)
		return true;
	return false;
}

Client *Channel::isIn(std::string clientName)
{
	for (std::map<int, Client *>::const_iterator it = _clients.begin(); it != _clients.end(); it++)
		if (caseInsensEqual(clientName, it->second->getNick()))
			return it->second;
	return (NULL);
}
// void Channel::sendAll(std::string & message)
// {
// 	for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
// 	{
// 		send((*it)->getSock(), message.c_str(), message.length(), 0);
// 	}
// }
