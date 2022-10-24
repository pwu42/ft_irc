#ifndef USER_HPP
#define USER_HPP
# include <map>
# include <string> 

class User
{
	private :
		std::string _nick;
		std::string _addr;
		std::string _username;

	public :
		std::string getUsername() const ;
		std::string getAddr() const ;
		std::string getNick() const ;

		void setUser(std::string const &nick);
		void setNick(std::string const &nick);
};

class Channel
{
	private :
		std::map<std::string, User *> _users;

	public :
		void addUser(User *user, std::string nick);
		void deleteUser(std::string nick);
};
//
// class Message
// {
// 	private :
// 		std::string _content;
// 		std::string _cmd;
//
// 	public :
// 		send();
// 		receive();
//
// }

#endif
