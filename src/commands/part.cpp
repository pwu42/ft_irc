#include "Server.hpp"

void Server::cmdPart(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() < 1)
	{
		message.addReply(':' + hostname + ' ' + ERR_NEEDMOREPARAMS + ' ' + sender->getNick() + ' ' + replies[ERR_NEEDMOREPARAMS], sender);
		return ;
	}
	if (!channelExist(_channels, message.getParams()[0]))
	{
		message.addReply(':' + hostname + ' ' + ERR_NOSUCHCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' '  + replies[ERR_NOSUCHCHANNEL], sender);
		return ;
	}
	if (!sender->isIn(message.getParams()[0]))
	{
		message.addReply(':' + hostname + ' ' + ERR_NOTONCHANNEL + ' ' + sender->getNick() + ' ' + message.getParams()[0] + ' ' + replies[ERR_NOTONCHANNEL], sender);
		return ;
	}
	_channels[strlower((message.getParams()[0]))]->sendMsg(':' + sender->getNick() + '!' + sender->getUser() + '@' + hostname + ' ' + message.getCommand() + " :" + message.getParams()[0] + "\r\n");
	sender->removeChannel(message.getParams()[0]);
	((_channels[strlower((message.getParams()[0]))])->removeClient(sender));
	if (((_channels[strlower((message.getParams()[0]))])->empty()))
		deleteChannel(message.getParams()[0]);
}
// // sendMsg
// Reading client socket 6
// buffer = [PART #plo :plo
// ]
// prefix: []
// command: [PART]
// params:2 [ #plo plo ]
// ==127591== Invalid read of size 8
// ==127591==    at 0x411C87: Channel::sendMsg(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (Channel.cpp:106)
// ==127591==    by 0x4211AE: Server::cmdPart(Client*, SplitMsg&) (part.cpp:22)
// ==127591==    by 0x4075FF: Server::exeMessage(Client*) (Server.cpp:112)
// ==127591==    by 0x407A22: Server::run() (Server.cpp:152)
// ==127591==    by 0x42D40D: main (main.cpp:42)
// ==127591==  Address 0x4e11c80 is 0 bytes inside a block of size 208 free'd
// ==127591==    at 0x484B8AF: operator delete(void*) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==127591==    by 0x404346: Client::~Client() (Client.cpp:14)
// ==127591==    by 0x40675C: Server::deleteClient(int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (Server.cpp:68)
// ==127591==    by 0x407A65: Server::run() (Server.cpp:153)
// ==127591==    by 0x42D40D: main (main.cpp:42)
// ==127591==  Block was alloc'd at
// ==127591==    at 0x4849899: operator new(unsigned long, std::nothrow_t const&) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==127591==    by 0x4063EF: Server::addNewClient() (Server.cpp:49)
// ==127591==    by 0x407972: Server::run() (Server.cpp:148)
// ==127591==    by 0x42D40D: main (main.cpp:42)
// ==127591==
// ==127591== Invalid read of size 4
// ==127591==    at 0x404A44: Client::sendMsg(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (Client.cpp:108)
// ==127591==    by 0x411C8C: Channel::sendMsg(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (Channel.cpp:106)
// ==127591==    by 0x4211AE: Server::cmdPart(Client*, SplitMsg&) (part.cpp:22)
// ==127591==    by 0x4075FF: Server::exeMessage(Client*) (Server.cpp:112)
// ==127591==    by 0x407A22: Server::run() (Server.cpp:152)
// ==127591==    by 0x42D40D: main (main.cpp:42)
// ==127591==  Address 0x4e11cf0 is 112 bytes inside a block of size 208 free'd
// ==127591==    at 0x484B8AF: operator delete(void*) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==127591==    by 0x404346: Client::~Client() (Client.cpp:14)
// ==127591==    by 0x40675C: Server::deleteClient(int, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (Server.cpp:68)
// ==127591==    by 0x407A65: Server::run() (Server.cpp:153)
// ==127591==    by 0x42D40D: main (main.cpp:42)
// ==127591==  Block was alloc'd at
// ==127591==    at 0x4849899: operator new(unsigned long, std::nothrow_t const&) (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==127591==    by 0x4063EF: Server::addNewClient() (Server.cpp:49)
// ==127591==    by 0x407972: Server::run() (Server.cpp:148)
// ==127591==    by 0x42D40D: main (main.cpp:42)
// ==127591==
