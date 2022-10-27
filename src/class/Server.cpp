#include "Server.hpp"

bool on = false;

Server::Server(int port, std::string pass):
	port(port),
	pass(pass),
	hostname(""),
	ip(""),
	serverSock(-2)
{
	std::cerr << "\n o0o0o0o Server is starting o0o0o0o\n\n";
	getHostInfo();
	initReplies();
	// signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	initSocket();
	on = true;
}

Server::~Server()
{
	exit();
}

void handler(int signo)
{
	if (signo == SIGINT || signo == SIGQUIT)
		on = false;
}

int Server::readMessage(Client * sender, std::string & message)
{
	char buffer[BUF_SIZE + 1];
	ssize_t readCount;

	while (message.find('\n') == std::string::npos)
	{
		if ((readCount = recv(sender->getSock(), buffer, BUF_SIZE, 0)) < 0)
			exit(true, "Error\nrecv()");
		buffer[readCount] = 0;
		message += buffer;
		if (readCount == 0)
		{
			std::cerr << "Client has left\n";
			return 1;
		}
	}
	message.erase(message.find('\n'));
	if (message.length() > 510)
	{
		message.erase(510);
	}
	message += "\r\n";
	return 0;
}

void Server::exeMessage(Client * sender, SplitMsg & message)
{
	if (message.getParams().size() > 15)
		return;

	std::string command = message.getCommand();

	if (command == std::string("PASS"))
		cmdPass(sender, message.getParams());
	else if (command == std::string("NICK"))
		cmdNick(sender, message.getParams());
	else if (command == std::string("USER"))
		cmdUser(sender, message.getParams());
}

void Server::run()
{
	int clientSock;

	std::cerr << "Waiting for client to connect ... ";
	if ((clientSock = accept(serverSock, reinterpret_cast<struct sockaddr *>(&address), &addrLength)) < 0)
		exit(true, "Error\naccept()");
	Client client(clientSock);
	clients.insert(std::make_pair(clientSock, &client));

	std::cerr << "Done\n";

	do
	{
		std::string message;
		if (readMessage(clients[clientSock], message) == 1)
			return;

		SplitMsg split(message);
		exeMessage(clients[clientSock], split);
	} while (on == true);
}

void Server::getHostInfo()
{
	char host[256];
	char *ip_buffer;
	struct hostent *host_entry;
	int host_name;

	std::cerr << "Retrieving host info ... ";
	if ((host_name = gethostname(host, sizeof(host))) < 0)
		exit(true, "Error\ngethostname()");
	if ((host_entry = gethostbyname(host)) == NULL)
		exit(true, "Error\ngethostbyname()");
	ip_buffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));

	hostname = host;
	ip = ip_buffer;

	std::cerr << "Done\t\t; Server IP address is : " << ip << '\n';
}

void Server::initReplies()
{
	replies.insert(std::make_pair("431", ":No nickname given\r\n"));
	replies.insert(std::make_pair("432", ":Erroneous nickname\r\n"));
	replies.insert(std::make_pair("433", ":Nickname is already in use\r\n"));
	replies.insert(std::make_pair("451", ":You have not registered\r\n"));
	replies.insert(std::make_pair("461", ":Not enough parameters\r\n"));
	replies.insert(std::make_pair("462", ":Unauthorized command (already registered)\r\n"));
	replies.insert(std::make_pair("464", ":Password incorrect\r\n"));
}

void Server::initSocket()
{
	int opt = 1;

	std::cerr << "Creating socket ... ";
	if ((serverSock = socket(AF_INET, SOCK_STREAM/* | SOCK_NONBLOCK*/, 6)) < 0)
		exit(true, "Error\nsocket()");
	if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		exit(true, "Error\nsetsockopt()");
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	addrLength = sizeof(address);
	if (bind(serverSock, reinterpret_cast<struct sockaddr *>(&address), addrLength) < 0)
		exit(true, "Error\nbind()");
	if (listen(serverSock, 4) < 0)
		exit(true, "Error\nlisten()");

	std::cerr << "Done\n";
}

ssize_t Server::sendNumeric(Client * target, std::string numeric, std::string param1, std::string param2)
{
	std::string reply = ":" + hostname + " " + numeric + " " + target->getNick() + " " + param1 + param2 + replies[numeric];
	return send(target->getSock(), reply.c_str(), reply.length(), 0);
}

void Server::exit(bool except, std::string msg)
{
	for (std::map<int, Client *>::iterator it = clients.begin(); it != clients.end(); it++)
		if (it->first > 0)
			close(it->first);
	if (serverSock > 0)
		close(serverSock);
	if (except == true)
		throw std::runtime_error(msg.c_str());
}