/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:22:24 by mneri             #+#    #+#             */
/*   Updated: 2024/05/20 18:32:55 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Channel.hpp"
#include "Utils.hpp"

void sendMsg(Client *client, std::string msg);

// CHANNEL ERROR //
std::string RPL_JOINCHANNEL(Client *client, std::string channelname);


// ERRORS //
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

// RESPONSES //

void RPL_WELCOME(Client *client);
void RPL_CHANNELMODEIS(Client *client, std::string channel, std::string modestring);