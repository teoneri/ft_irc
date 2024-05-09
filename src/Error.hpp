/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:22:24 by mneri             #+#    #+#             */
/*   Updated: 2024/05/09 17:54:52 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "Channel.hpp"

// ERRORS //
void ERR_ALREADYREGISTERED(Client *client);
void ERR_NEEDMOREPARAMS(Client *client, std::string cmd);