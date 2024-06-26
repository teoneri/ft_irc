/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:22:24 by mneri             #+#    #+#             */
/*   Updated: 2024/06/11 16:15:34 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Channel.hpp"
#include "Utils.hpp"

void sendMsg(Client *client, std::string msg);

// CHANNEL ERROR //
std::string RPL_JOINCHANNEL(Client *client, std::string channelname);
std::string RPL_KICKCHANNEL(Client *client, std::string channelname, std::string kicked, std::string reason);
std::string RPL_INVITING(Client *client, std::string invited, std::string channel);
std::string RPL_INVITED(Client *client, std::string invited, std::string channel);
std::string RPL_PART(Client *client, std::string channel, std::string reason);
std::string RPL_QUIT(Client *client, std::string reason);
std::string RPL_MSG(Client *client, std::string recipient, std::string msg);
std::string RPL_NAMREPLY(std::string nickname, std::string channel, std::string list);
std::string RPL_CREATIONTIME(std::string nick, std::string channel, std::string creationtime);
std::string RPL_ENDOFNAMES(std::string nick, std::string channel);
std::string RPL_NICKCHANGE(std::string oldnickname, std::string newnickname);
std::string	RPL_MODE(Client *client, std::string channel, std::string mode, std::string target);
std::string RPL_SETTOPIC(Client *client, std::string channel, std::string topic);
std::string RPL_TOPIC(Client *client, std::string channel, std::string topic);
// :mneri!mneri INVITE mneri #foo// ERRORS //
void ERR_ALREADYREGISTERED(Client *client);
void ERR_NEEDMOREPARAMS(Client *client, std::string cmd);
void ERR_PASSWDMISMATCH(Client *client);
void ERR_ERRONEUSNICKNAME(Client *client, std::string nick);
void ERR_NONICKNAMEGIVEN(Client *client);
void ERR_NICKNAMEINUSE(Client *client, std::string nick);
void ERR_NOTREGISTERED(Client *client);
void ERR_NOSUCHCHANNEL(Client *client, std::string channel);
void ERR_TOOMANYCHANNELS(Client *client, std::string channel);
void ERR_BADCHANNELKEY(Client *client, std::string channel);
void ERR_ALREADYJOIN(Client *client, std::string channelname);
void ERR_INVITEONLYCHAN(Client *client, std::string channelname);
void ERR_NOSUCHCHANNEL(Client *client, std::string channel);
void ERR_CHANOPRIVSNEEDED(Client *client, std::string channel);
void ERR_INVALIDMODEPARAM(Client *client, std::string channel, std::string param);
void ERR_UNKNOWNMODE(Client *client);
void ERR_USERNOTINCHANNEL(Client *client, std::string nick, std::string channel);
void ERR_NOTONCHANNEL(Client *client, std::string channel);
void ERR_USERONCHANNEL(Client *client, std::string nick, std::string channel);
void ERR_NORECIPIENT(Client *client);  
void ERR_NOSUCHNICK(Client *client, std::string nick);
void ERR_NOTEXTOSEND(Client *client);
void ERR_CMDNOTFOUND(Client *client, std::string cmd);
void ERR_CLIENTCAP(Client *client, std::string channelname);

// RESPONSES //

void RPL_WELCOME(Client *client);
void RPL_CHANNELMODEIS(Client *client, std::string channel, std::string modestring);
