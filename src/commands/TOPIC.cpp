/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:48:41 by mneri             #+#    #+#             */
/*   Updated: 2024/06/11 16:23:21 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Channel.hpp"
#include "../Server.hpp"

void Channel::parseTopicCommand(Client *client, std::vector<std::string> cmd)
{
	if(cmd.size() == 2)
	{
		sendMsg(client, RPL_TOPIC(client, cmd[1], _topic));
		return;
	}
	else
	{
		if(getAdmtopic() == true  && getClientInChannel(client->getFd()) != getAdmins(client->getFd()))
		{
			ERR_CHANOPRIVSNEEDED(client, cmd[1]);
			return;
		}
		std::string msg;
		for(size_t arg = 2; arg < cmd.size(); arg++)
			msg += cmd[arg] + " ";
		setTopic(msg);
		sendMsg(client, RPL_SETTOPIC(client, cmd[1], msg));
		sendToChannel(RPL_SETTOPIC(client, cmd[1], msg), client->getFd());
	}

}


void Server::TOPIC(int fd, std::vector<std::string> cmd)
{
	Client *cli = getClient(fd);
    Channel *channel = getChannel(cmd[1]);
    if(cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(cli, "TOPIC");
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
	channel->parseTopicCommand(cli, cmd);
		
}	
