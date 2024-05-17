/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:28:37 by mneri             #+#    #+#             */
/*   Updated: 2024/05/17 18:07:12 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"


void sendMsg(Client *client, std::string msg)
{
	send(client->getFd(), msg.c_str(), msg.size(), 0);
	std::cout << msg;
}



// ERROR //
void ERR_ALREADYREGISTERED(Client *client){std::string str =  std::string(RED) +  "ERR_ALREADYREGISTEstd::string(RED)(462) " + "<" + client->getNick() + ">" + ":You may not reregister\n" + WHITE; sendMsg(client, str);}
void ERR_NEEDMOREPARAMS(Client *client, std::string cmd){std::string str =  std::string(RED) + "ERR_NEEDMOREPARAMS(461) " + "<" + client->getNick() + "> " + cmd + ":Not enough parameters\n" + WHITE; sendMsg(client, str);}
void ERR_PASSWDMISMATCH(Client *client){std::string str =  std::string(RED) + "ERR_PASSWDMISMATCH (464) ) " + "<" + client->getNick() + "> " + ":Password incorrect\n" + WHITE; sendMsg(client, str);}
void ERR_ERRONEUSNICKNAME(Client *client, std::string nick){std::string str =  std::string(RED) + "ERR_ERRONEUSNICKNAME (432) " + "<" + client->getNick() + "> " + nick + ":Erroneus nickname\n" + WHITE; sendMsg(client, str);}
void ERR_NONICKNAMEGIVEN(Client *client){std::string str =  std::string(RED) + " ERR_NONICKNAMEGIVEN (431) " + "<" + client->getNick() + "> " + ":No nickname given\n" + WHITE; sendMsg(client, str);}
void ERR_NICKNAMEINUSE(Client *client, std::string nick){std::string str =  std::string(RED) + " ERR_NICKNAMEINUSE (433) " + "<" + client->getNick() + "> " + nick + ":Nickname is already in use\n" + WHITE; sendMsg(client, str);}
void ERR_NOTREGISTERED(Client *client){std::string str =  std::string(RED) + " ERR_NONICKNAMEGIVEN (431) " + "<" + client->getNick() + "> " + ":No nickname given\n" + WHITE; sendMsg(client, str);}
void ERR_NOSUCHCHANNEL(Client *client, std::string channel){std::string str = std::string(RED) + "ERR_NOSUCHCHANNEL (403) " + "<" + client->getNick() + "> " + channel + ":No such channel\n" + WHITE; sendMsg(client, str);}
void ERR_TOOMANYCHANNELS(Client *client, std::string channel){std::string str =  std::string(RED) + "ERR_TOOMANYCHANNELS (405) " + "<" + client->getNick() + "> " + channel + ":You have joined too many channels\n" + WHITE; sendMsg(client, str);}
void ERR_BADCHANNELKEY(Client *client, std::string channel){std::string str = std::string(RED) + "ERR_BADCHANNELKEY (475) " + "<" + client->getNick() + "> " + channel + " :Cannot join channel (+k)\n" + WHITE; sendMsg(client, str);}
void ERR_ALREADYJOIN(Client *client, std::string channelname){std::string str = std::string(RED) + client->getNick() + " already joined " + channelname + "\n" + WHITE; sendMsg(client, str);}
void ERR_INVITEONLYCHAN(Client *client, std::string channelname){std::string str = std::string(RED) + "ERR_INVITEONLYCHAN (473) " + "<" + client->getNick() + "> " + channelname + " :Cannot join channel (+i)\n" + WHITE; sendMsg(client, str);}
void ERR_NOSUCHCHANNEL(Client *client, std::string channel){std::string str = std::string(RED) + "ERR_NOSUCHCHANNEL (403) " + "<" + client->getNick() + "> " + channel + " :No such channel\n" + WHITE; sendMsg(client, str);}
void ERR_CHANOPRIVSNEEDED(Client *client, std::string channel){std::string str = std::string(RED) + "ERR_CHANOPRIVSNEEDED (482) " + "<" + client->getNick() + "> " + channel + " :You're not channel operator\n" + WHITE; sendMsg(client, str);}
void ERR_INVALIDMODEPARAM(Client *client, std::string channel, std::string param){std::string str = std::string(RED) + "ERR_INVALIDMODEPARAM (696) " + "<" + client->getNick() + "> " + channel + " :Missing parameter for MODE (" + param + ") \n" + WHITE; sendMsg(client, str);}
//REPLIES// 

void RPL_WELCOME(Client *client){std::string str = "<" + client->getNick() + "> Welcome to the IRC server!\n"; sendMsg(client, str);}
void RPL_CHANNELMODEIS(Client *client, std::string channel, std::string modestring){std::string str = "RPL_CHANNELMODEIS (324) <" + client->getNick() + "> " + channel + " " + modestring;}

// CHANNEL ERRORS // 
std::string RPL_JOINCHANNEL(Client *client, std::string channelname){return client->getNick() + ":" + client->getUser() + "@" + client->getIPaddr() + " JOIN " + channelname + "\n";}
