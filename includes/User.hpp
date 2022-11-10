#ifndef USER_HPP
#define USER_HPP
// #include <csignal>
// #include <cstdlib>
// #include <cstring>
//
// #include <fcntl.h>
// #include <netdb.h>
// #include <poll.h>
// #include <sys/socket.h>
// #include <unistd.h>
//
// #include <iostream>
// #include <string>
// # include <map>
// # include <string>

# include "Irc.hpp"

// add enum status sur client
enum e_status
{
	CLIENT_HAS_PASS = 1,
 	CLIENT_HAS_NICK = 2,
 	CLIENT_HAS_USER = 4,
	CLIENT_REGISTER = 8,
 	CLIENT_IS_SERV_OPS = 16,
	CLIENT_HAS_LEFT = 32
};

class User
{
	private :
		unsigned char _status;
		int _sock;
		std::string _nick;
		std::string _addr;
		std::string _username;

	public :
		User();

		std::string getUsername() const ;
		std::string getAddr() const ;
		std::string getNick() const ;
		int	getSock() const;
		unsigned char getStatus() const;

		void addStatus(unsigned char status);
		void removeStatus(unsigned char status);
		void setUser(std::string const &username);
		void setNick(std::string const &nick);
		void setSock(int sock);

		~User();
};

#endif
