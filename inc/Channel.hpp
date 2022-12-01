#pragma once

#include "ft_irc.hpp"
#include "Client.hpp"

// : public IMsgTarget
class Channel
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


	void sendMsg(std::string & message);

public:
	Channel(const std::string & channelName, Client *creator);
	virtual ~Channel();
	std::string  & getName();
	std::string getTopic() const;
	std::string getTopicOps() const;
	std::string getTopicSetat() const;
	bool empty();
	void setTopic(std::string topic, Client *ops);
	void addClient(Client * to_add);
	void removeClient(Client * to_rmv);
	void addOper(Client * to_add);
	void removeOper(Client * to_rmv);
	// 			bool UserIsOp();
};
