/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teo <teo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:28:37 by mneri             #+#    #+#             */
/*   Updated: 2024/05/10 16:15:38 by teo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"


// ERROR //
void ERR_ALREADYREGISTERED(Client *client){std::cout << RED <<  "ERR_ALREADYREGISTERED(462) " << "<" << client->getNick() << ">" << ":You may not reregister\n" << WHITE;}
void ERR_NEEDMOREPARAMS(Client *client, std::string cmd){std::cout << RED << "ERR_NEEDMOREPARAMS(461) " << "<" << client->getNick() << "> " << cmd << ":Not enough parameters\n" << WHITE;}
void ERR_PASSWDMISMATCH(Client *client){std::cout << RED << "ERR_PASSWDMISMATCH (464) ) " << "<" << client->getNick() << "> " << ":Password incorrect\n" << WHITE;}
void ERR_ERRONEUSNICKNAME(Client *client, std::string nick){std::cout << RED << "ERR_ERRONEUSNICKNAME (432) " << "<" << client->getNick() << "> " << nick << ":Erroneus nickname\n" << WHITE;}
void ERR_NONICKNAMEGIVEN(Client *client){std::cout << RED << " ERR_NONICKNAMEGIVEN (431) " << "<" << client->getNick() << "> " << ":No nickname given\n" << WHITE;}
void ERR_NICKNAMEINUSE(Client *client, std::string nick){std::cout << RED << " ERR_NICKNAMEINUSE (433) " << "<" << client->getNick() << "> " << nick << ":Nickname is already in use\n" << WHITE;}
void ERR_NOTREGISTERED(Client *client){std::cout << RED << " ERR_NONICKNAMEGIVEN (431) " << "<" << client->getNick() << "> " << ":No nickname given\n" << WHITE;}

//REPLIES//

void RPL_WELCOME(Client *client){std::cout << "<" <<client->getNick() << "> Welcome to the IRC server!\n";}
