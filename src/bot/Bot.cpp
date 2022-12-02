#include "Bot.hpp"

Bot::Bot():
	registered(false)
{
	sock.fd = -2;
	sock.events = POLLIN;
	(void)registered;
}

Bot::~Bot()
{
	if (sock.fd >= 3)
		close(sock.fd);
}

void Bot::init(int port, const std::string & password)
{
	int opt = 1;
	int connect_try = 0;
	socklen_t optlen = sizeof(opt);

	std::cerr << "\n o0o0o0o IRC Bot is starting o0o0o0o\n";
	if ((sock.fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP)) < 0)
	{
		perror("socket()");
		throw std::runtime_error("");
	}
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0)
	{
		perror("inet_pton()");
		throw std::runtime_error("");
	}
	std::cerr << "\nConnecting ...";
	while (connect(sock.fd, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) < 0)
	{
		if (connect_try > 3)
		{
			if (errno != EINPROGRESS && errno != EAGAIN)
				perror(" Error\nconnect()");
			else
				std::cerr << " Error\nTimed out.";
			throw std::runtime_error("");
		}
		++connect_try;
		sleep(5);
		std::cerr << '.';
	}
	std::cerr << " Done\n";
	if (getsockopt(sock.fd, SOL_SOCKET, SO_ERROR, &opt, &optlen) < 0)
	{
		perror("getsockopt()");
		throw std::runtime_error("");
	}
	pass = password;
	bot_on = true;
}

void Bot::run()
{
	sendMsg("PASS " + pass + "\r\nNICK bot\r\nUSER bot 0 * bot\r\n");
	while (bot_on)
	{
		if (poll(&sock, 1, -1) < 0)
		{
			if (bot_on)
				perror("poll()");
			break;
		}
		if (sock.revents != POLLIN && !(sock.revents & POLLHUP))
		{
			std::cerr << "Fatal error: revents = " << sock.revents << '\n';
			bot_on = false;
		}
		if (recvMsg() || exeMsg())
			bot_on = false;
	}
}

void Bot::sendMsg(const std::string & msg)
{
	send(sock.fd, msg.c_str(),msg.length(), MSG_NOSIGNAL);
}

int Bot::recvMsg()
{
	char buffer[BUFSIZ + 1];
	ssize_t recvCount;

	recvCount = recv(sock.fd, buffer, BUFSIZ, 0);
	switch (recvCount)
	{
	case -1:
		if (errno != EAGAIN && errno != EWOULDBLOCK)
			perror("recv()");
		return 1;
	case 0:
		std::cerr << "Connection lost\n";
		return 1;
	}
	buffer[recvCount] = 0;
	std::cerr << "buffer = [" << buffer << "]\n";
	message = buffer;
	return 0;
}

int Bot::exeMsg()
{
	while (message.find('\n') != std::string::npos)
	{
		std::string to_exe = message.substr(0, message.find_first_of("\r\n")) + "\r\n";
		SplitMsg split(to_exe);

		// if (to_exe.length() < 512 && split.getParams().size() < 15 && !split.getCommand().empty())

		message.erase(0, message.find('\n') + 1);
	}
	return 0;
}