#include "Server.hpp"

void Server::sendReply(Client * sender, SplitMsg & message)
{
	switch (message.getTarget())
	{
	case TARGET_SENDER:
		send(sender->getSock(), message.getReply().c_str(), message.getReply().length(), 0);
		break;
	case TARGET_ALL: // add function to get all clients that share a channel w/ sender
		send(sender->getSock(), message.getReply().c_str(), message.getReply().length(), 0);
		break;

	default:
		break;
	}
}

void Server::sendNumeric(Client * target, const std::string & numeric, const std::string & param1, const std::string & param2)
{
	std::string reply = ":" + hostname + " " + numeric + " " + target->getNick() + " " + param1 + param2 + replies[numeric];
	send(target->getSock(), reply.c_str(), reply.length(), 0);
}

void Server::welcome(Client * target)
{
	sendNumeric(target, RPL_WELCOME, ":Welcome to the Internet Relay Network " + target->getNick() + "!" + target->getUser() + "@" + hostname);
	sendNumeric(target, RPL_YOURHOST);
	sendNumeric(target, RPL_CREATED);
	sendNumeric(target, RPL_MYINFO);

	target->signUp();
}