/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:28:37 by mneri             #+#    #+#             */
/*   Updated: 2024/06/04 18:16:32 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"


void sendMsg(Client *client, std::string msg)
{
	std::cout << msg;
	send(client->getFd(), msg.c_str(), msg.size(), 0);
}



// ERROR //
void ERR_ALREADYREGISTERED(Client *client){std::string str = ": 462 " + client->getNick() + ": You may not reregister\r\n"; sendMsg(client, str);}
void ERR_NEEDMOREPARAMS(Client *client, std::string cmd){std::string str = ": 461 " + client->getNick()  + cmd + ": Not enough parameters\r\n"; sendMsg(client, str);}
void ERR_PASSWDMISMATCH(Client *client){std::string str =  ": 464 " + client->getNick() + ": Password incorrect\r\n"; sendMsg(client, str);}
void ERR_ERRONEUSNICKNAME(Client *client, std::string nick){std::string str =  ": 432 " + client->getNick() + nick + ": Erroneus nickname\r\n"; sendMsg(client, str);}
void ERR_NONICKNAMEGIVEN(Client *client){ std::string str = ": 431 " + client->getNick() + ": No nickname given\r\n"; sendMsg(client, str);}
void ERR_NICKNAMEINUSE(Client *client, std::string nick){ std::string str = " : 433 " + client->getNick() + " " + nick + ": Nickname is already in use\r\n"; sendMsg(client, str);}
void ERR_NOTREGISTERED(Client *client){ std::string str = ": 451 " + client->getNick() + ": You have not registered\r\n"; sendMsg(client, str);}
void ERR_NOSUCHCHANNEL(Client *client, std::string channel){ std::string str =  ": 403" + client->getNick() + " " + channel + ": No such channel\r\n"; sendMsg(client, str);}
void ERR_TOOMANYCHANNELS(Client *client, std::string channel){ std::string str = ": 405 " + client->getNick() + " " + channel + ": You have joined too many channels\r\n"; sendMsg(client, str);}
void ERR_BADCHANNELKEY(Client *client, std::string channel){ std::string str = ": 475 " + client->getNick() + " " + channel + ": Cannot join channel (+k)\r\n"; sendMsg(client, str);}
void ERR_ALREADYJOIN(Client *client, std::string channelname){ std::string str =  client->getNick() + " already joined " + channelname + "\r\n"; sendMsg(client, str);}
void ERR_INVITEONLYCHAN(Client *client, std::string channelname){ std::string str =  ": 473 " + client->getNick() + " " + channelname + ": Cannot join channel (+i)\r\n"; sendMsg(client, str);}
void ERR_CHANOPRIVSNEEDED(Client *client, std::string channel){  std::string str = ": 482 " + client->getNick() + " " + channel + ": You're not channel operator\r\n"; sendMsg(client, str);}
void ERR_INVALIDMODEPARAM(Client *client, std::string channel, std::string param){ std::string str =  ": 696" + client->getNick() + " " + channel + ": Missing parameter for MODE (" + param + ") \r\n"; sendMsg(client, str);}
void ERR_UNKNOWNMODE(Client *client){ std::string str =  ": 472 " + client->getNick() + " " + ": Unkwown mode char\r\n"; sendMsg(client, str);}
void ERR_USERNOTINCHANNEL(Client *client, std::string nick, std::string channel){std::string str =  ": 441 " + client->getNick() + " " + nick + " " + channel + ": They aren't on that channel\r\n"; sendMsg(client, str);}
void ERR_NOTONCHANNEL(Client *client, std::string channel){  std::string str = ": 442 " + client->getNick() + "> " + channel + ": You're not on that channel\r\n"; sendMsg(client, str);}
void ERR_USERONCHANNEL(Client *client, std::string nick, std::string channel){ std::string str = ": 443" + client->getNick() + " " + nick + " " + channel + ": is already on channel\r\n"; sendMsg(client, str);}
void ERR_NORECIPIENT(Client *client){ std::string str =  ": 411 " + client->getNick() + " " + ": No recipient given\r\n"; sendMsg(client, str);}
void ERR_NOSUCHNICK(Client *client, std::string nick){ std::string str =  ": 401 " + client->getNick() + " " + nick + ": No such nick/channel\r\n"; sendMsg(client, str);}
void ERR_NOTEXTOSEND(Client *client){ std::string str =  ": 412 " + client->getNick() + " " + ": No text to send\r\n"; sendMsg(client, str);}
void ERR_CMDNOTFOUND(Client *client, std::string cmd){std::string str = ": 421 " + client->getNick() + " " + cmd + " :Unknown command\r\n";sendMsg(client, str);}

//REPLIES// 

void RPL_WELCOME(Client *client){std::string str = ": 001 " + client->getNick() + ": Welcome to the IRC server!\r\n"; sendMsg(client, str);}
void RPL_CHANNELMODEIS(Client *client, std::string channel, std::string modestring){std::string str = ": 324 " + client->getNick() + " " + channel + " " + modestring + "\r\n"; sendMsg(client, str);}
void RPL_TOPIC(Client *client, std::string channel, std::string topic){std::string str = ": 332 " + client->getNick() + " " + channel + " : " + topic + "\r\n"; sendMsg(client, str);}

// CHANNEL ERRORS // 
std::string RPL_JOINCHANNEL(Client *client, std::string channelname){return ":" + client->getNick() + "!" + client->getUser() + "@" + client->getIPaddr() + " JOIN " + channelname + "\r\n";}
std::string RPL_KICKCHANNEL(Client *client, std::string channelname, std::string kicked, std::string reason){return client->getNick() + "!" + client->getUser() + "@" + client->getIPaddr() + " KICK " + channelname + " " + kicked +  ":" + reason +"\r\n";}
std::string RPL_INVITING(Client *client, std::string invited, std::string channel){return client->getNick() + "!" + client->getUser() + "@" + client->getIPaddr() + " INVITE " + invited + " " + channel + "\r\n";}
std::string RPL_PART(Client *client, std::string channel, std::string reason){return client->getNick() + "!" + client->getUser() + "@" + client->getIPaddr() + " PART " + channel + " :" + reason + "\r\n";}
std::string RPL_QUIT(Client *client, std::string reason){return client->getNick() + "!" + client->getUser() + "@" + client->getIPaddr() + " QUIT :" + reason + "\r\n";}
std::string RPL_MSG(Client *client, std::string recipient, std::string msg){return client->getNick() + "!" + client->getUser() + "@" + client->getIPaddr() + " PRIVMSG :" + recipient + " " + msg + "\r\n";}
std::string RPL_NAMREPLY(std::string nick, std::string channel, std::string list){return ": 353 " + nick + " @ " + channel + " :" + list + "\r\n";}
std::string RPL_CREATIONTIME(std::string nick, std::string channel, std::string creationtime){ return ": 329 " + nick + " " + channel + " " + creationtime + "\r\n";}
std::string RPL_ENDOFNAMES(std::string nick, std::string channel){return ": 366 " + nick + " " + channel + " :END of /NAMES list" + "\r\n";}
std::string RPL_NICKCHANGE(std::string oldnickname, std::string newnickname){return ":" + oldnickname + " NICK " + newnickname + "\r\n";}