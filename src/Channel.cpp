/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teo <teo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:59:03 by mneri             #+#    #+#             */
/*   Updated: 2024/06/05 17:43:26 by teo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel() 
{
	_name = "";
	_password = "";
	_topic = "";
	client_cap = -1;
	inv_only = false;
	adm_topic = false;
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
	if(clients.empty())
		return NULL;
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

Client *Channel::getClientInChannel(int fd)
{	
	std::vector<Client>::iterator it;
	for(it = admins.begin(); it != admins.end(); it++)
	{
		if(it->getFd() == fd)
			return &(*it);
	}
	for(it= clients.begin(); it != clients.end(); it++)
	{
		if(it->getFd() == fd)
			return &(*it);
	}
	return NULL;
	
}

Client *Channel::getInvited(int fd)
{
	std::vector<Client>::iterator it;
	for(it = invited.begin(); it != invited.end(); it++)
	{
		if(it->getFd() == fd)
			return &(*it);
	}
	return NULL;
}

std::string Channel::getClientList()
{
	std::string list;
	for(size_t i = 0; i < admins.size(); i++)
	{
		list += "@" + admins[i].getNick();
		if((i + 1) < admins.size())
			list += " ";
	}
	for(size_t i = 0; i < clients.size(); i++)
	{
		if(!getAdminbyName(clients[i].getNick()))
			list += clients[i].getNick();
		if((i + 1) < clients.size())
			list += " ";
	}
	return list;
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


bool Channel::getInvonly()
{
	return inv_only;
}

void Channel::setInvonly(bool inv)
{
	inv_only = inv;
}

void Channel::setCreationTime()
{
	std::time_t _time = std::time(NULL);
	std::ostringstream oss;
	oss << _time;
	this->_creationTime = std::string(oss.str());
}

std::string Channel::getCreationTime()
{
	return _creationTime;
}

bool Channel::getAdmtopic()
{
	return adm_topic;
}

void Channel::setAdmtopic(bool adm)
{
	adm_topic = adm;
}

int Channel::getClientcap()
{
	return client_cap;
}
		
void Channel::setClientcap(int cap)
{
	client_cap = cap;
}

void Channel::sendToChannel(std::string msg, int fd)
{
	
	std::vector<Client>::iterator it;
	for(it = clients.begin(); it != clients.end(); it++)
	{
		if(it->getFd() != fd)
			sendMsg(&(*it), msg);
	}
}

size_t Channel::countClients()
{
	return clients.size();
}

std::vector<std::string> Channel::getModes()
{
	return modes;
}

void Channel::addModes(std::string mode)
{
	modes.push_back(mode);
}

void Channel::remAdmins(int fd)
{
	std::vector<Client>::iterator it;

	for(it = admins.begin(); it != admins.end(); it++)
	{
		if(it->getFd() == fd)
		{	
			admins.erase(it);
			return ;
		}
	}
}

void Channel::remClients(int fd)
{
	std::vector<Client>::iterator it;

	for(it = clients.begin(); it != clients.end(); it++)
	{
		if(it->getFd() == fd)
		{	
			clients.erase(it);
			return ;
		}
	}
}

void Channel::remInvited(int fd)
{
	std::vector<Client>::iterator it;

	for(it = invited.begin(); it != invited.end(); it++)
	{
		if(it->getFd() == fd)
		{	
			invited.erase(it);
			return ;
		}
	}
}

Client *Channel::getAdminbyName(std::string adminName)
{
	std::vector<Client>::iterator it;
	for(it = admins.begin(); it != admins.end(); it++)
	{
		if(it->getNick() == adminName)
			return &(*it);
	}
	return NULL;
}


Client *Channel::getClientbyName(std::string clientName)
{
	std::vector<Client>::iterator it;
	for(it = clients.begin(); it != clients.end(); it++)
	{
		if(it->getNick() == clientName)
			return &(*it);
	}
	return NULL;
}
