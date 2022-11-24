#include "Server.hpp"

void Server::reply(SplitMsg & message)
{
	const std::vector<std::pair<std::string, MsgTarget *> > & replyVector = message.getReplyVector();
	for (std::vector<std::pair<std::string, MsgTarget *> >::const_iterator it = replyVector.begin(); it != replyVector.end(); it++)
	{
		if (it->second)
			it->second->sendMsg(it->first);
		else
		{
			for (std::map<int, Client *>::const_iterator it2 = clients.begin(); it2 != clients.end(); it2++)
				send(it2->second->getSock(), it->first.c_str(), it->first.length(), 0);
		}
	}
}

void Server::welcome(Client * target, SplitMsg & message)
{
	message.addReply(':' + hostname + ' ' + RPL_WELCOME + ' ' + target->getNick() + ' ' + replies[RPL_WELCOME] + target->getNick() + "!" + target->getUser() + "@" + hostname + "\r\n", target);
	message.addReply(':' + hostname + ' ' + RPL_YOURHOST + ' ' + target->getNick() + ' ' + replies[RPL_YOURHOST], target);
	message.addReply(':' + hostname + ' ' + RPL_CREATED + ' ' + target->getNick() + ' ' + replies[RPL_CREATED], target);
	message.addReply(':' + hostname + ' ' + RPL_MYINFO + ' ' + target->getNick() + ' ' + replies[RPL_MYINFO], target);
	target->signUp();
}