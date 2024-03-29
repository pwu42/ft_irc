#include "Server.hpp"

bool on = false;

Server::Server(int port, const std::string & pass):
	port(port),
	pass(pass),
	fdCount(1)
{
}

Server::~Server()
{
	for (size_t i = 0; i < fdCount; i++)
	{
		if (i > 0)
			delete clients[fds[i].fd];
		if (fds[i].fd >= 3)
			close(fds[i].fd);
	}
	delete [] fds;

	for (std::map<std::string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); it++)
	{
		delete it->second;
	}
}

void Server::addNewClient()
{
	int fd;
	Client * newClient = NULL;

	std::cerr << "Reading server socket\n";
	do
	{
		if ((fd = accept(fds[0].fd, reinterpret_cast<struct sockaddr *>(&address), &addrLength)) < 0)
		{
			if (errno != EAGAIN && errno != EWOULDBLOCK)
				perror("accept()");
			break;
		}
		else if (fd == int(fdLimit - 1))
		{
			close(fd);
			std::cerr << "Error: Too many connections\n";
			break;
		}
		if ((newClient = new (std::nothrow) Client(fd)) == NULL)
		{
			close(fd);
			std::cerr << "Error: Out of memory\n";
			break;
		}
		std::cerr << "New connection on socket " << fd << '\n';
		fds[fdCount].fd = fd;
		fds[fdCount].events = POLLIN;
		++fdCount;
		clients[fd] = newClient;
	} while (fd != -1);
}

void Server::deleteClient(int index, const std::string & quitMsg)
{
	if (!(clients[fds[index].fd]->getStatus() & CLIENT_HAS_QUIT))
		clientDisconnect(clients[fds[index].fd], quitMsg);
	leaveAllChannels(clients[fds[index].fd]);
	std::cerr << "Client " << fds[index].fd << " has left\n";
	delete clients[fds[index].fd];
	clients.erase(fds[index].fd);
	close(fds[index].fd);
	fds[index].fd = fds[fdCount - 1].fd;
	--fdCount;
}

int Server::recvMessage(Client * sender)
{
	char buffer[BUF_SIZE + 1];
	ssize_t recvCount;

	recvCount = recv(sender->getSock(), buffer, BUF_SIZE, 0);
	switch (recvCount)
	{
	case -1:
		if (errno != EAGAIN && errno != EWOULDBLOCK)
			perror("recv()");
		return 1;
	case 0:
		return 1;
	}
	buffer[recvCount] = 0;
	// std::cerr << "buffer = [" << buffer << "]\n";
	sender->addMessage(buffer);
	return 0;
}

int Server::exeMessage(Client * sender)
{
	while (sender->getMessage().find('\n') != std::string::npos)
	{
		std::string msg = sender->getMessage().substr(0, sender->getMessage().find('\n')) + "\r\n";
		SplitMsg split(msg);

		if (msg.length() < 512 && split.getParams().size() < 15 && !split.getCommand().empty())
		{
			if (!commands.count(split.getCommand()))
				split.addReply(':' + hostname + ' ' + ERR_UNKNOWNCOMMAND + ' ' + sender->getNick() + ' ' + split.getCommand() + ' ' + replies[ERR_UNKNOWNCOMMAND], sender);
			else if (!(sender->getStatus() & CLIENT_REGISTER)
				&& split.getCommand() != "CAP" && split.getCommand() != "PASS" && split.getCommand() != "NICK"
				&& split.getCommand() != "USER" && split.getCommand() != "PONG" && split.getCommand() != "QUIT")
				split.addReply(':' + hostname + ' ' + ERR_NOTREGISTERED + ' ' + sender->getNick() + ' ' + replies[ERR_NOTREGISTERED], sender);
			else
				(this->*commands[split.getCommand()])(sender, split);
			reply(sender, split);
			if (sender->getStatus() & CLIENT_HAS_QUIT)
				return 1;
		}
		sender->getMessage().erase(0, sender->getMessage().find('\n') + 1);
	}
	return 0;
}

void Server::run()
{
	size_t currentSize;

	while (on)
	{
		std::cerr << "Polling ... \n";
		if (poll(fds, fdCount, POLL_TIMEOUT * 1000) < 0)
		{
			if (on == true)
				perror("poll()");
			break;
		}
		pingClients();
		currentSize = fdCount;
		for (size_t i = 0; i < std::min(currentSize, fdCount); i++)
		{
			if (fds[i].revents == 0 || fds[i].fd == -2)
				continue;
			if (fds[i].revents != POLLIN && !(fds[i].revents & POLLHUP))
			{
				std::cerr << "Fatal error: revents = " << fds[i].revents << " for " << fds[i].fd << '\n';
				on = false;
			}
			if (fds[i].fd == fds[0].fd)
				addNewClient();
			else
			{
				std::cerr << "Reading client socket " << fds[i].fd << '\n';
				if (recvMessage(clients[fds[i].fd]) == 1 || exeMessage(clients[fds[i].fd]) == 1)
					deleteClient(i);
			}
		}
	}
}

void Server::addNewChannel(const std::string &channelName, Client * creator)
{
	Channel *chan = NULL;

	if ((chan = new (std::nothrow) Channel(channelName, creator)) == NULL)
	{
		std::cerr << "Error: Out of memory\n";
	}
	else
	{
		chan->addOper(creator);
		_channels[strlower(channelName)] = chan;
	}
}

void Server::deleteChannel(const std::string & channelName)
{
	delete _channels[strlower(channelName)];
	_channels.erase(strlower(channelName));
}

void Server::cmdDoNothing(Client * sender, SplitMsg & message)
{
	(void)sender;
	(void)message;
}

void Server::exit(bool except, const std::string & msg)
{
	if (except == true)
	{
		std::cerr << "Error\n";
		perror(msg.c_str());
		throw std::runtime_error("");
	}
}

bool channelExist(const std::map<std::string , Channel *> & _channels, const std::string & channelName)
{
	for (std::map<std::string, Channel *>::const_iterator it = _channels.begin(); it != _channels.end(); it++)
		if (caseInsensEqual(channelName, it->first))
			return true;
	return false;
}
