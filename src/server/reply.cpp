#include "Server.hpp"

void Server::reply(Client * sender, SplitMsg & message)
{
	(void)sender;
	const std::map<IMsgTarget *, std::string> replies = message.getReplies();
	for (std::map<IMsgTarget *, std::string>::const_iterator it = replies.begin(); it != replies.end(); it++)
	{
		std::cerr << "reply = [" << it->second << "]\n";
		if (it->first)
			it->first->sendMsg(it->second, sender);
		else
		{	//send to all channels sender is in
			for (std::map<int, Client *>::const_iterator it2 = clients.begin(); it2 != clients.end(); it2++)
				send(it2->second->getSock(), it->second.c_str(), it->second.length(), MSG_NOSIGNAL);
		}
	}
}

void Server::welcome(Client * target, SplitMsg & message)
{
	message.addReply(':' + hostname + ' ' + RPL_WELCOME + ' ' + target->getNick() + ' ' + replies[RPL_WELCOME] + target->getNick() + "!" + target->getUser() + "@" + hostname + "\r\n", target);
	message.addReply(':' + hostname + ' ' + RPL_YOURHOST + ' ' + target->getNick() + ' ' + replies[RPL_YOURHOST], target);
	message.addReply(':' + hostname + ' ' + RPL_CREATED + ' ' + target->getNick() + ' ' + replies[RPL_CREATED], target);
	message.addReply(':' + hostname + ' ' + RPL_MYINFO + ' ' + target->getNick() + ' ' + replies[RPL_MYINFO], target);
	target->addStatus(CLIENT_REGISTER);
}