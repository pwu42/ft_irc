#include "Server.hpp"

void Server::sendReply(Client * sender, SplitMsg & message)
{
	const std::vector<std::pair<std::string, unsigned char> > & replyVector = message.getReplyVector();
	for (std::vector<std::pair<std::string, unsigned char> >::const_iterator it = replyVector.begin(); it != replyVector.end(); it++)
	{
		switch (it->second)
		{
		case TARGET_SENDER:
			send(sender->getSock(), it->first.c_str(), it->first.length(), 0);
			break;
		case TARGET_ALL: // add function to get all clients that share a channel w/ sender
			send(sender->getSock(), it->first.c_str(), it->first.length(), 0);
			break;

		default:
			break;
		}
	}
}

void Server::welcome(Client * target, SplitMsg & message)
{
	message.addReply(':' + hostname + ' ' + RPL_WELCOME + ' ' + target->getNick() + ' ' + replies[RPL_WELCOME] + target->getNick() + "!" + target->getUser() + "@" + hostname + "\r\n", TARGET_SENDER);
	message.addReply(':' + hostname + ' ' + RPL_YOURHOST + ' ' + target->getNick() + ' ' + replies[RPL_YOURHOST], TARGET_SENDER);
	message.addReply(':' + hostname + ' ' + RPL_CREATED + ' ' + target->getNick() + ' ' + replies[RPL_CREATED], TARGET_SENDER);
	message.addReply(':' + hostname + ' ' + RPL_MYINFO + ' ' + target->getNick() + ' ' + replies[RPL_MYINFO], TARGET_SENDER);

	target->signUp();
}