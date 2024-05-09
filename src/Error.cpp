/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:28:37 by mneri             #+#    #+#             */
/*   Updated: 2024/05/09 17:29:00 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"

void ERR_ALREADYREGISTERED(Client *client){std::cout << "ERR_ALREADYREGISTERED(462) " << "<" << client->getNick() << ">" << ":You may not reregister\n";}
void ERR_NEEDMOREPARAMS(Client *client, std::string cmd){std::cout << "ERR_NEEDMOREPARAMS(461) " << "<" << client->getNick() << "> " << cmd << ":Not enough parameters\n";}
