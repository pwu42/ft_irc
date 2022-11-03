#include "Commands.hpp"

void setCommands()
{
	_commands["001"] = _rpl_welcome;

	_commands["NICK"] = _cmdNick;
	_commands["PASS"] = _cmdPass;
}
