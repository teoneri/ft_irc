/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:59:03 by mneri             #+#    #+#             */
/*   Updated: 2024/05/16 17:58:17 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel()
{
}

Channel::~Channel()
{
	
}

std::string Channel::getName()
{
	return _name;
}

std::string Channel::getPassword()
{
	return _password;
}

std::string Channel::getTopic()
{
	return _topic;
}

Client *Channel::getClient(int fd)
{
	std::vector<Client>::iterator it;
	for(it= clients.begin(); it != clients.end(); it++)
	{
		if(it->getFd() == fd)
			return &(*it);
	}
	return NULL;
}

Client *Channel::getAdmins(int fd)
{
	std::vector<Client>::iterator it;
	for(it = admins.begin(); it != admins.end(); it++)
	{
		if(it->getFd() == fd)
			return &(*it);
	}
	return NULL;
}

Client *Channel::getInvited(int fd)
{
	std::vector<Client>::iterator it;
	for(it = admins.begin(); it != invited.end(); it++)
	{
		if(it->getFd() == fd)
			return &(*it);
	}
	return NULL;
}

void Channel::setName(std::string name)
{
	_name = name;
}

void Channel::setPassword(std::string password)
{
	_password = password;
}

void Channel::setTopic(std::string topic)
{
	_topic = topic;
}

void Channel::addClient(Client *client)
{
    clients.push_back(*client);
}

void Channel::addAdmins(Client *client)
{
    admins.push_back(*client);
}

void Channel::addInvited(Client *client)
{
    invited.push_back(*client);
}

std::string Channel::getTopic()
{
	return _topic;
}
std::string Channel::getPassword()
{
	return _password
}

bool Channel::getInvonly()
{
	return inv_only;
}

void Channel::setInvonly(bool inv)
{
	inv_only = inv;
}

void Channel::sendToChannel(std::string msg)
{
	std::vector<Client>::iterator it;
	for(it = clients.begin(); it != clients.end(); it++)
	{
		sendMsg(&(*it), msg);
	}
}
