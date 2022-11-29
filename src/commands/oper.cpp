#include "Server.hpp"

void Server::cmdOper(Client * sender, SplitMsg & message)
{
	if ((sender->getStatus() & CLIENT_REGISTER) == 0)
		message.addReply(':' + hostname + ' ' + ERR_NOTREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_NOTREGISTERED], sender);
	else if (message.getParams().size() < 2)
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
	else if (message.getParams()[1] != OPER_PASS)
		message.addReply(':' + hostname + ' ' + ERR_PASSWDMISMATCH + ' ' + sender->getNick() + ' ' + replies[ERR_PASSWDMISMATCH], sender);
	else if (message.getParams()[0] != OPER_NAME)
		message.addReply(':' + hostname + ' ' + ERR_NOOPERHOST + ' ' + sender->getNick() + ' ' + replies[ERR_NOOPERHOST], sender);
	else
	{
		message.addReply(':' + hostname + ' ' + RPL_YOUREOPER + ' ' + sender->getNick() + ' ' + replies[RPL_YOUREOPER], sender);
		message.addReply("MODE " + sender->getNick() + " +o\r\n", sender);
		sender->addStatus(CLIENT_OPERATOR);
	}
}
