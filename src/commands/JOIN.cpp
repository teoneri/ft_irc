/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:32:24 by mneri             #+#    #+#             */
/*   Updated: 2024/06/11 16:21:30 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"


void Server::channelNotFound(Client *client, std::string name)
{
	Channel newChannel;
	newChannel.setName(name);
	newChannel.addAdmins(client);
	newChannel.addClient(client);
	newChannel.setCreationTime();
	channels.push_back(newChannel);
    sendMsg(client,  RPL_JOINCHANNEL(client, name) + RPL_NAMREPLY(client->getNick(), newChannel.getName(), newChannel.getClientList()) +\
	RPL_ENDOFNAMES(client->getNick(), name));
}


void Server::channelFound(Client *client, Channel *channel, std::vector<std::string> cmd, int fd)
{
	if(channel->getClient(fd))
	{	
		ERR_ALREADYJOIN(client, cmd[1]);
		return;
	}
	if(!channel->getPassword().empty())
	{
		if(cmd.size() < 3 || cmd[2] != channel->getPassword())
		{
			ERR_BADCHANNELKEY(client, cmd[1]);
			return;
		}
	}
	if(channel->getInvonly() == true)
	{
		if(!channel->getInvited(fd))
		{
			ERR_INVITEONLYCHAN(client, cmd[1]);
			return;
		}
	}
	if(channel->getClientcap() > 0 && channel->countClients() >= (size_t)channel->getClientcap())
	{
		ERR_CLIENTCAP(client, cmd[1]);
		return;
	}
	channel->addClient(client);
    std::string joinMessage = RPL_JOINCHANNEL(client, cmd[1]);
    sendMsg(client,  joinMessage + RPL_NAMREPLY(client->getNick(), cmd[1], channel->getClientList()) +\
	RPL_ENDOFNAMES(client->getNick(), cmd[1]));
	channel->sendToChannel(joinMessage, client->getFd());
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
			channelFound(cli, &channels[i], cmd, fd);
			return;
		}	
	}
	channelNotFound(cli, cmd[1]);
}
