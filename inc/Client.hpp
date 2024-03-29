#pragma once

#include "ft_irc.hpp"
#include "IMsgTarget.hpp"

class Client: public IMsgTarget
{
private:
	unsigned char status;
	std::string nickname;
	std::string username;
	std::string fullname;

	int sock;
	std::string message;
	std::string pingToken;
	std::list<std::string> _channels;

public:
	Client(int fd, const std::string & nick = "*");
	~Client();

	void addStatus(unsigned char to_add);
	void removeStatus(unsigned char to_rmv);
	void setNick(const std::string & newNick);
	void setUser(const std::string & newUser, const std::string & hostname);
	void setSock(int fd);
	void addMessage(const std::string & msg);
	void clearMessage();

	std::list<std::string> getList() const ;
	void addChannel(const std::string & channelName);
	void removeChannel(const std::string & channelName);
	bool isIn(const std::string & channelName);
	void leaveAllChannels();

	void ping(const std::string & token);
	void pong(const std::string & token);

	std::string & getName() { return getNick(); }
	void sendMsg(const std::string & message, IMsgTarget *exception = NULL);

	unsigned char getStatus() { return status; }
	std::string & getNick() { return nickname; }
	std::string & getUser() { return username; }
	std::string getFullName() { return std::string(nickname + fullname); }
	int getSock() { return sock; }
	std::string & getMessage() { return message; }
	std::string getMode() { return (status & CLIENT_OPERATOR) ? "+o":""; }
	std::list<std::string> & getChannels() { return _channels; }
};
