/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:59:03 by mneri             #+#    #+#             */
/*   Updated: 2024/05/13 16:44:16 by mneri            ###   ########.fr       */
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
	std::vector<Client>::iterator it = clients.begin();
	for(it; it != clients.end(); it++)
	{
		if(it->getFd() == fd)
			return &(*it);
	}
	return NULL;
}

Client *Channel::getAdmins(int fd)
{
	std::vector<Client>::iterator it = admins.begin();
	for(it; it != admins.end(); it++)
	{
		if(it->getFd() == fd)
			return &(*it);
	}
	return NULL;
}

void Channel::setName(std::string name)
{
	_name = name
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

void Channel::addClient(Client *client)
{
    clients.push_back(*client);
}