#include "Server.hpp"

void Server::reply(Client * sender, SplitMsg & message)
{
	const std::map<IMsgTarget *, std::string> replies = message.getReplies();
	for (std::map<IMsgTarget *, std::string>::const_iterator reply_it = replies.begin(); reply_it != replies.end(); reply_it++)
	{
		// std::cerr << "reply to " << reply_it->first << " = [" << reply_it->second << "]\n";
		if (reply_it->first)
			reply_it->first->sendMsg(reply_it->second, sender);
		else
		{
			std::set<Client *> targets;
			targets.insert(sender);
			for (std::list<std::string>::const_iterator chan_it = sender->getChannels().begin(); chan_it != sender->getChannels().end(); chan_it++)
			{
				for (std::map<int, Client *>::const_iterator chan_client_it = reinterpret_cast<Channel *>(findTarget(*chan_it))->getClients().begin(); chan_client_it != reinterpret_cast<Channel *>(findTarget(*chan_it))->getClients().end(); chan_client_it++)
					targets.insert(chan_client_it->second);
			}
			// std::cerr << "Targets: " << targets.size() << '\n';
			for (std::set<Client *>::const_iterator target_it = targets.begin(); target_it != targets.end(); target_it++)
				(*target_it)->sendMsg(reply_it->second);
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