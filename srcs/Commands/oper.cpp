# include "Server.hpp"

void Server::_cmdOper(Message &msg)
{
	if ((msg.getArgs()).size() < 2)
		callReply(ERR_NEEDMOREPARAMS, msg);
	else if (OPER_NAME1 != (msg.getArgs())[0] && OPER_NAME2 != (msg.getArgs())[0])
		callReply(ERR_NOOPERHOST, msg);
	else if ((OPER_PSWD1 != (msg.getArgs())[1] && OPER_NAME1 == (msg.getArgs())[0]) || (OPER_PSWD2 != (msg.getArgs())[1] && OPER_NAME2 == (msg.getArgs())[0]))
		callReply(ERR_PASSWDMISMATCH, msg);
	else
	{
		_client.addStatus(CLIENT_IS_SERV_OPS);
		callReply(RPL_YOUREOPER, msg);
	}
}
