/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:29:38 by mneri             #+#    #+#             */
/*   Updated: 2024/06/07 16:52:48 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../Channel.hpp"
#include "../Server.hpp"

void Channel::parsePartCommand(Client *client, std::vector<std::string> cmd)
{
	std::string reason = "";
	if(cmd.size() > 2)
	{
		for(size_t arg = 2; arg < cmd.size(); arg++)
		{
			reason += cmd[arg] + " ";
		}
	}
	std::string msg = RPL_PART(client, cmd[1], reason);
	sendMsg(client, msg);
	sendToChannel(msg, client->getFd());
	remAdmins(client->getFd());
	remClients(client->getFd());
	remInvited(client->getFd());
}


void Server::PART(int fd, std::vector<std::string> cmd)
{
	Client *cli = getClient(fd);
    Channel *channel = getChannel(cmd[1]);
    if(cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(cli, "PART");
		return;
	}
	if(!channel)
	{
		ERR_NOSUCHCHANNEL(cli, cmd[1]);
		return;
	}
    if(!channel->getClient(fd))
	{	
		ERR_NOTONCHANNEL(cli, cmd[1]);
		return;
    }
	channel->parsePartCommand(cli, cmd);
}	
