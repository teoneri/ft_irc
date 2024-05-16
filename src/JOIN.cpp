/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:32:24 by mneri             #+#    #+#             */
/*   Updated: 2024/05/16 17:59:06 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


void Server::channelNotFound(Client *client, std::string name)
{
	Channel channel;
	channel.setName(name);
	channel.addAdmins(client);
	channels.push_back(channel);
	RPL_JOINCHANNEL(client, name);
}

void Server::channelFound(Client *client, Channel *channel, std::vector<std::string> cmd, int fd)
{
	if(channel->getClient(fd) == client)
	{	
		ERR_ALREADYJOIN(client, cmd[1]);
		return;
	}
	if(cmd.size() > 2)
	{
		if(!channel->getPassword().empty() && cmd[2] != channel->getPassword())
		{
			ERR_BADCHANNELKEY(client, cmd[1]);
			return;
		}
	}
	if(channel->getInvonly() == true)
	{
		if(channel->getInvited(fd) == client)
		{
			ERR_INVITEONLYCHAN(client, cmd[1]);
			return;
		}
	}
	channel->addClient(client);
	channel->sendToChannel()
}



void Server::JOIN(int fd, std::vector<std::string> cmd)
{
	Client *cli = getClient(fd);
	if(cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(cli, "JOIN"); 
		return;
	}
	if(*(cmd[1].begin()) != '#')
	{
		ERR_NOSUCHCHANNEL(cli, cmd[1]);
		return;
	}
	for(size_t i = 0; i < channels.size(); i++)
	{
		if(cmd[1] == channels[i].getName())
		{
			channelFound(cli, channel[i], cmd, fd);
			return;
		}	
	}
	channelNotFound(cli, cmd[1]);
}
