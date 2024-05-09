/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:57:54 by mneri             #+#    #+#             */
/*   Updated: 2024/05/09 17:23:20 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client() : logged(false)
{
	_IPaddr.clear();
	_username.clear();
	_nickname = "*";
	_buff.clear();
}

Client::~Client(){}


int Client::getFd()
{
	return _fd;
}

void Client::setUsername(std::string username)
{
	_username = username;
}
void Client::setNick(std::string nickname)
{
	_nickname = nickname;
}
void Client::setBuff(std::string buff)
{
	_buff = buff;
}

void Client::setFd(int fd)
{
	_fd = fd;
}

void Client::setIPaddr(std::string ipadd)
{
	_IPaddr = ipadd;
}

void Client::setLogged(bool bool_)
{
	logged = bool_;
}

bool Client::getLogged()
{
	return logged;
}

std::string Client::getNick()
{
	return _nickname;
}
