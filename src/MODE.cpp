/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:18:35 by mneri             #+#    #+#             */
/*   Updated: 2024/05/20 18:41:21 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"

bool isAllNumbers(const std::string& str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (!std::isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

void Channel::addMode(Client *client, std::vector<std::string> cmd, std::string mode)
{
	size_t arg = 3;
	for(int i = 0; mode[i]; i++)
	{
		switch (mode[i])
		{
		case 'i':
		{
			if(inv_only == false)
			{
				inv_only = true;
				modes.push_back("i");
			}
			break;
		}
		case 't':
		{
			if(adm_topic == false)
			{
				adm_topic = true;
				modes.push_back("t");
			}
			break;
		}
		case 'k':
		{
			if(arg + 1 < cmd.size())
			{
				ERR_INVALIDMODEPARAM(client, cmd[1], "k");
				return ;
			}
			else if(_password.empty())
				_password = cmd[arg];
			arg++;
			break;
		}
		case 'o':
		{
			if(client != getAdmins(client->getFd()))
				addAdmins(client);
			break;
		}
		case 'l':
		{
			if(arg + 1 < cmd.size() && !isAllNumbers(cmd[arg]))
			{
				ERR_INVALIDMODEPARAM(client, cmd[1], "l");
				return ;
			}
			else if(client_cap < 0)
				client_cap = std::atoi(cmd[arg].c_str());
			arg++;
		}
		default:
		{
			ERR_UNKNOWNMODE(client);
			return;
		}
		}
	}
	
}

void Channel::remMode(Client *client, std::string mode)
{
	std::vector<std::string>::iterator it;

	for(int i = 0; mode[i]; i++)
	{
		switch (mode[i])
		{
		case 'i':
		{
			if(inv_only == true)
			{
		        it = std::find(modes.begin(), modes.end(), "i");
				inv_only = false;
				modes.erase(it);
			}
			break;
		}
		case 't':
		{
			if(adm_topic == true)
			{
		        it = std::find(modes.begin(), modes.end(), "t");
				adm_topic = false;
				modes.erase(it);
			}
			break;
		}
		case 'k':
		{
			if(!_password.empty())
			{
		        it = std::find(modes.begin(), modes.end(), "k");
				_password.clear();
				modes.erase(it);
			}
			break;
		}
		case 'o':
		{
			if(client == getAdmins(client->getFd()))
			{
		        it = std::find(modes.begin(), modes.end(), "o");
				remAdmins(client);
				modes.erase(it);

			}
			break;
		}
		case 'l':
		{
			if(client_cap > 0 )
			{
		        it = std::find(modes.begin(), modes.end(), "l");
				client_cap = -1;
				modes.erase(it);
			}
		}
		default:
			break;
		}
	}
	}

std::string Channel::displayMode()
{
	std::vector<std::string>::iterator it;
	std::string msg = "";
	if(modes.size() > 0)
		msg = "+";
	for(it = modes.begin(); it != modes.end(); it++)
	{
		msg += *it;
	}
	return msg;
}

void Server::MODE(int fd, std::vector<std::string> cmd)
{
	Client *cli = getClient(fd);
	if(cmd.size() < 2)
	{
		ERR_NEEDMOREPARAMS(cli, "MODE");
		return;
	}
	Channel *channel = getChannel(cmd[1]);
	if(!channel)
	{
		ERR_NOSUCHCHANNEL(cli, cmd[1]);
		return;
	}
	if(channel->getClientInChannel(fd) != channel->getAdmins(fd))
	{
		ERR_CHANOPRIVSNEEDED(cli, cmd[1]);
		return;
	}
	if(cmd.size() == 2)
	{
		RPL_CHANNELMODEIS(cli, cmd[1], channel->displayMode());
		return ;
	}
	if(cmd[2][0] == '+')
		channel->addMode(cli, cmd, cmd[2].substr(1));
	else if(cmd[2][0] == '-')
		channel->remMode(cli, cmd[2].substr(1));
		
}	
