#pragma once

#include "ft_irc.hpp"
#include "Client.hpp"

//
class Channel : public IMsgTarget
{
private:
	std::string _name; // start with "&#+!", max length 50, case insens, no "\7 ,:"
	std::string _topic;
	std::string _topicSetat;
	std::string _topicOps;
	std::map<int , Client *> _clients;
	Client * _creator;
	std::map<int , Client *> _operators;
	// std::vector<Client *> _operators;


public:
	Channel(const std::string & channelName, Client *creator);
	virtual ~Channel();
	std::string  & getName();
	Client *getCreator() const;
	std::string getTopic() const;
	std::string getTopicOps() const;
	std::string getTopicSetat() const;
	std::string getNumberOfClient() const;
	bool empty();
	void setTopic(std::string topic, Client *ops);
	void addClient(Client * to_add);
	void removeClient(Client * to_rmv);
	void addOper(Client * to_add);
	void removeOper(Client * to_rmv);
	std::string clientsNames();
	Client *isIn(std::string clientName);
	bool clientIsOp(int sock) const;
	void sendMsg(const std::string & message);
};
