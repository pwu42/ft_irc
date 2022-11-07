#ifndef USER_HPP
#define USER_HPP
#include <csignal>
#include <cstdlib>
#include <cstring>

#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>
# include <map>
# include <string>

// add enum status sur client


class User
{
	private :
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

		void setUser(std::string const &username);
		void setNick(std::string const &nick);
		void setSock(int sock);

		~User();
};

#endif
