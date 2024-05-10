/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teo <teo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:22:24 by mneri             #+#    #+#             */
/*   Updated: 2024/05/10 16:11:49 by teo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Channel.hpp"

// ERRORS //
void ERR_ALREADYREGISTERED(Client *client);
void ERR_NEEDMOREPARAMS(Client *client, std::string cmd);
void ERR_PASSWDMISMATCH(Client *client);
void ERR_ERRONEUSNICKNAME(Client *client, std::string nick);
void ERR_NONICKNAMEGIVEN(Client *client);
void ERR_NICKNAMEINUSE(Client *client, std::string nick);
void ERR_NOTREGISTERED(Client *client);

// RESPONSES //

void RPL_WELCOME(Client *client);