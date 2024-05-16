/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:22:24 by mneri             #+#    #+#             */
/*   Updated: 2024/05/16 17:02:23 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Channel.hpp"
#include "Utils.hpp"

void sendMsg(Client *client, std::string msg);

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
// RESPONSES //

void RPL_WELCOME(Client *client);
void RPL_JOINCHANNEL(Client *client, std::string channelname);