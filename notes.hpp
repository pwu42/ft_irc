// # ifndef CHANNEL_HPP
// # define CHANNEL_HPP
// # include "Irc.hpp"
//
// fct send to all users in channel
// class Channel
// {
// 		private :
// 			std::string _name;
			// std::string _topic;
			// std::map<int sock, Client *> _ops;
// 			std::map<int sock, Client *> _users;
//
// 		public :
			// Channel(std::string name);
// 			void addUser(User *user, std::string nick);
// 			bool UserIsIn();
// 			bool UserIsOp();
// 			void deleteUser(std::string nick);
			// setUsers
			// setOps
			// setTopic

			// ~Channel();

// };
//add send all pwu
// #endif




// URGENT

// join

// ==> JOIN #okij
// <== :ereali!~ereali@62.A6C72468 JOIN #okij to everyone including me
// <== :celestin.fr.ircube.org 353 ereali = #okij :@ereali
// <== :celestin.fr.ircube.org 366 ereali #okij :End of /NAMES list.



// :ereali_!~ereali@62.A6858496 PART :#plop
// <== :ereali_!~ereali@62.A6858496 JOIN #plop
// : fullname cmd : channel

// part test sur proxy  avec multi
 // send "PART #plop :tchouss" to everyone including me
 // topic lorsqu /topic seul rien envoyer a serveur ?

// names
// <== :celestin.fr.ircube.org 353 ereali = #plop :@ereali
// <== :celestin.fr.ircube.org 366 ereali #plop :End of /NAMES list.
// ou
// <== :celestin.fr.ircube.org 353 ereali = #aide :ereali ced117 Pyrrah olasd Menwe Kahan kouak Cesar @Z
// <== :celestin.fr.ircube.org 366 ereali #aide :End of /NAMES list.

// topic
// :ereali!~ereali@62.7C8A0A20 TOPIC #plop ::salut ceci est un test 42
// ':' + sender->getNick() + '!' + sender->getUser() + '@' + hostname + ' ' + message.getCommand() + ' ' + message.getParams()[0] + " :" + (message.getParams()[1])


// list
// <== :celestin.fr.ircube.org 321 ereali Channel :Users  Name
// <== :celestin.fr.ircube.org 322 ereali #webrankinfo 3 :WebRankInfo : R�f�rencement, web et compagnie
// <== :celestin.fr.ircube.org 322 ereali #HeroCorp 1 :
// <== :celestin.fr.ircube.org 322 ereali #gluster 1 :
// <== :celestin.fr.ircube.org 322 ereali #ircuve 3 :12 Le Bar d'IRCube 1- Dirigez vous vers le bar avant toute prise de parole - Merci, La Direction
// <== :celestin.fr.ircube.org 322 ereali #plop 1 :
// <== :celestin.fr.ircube.org 322 ereali #Poudlard 3 :8,0æ0,8æ7,8æ8,7æ4,7æ7,4æ5,4æ4,5æ1,5æ5,1æ8,1 [Poudlard.org] Ancien channel officiel - http://www.poudlard.org 5,1æ1,5æ4,5æ5,4æ7,4æ4,7æ8,7æ7,8æ0,8æ8,0æ
// <== :celestin.fr.ircube.org 322 ereali #aide 8 :Bienvenue sur le salon d'aide du r�seau IRCube - Consultez l'aide avant de poser vos questions http://wiki.ircube.org
// <== :celestin.fr.ircube.org 322 ereali #lafermeadede 2 :Bienvenue sur La ferme � D�d� - http://www.lafermeadede.com
// <== :celestin.fr.ircube.org 322 ereali #IRCube 10 :[ http://ircube.org/ ] Bienvenue sur le salon d'accueil du r�seau IRCube ! 12Bon t'chat !
// <== :celestin.fr.ircube.org 323 ereali :End of /LIST

// mode O +-o

   // MODE !12345ircd O               ; Command to ask who the channel
   //                                 creator for "!12345ircd" is

   // MODE #Finnish +o Kilroy         ; Command to give 'chanop' privileges
   //                                 to Kilroy on channel #Finnish.

// invite ?
// kick
// <== :ereali!~ereali@62.A6858496 KICK #plop ereali_ :ereali
// <== :ereali!~ereali@62.A6858496 KICK #plop ereali_ :ereali
// : fullname cmd channel cible :opsnick

// 18:33 -!- Irssi: Doing this is not a good idea. Add -YES option to command if you really mean it
// because this can make leave the client by an overflow buffer on old machine or by stopping the ping answer


// ./proxy.sh 4243 irc.ircube.org 6667
// /connect localhost 4243

// Tester send all  fulName became
// ':' + sender->getNick() + '!' + sender->getUser() + '@' + hostname +
