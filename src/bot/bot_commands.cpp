#include "Bot.hpp"

std::string roll(int max)
{
	if (max <= 0)
		max = 1;
	std::stringstream ss;

	srand(time(NULL));
	ss << rand() % max;
	return ss.str();
}

void Bot::cmdNickInUse(SplitMsg & msg)
{
	(void)msg;
	if (nick.length() > 9)
	{
		std::cerr << "Error: Nick in use\n";
		bot_on = false;
		return;
	}
	sendMsg("NICK " + nick + '_' + "\r\n");
	nick += '_';
}

void Bot::cmdWrongPass(SplitMsg & msg)
{
	(void)msg;
	std::cerr << "Error: incorrect password\n";
	bot_on = false;
}

void Bot::cmdPing(SplitMsg & msg)
{
	if (msg.getParams().size() > 0)
		sendMsg("PONG " + msg.getParams()[0] + "\r\n");
}

void Bot::cmdPrivmsg(SplitMsg & msg)
{
	if (msg.getParams().size() == 2 && msg.getParams()[1].substr(0, msg.getParams()[1].find(' ')) == "/roll")
	{
		strtok(const_cast<char *>(msg.getParams()[1].c_str()), " ");
		if (char * number = strtok(NULL, " "))
			sendMsg("NOTICE " + msg.getPrefix().substr(0, msg.getPrefix().find('!')) + ' ' + roll(atoi(number)) + "\r\n");
	}
}