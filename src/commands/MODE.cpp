/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:18:35 by mneri             #+#    #+#             */
/*   Updated: 2024/06/07 18:43:30 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Server.hpp"
#include "../Channel.hpp"

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
	std::string modsadded = "+";
	std::vector<int> error;
	for(int i = 0; mode[i]; i++)
	{
		switch (mode[i])
		{
		case 'i':
		{
			if(inv_only == false)
			{
				inv_only = true;
				modsadded += "i";
				modes.push_back("i");
			}
			break;
		}
		case 't':
		{
			if(adm_topic == false)
			{
				adm_topic = true;
				modsadded += "t";
				modes.push_back("t");
			}
			break;
		}
		case 'k':
		{
			if(cmd.size() <= 3)
			{
				ERR_INVALIDMODEPARAM(client, cmd[1], "k");
				error.push_back(i);
			}
			else if(_password.empty())
			{	
				_password = cmd[arg];
				modsadded += "k";
				modes.push_back("k");
			}
			arg++;
			break;
		}
		case 'o':
		{
			if(cmd.size() <= 3 )
			{
				ERR_INVALIDMODEPARAM(client, cmd[1], "o");
				error.push_back(i);
			}
			else if(!getClientbyName(cmd[arg]))
			{
				ERR_NOSUCHNICK(client, cmd[arg]);
				error.push_back(i);
			}	
			else if(!getAdminbyName(cmd[arg]))
			{	
				Client *cli = getClientbyName(cmd[arg]);
				if(cli)
					admins.push_back(*cli);
				modsadded += "o";
				
			}
			arg++;
			break;
		}
		case 'l':
		{
			if(cmd.size() <= 3 || !isAllNumbers(cmd[arg]))
			{
				ERR_INVALIDMODEPARAM(client, cmd[1], "l");
				error.push_back(i);
			}
			else if(client_cap < 0)
			{	
				client_cap = std::atoi(cmd[arg].c_str());
				modes.push_back("l");
				modsadded += "l";
			}
			arg++;
			break;
		}
		default:
		{
			ERR_UNKNOWNMODE(client);
		}
		}
	}
	std::string target = "";
	if(cmd.size() > 3)
	{
		size_t i = 3;
		int j = 0;
		while(i < cmd.size())
		{
			std::vector<int>::iterator it = std::find(error.begin(), error.end(), j);
			if(i != cmd.size())
				target += " ";
			if(it == error.end())
				target += cmd[i];
			i++;
			j++;
		}
	}	
	sendMsg(client, RPL_MODE(client, cmd[1], modsadded, target));
	sendToChannel(RPL_MODE(client, cmd[1], modsadded, target), client->getFd());
}

void Channel::remMode(Client *client, std::vector<std::string> cmd,  std::string mode)
{
	std::vector<std::string>::iterator it;
	size_t arg = 3;
	std::string modsremoved = "-";
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
				modsremoved += "i";
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
				modsremoved += "t";
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
				modsremoved += "k";
			}
			break;
		}
		case 'o':
		{
			if(cmd.size() <= 3 )
			{
				ERR_INVALIDMODEPARAM(client, cmd[1], "o");
			}
			if(getAdminbyName(cmd[arg]))
			{	
				Client *cli = getAdminbyName(cmd[arg]);
				if(cli)
					remAdmins(cli->getFd());
				modsremoved += "o";
			}
			arg++;
			break;
		}
		case 'l':
		{
			if(client_cap > 0 )
			{
		        it = std::find(modes.begin(), modes.end(), "l");
				client_cap = -1;
				modes.erase(it);
				modsremoved += "l";
			}
		}
		default:
			break;
		}
	}
	std::string target = "";
	if(cmd.size() > 3)
		target = " " + cmd[3];
	sendMsg(client, RPL_MODE(client, cmd[1], modsremoved, target));
	sendToChannel(RPL_MODE(client, cmd[1], modsremoved, target), client->getFd());
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
		channel->remMode(cli, cmd,  cmd[2].substr(1));
		
}	
