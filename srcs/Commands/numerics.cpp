# include "Server.hpp"

void Server::_rpl_welcome(Message &msg) // 001
{
	(void)msg;
	msg.setReply("001 " + _client.getNick() + " :Welcome to the bIRCher Network, " + _client.getNick() + "\r\n");
}

void Server::_rpl_topic(Message &msg)
{
	msg.setReply("332 "+ _client.getNick() + " <channel> :<topic>");
}

void Server::_rpl_topicWhoTime(Message &msg)
{
	msg.setReply("333 "+ _client.getNick() + " <channel> <nick> <setat>");
}

void Server::_rpl_namReply(Message &msg)
{
	msg.setReply("353 "+ _client.getNick() + " <symbol> <channel> :[prefix]<nick>{ [prefix]<nick>}");
}

void Server::_rpl_endOfNames(Message &msg)
{
	msg.setReply("366 "+ _client.getNick() + "<channel> :End of /NAMES list");
}

void Server::_rpl_youreOper(Message &msg)
{
	(void)msg;
	msg.setReply("381 "+ _client.getNick() + " :You are now an IRC operator.\r\n");
}

void Server::_err_noSuchChannel(Message &msg)
{
	msg.setReply("403 "+ _client.getNick() + " <channel> :No such channel.\r\n");
}

void Server::_err_noNicknameGiven(Message &msg)
{
	(void)msg;
	msg.setReply("431 " + _client.getNick() + " :No nickname given.\r\n");
}

void Server::_err_erroneusNickname(Message &msg)
{
	(void)msg;
	msg.setReply("432 " + _client.getNick() + " " + (msg.getArgs())[0] + "  :Erroneous nickname.\r\n");
}

void Server::_err_nicknameInUse(Message &msg)
{
	(void)msg;
	msg.setReply("433 " + _client.getNick() + " " + (msg.getArgs())[0] + " :Nickname is already in use.\r\n");
}

void Server::_err_needMoreParams(Message &msg)
{
	msg.setReply("461 "+ _client.getNick() + " " + msg.getCommand() + " :Not enough parameters.\r\n");
}

void Server::_err_alreadyRegistered(Message &msg) // see with client status
{
	(void)msg;
	msg.setReply("462 "+ _client.getNick() + " :You may not reregister.\r\n");
}

void Server::_err_passwdMisMatch(Message &msg)
{
	(void)msg;
	msg.setReply("464 "+ _client.getNick() + " :Password incorrect.\r\n");
}


void Server::_err_noOperHost(Message &msg)
{
	(void)msg;
	msg.setReply("491 "+ _client.getNick() + " :No O-lines for your host.\r\n");
}
