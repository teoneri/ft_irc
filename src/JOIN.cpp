/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:32:24 by mneri             #+#    #+#             */
/*   Updated: 2024/05/13 17:39:35 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"



void Server::channelFound()
{
	
}

void Server::channelNotFound(int fd, Client *client, std::string name)
{

	Channel channel;
	channel.setName(name);
	channel.addAdmins(client);
	channels.push_back(channel);
}


void Server::JOIN(int fd, std::vector<std::string> cmd)
{
	Client *cli = getClient(fd);
	if(cmd.size() < 3)
	{
		ERR_NEEDMOREPARAMS(cli, "JOIN"); 
		return;
	}
	if(!cli->getRegistered())
	{
		ERR_NOTREGISTERED(cli); 
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
			channelFound();
			return;
		}	
	}
	channelNotFound(fd, cli, cmd[1])
}
