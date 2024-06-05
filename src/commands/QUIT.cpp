/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teo <teo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:51:14 by mneri             #+#    #+#             */
/*   Updated: 2024/06/05 17:46:43 by teo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"

void Server::QUIT(int fd, std::vector<std::string> cmd)
{
	std::string reason = "";
	if (cmd.size() > 1)
	{
		for (size_t i = 1; i < cmd.size(); i++)
			reason += cmd[i] + " ";
	}
	close(fd);
	std::string msg = RPL_QUIT(getClient(fd), reason);
	std::vector<Channel>::iterator it;
	for (it = channels.begin(); it != channels.end(); it++)
	{
		if (it->getClient(fd))
			it->sendToChannel(msg, fd);
	}
	std::cout << RED << "Client " << getClient(fd)->getNick() << " <" << getClient(fd)->getFd() << "> " << " disconnected\n"
			  << WHITE;
	removeClient(fd);
}
