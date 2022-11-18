#include "Server.hpp"

void Server::reply(Client * sender, SplitMsg & message)
{
	const std::vector<std::pair<std::string, unsigned char> > & replyVector = message.getReplyVector();
	for (std::vector<std::pair<std::string, unsigned char> >::const_iterator it = replyVector.begin(); it != replyVector.end(); it++)
	{
		switch (it->second)
		{
		case TARGET_SENDER:
			send(sender->getSock(), it->first.c_str(), it->first.length(), 0);
			break;
		case TARGET_ALL: // all clients that share a channel w/ sender
			for (std::map<int, Client *>::const_iterator it2 = clients.begin(); it2 != clients.end(); it2++)
				send(it2->second->getSock(), it->first.c_str(), it->first.length(), 0);
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