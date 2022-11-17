#include "Server.hpp"

void Server::cmdOper(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 2)
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], TARGET_SENDER);
	else if (message.getParams()[1] != OPER_PASS)
		message.addReply(':' + hostname + ' ' + ERR_PASSWDMISMATCH + ' ' + sender->getNick() + ' ' + replies[ERR_PASSWDMISMATCH], TARGET_SENDER);
	else if (message.getParams()[0] != OPER_NAME)
		message.addReply(':' + hostname + ' ' + ERR_NOOPERHOST + ' ' + sender->getNick() + ' ' + replies[ERR_NOOPERHOST], TARGET_SENDER);
	else
	{
		message.addReply(':' + hostname + ' ' + RPL_YOUREOPER + ' ' + sender->getNick() + ' ' + replies[RPL_YOUREOPER], TARGET_SENDER);
		message.addReply("MODE " + sender->getNick() + " +o\r\n", TARGET_SENDER);
		sender->setOper();
	}
}