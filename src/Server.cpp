/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:32:20 by mneri             #+#    #+#             */
/*   Updated: 2024/06/11 18:06:33 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

bool Server::_signal = false;

Server::Server()
{
}

void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << "Signal Received" << std::endl;
	_signal = true;
}

void Server::CloseFds()
{
	for(size_t i = 0; i < clients.size(); i++)
	{
		std::cout << "\e[1;31mClient" << clients[i].getFd() << "> Disconnected\e[0;37m" << std::endl;
		close(clients[i].getFd());
	}
	if(_serverSocket != -1)
	{
		std::cout << "\e[1;31mServer <" << _serverSocket << "> Disconnected\e[0;37m" << std::endl;
		close(_serverSocket);
	}
}	

void Server::SerSocket()
{
	int en = 1;
	add.sin_family = AF_INET;
	add.sin_port = htons(_port);
	add.sin_addr.s_addr = INADDR_ANY;
	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(_serverSocket == -1)
		throw(std::runtime_error("Failed to create socket"));
	if(setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("Failed to set option (SO_REUSEADDR) on socket"));
	if(fcntl(_serverSocket, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("Failed to set option (O_NONBLOCK) on socket"));
	if(bind(_serverSocket, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("failed to bind socket"));
	if(listen(_serverSocket, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() failed"));
		
	NewPoll.fd = _serverSocket;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	fds.push_back(NewPoll);
}

void Server::ServerInit(int port, std::string pass)
{
	this->_port = port;
	this->_password = pass;
	SerSocket();
	std::cout << GREEN << "Server " << _serverSocket << " connected" << WHITE << std::endl;
	std::cout << YELLOW << "Waiting to accept connection...\n" << WHITE;
	while(Server::_signal == false)
	{
		if((poll(&fds[0], fds.size(), -1) == -1) && Server::_signal == false)
			throw(std::runtime_error("poll() failed"));
		for(size_t i = 0; i < fds.size(); i++)
		{
			if(fds[i].revents & POLLIN)
			{
				if(fds[i].fd == _serverSocket)
					AcceptNewClient();
				else
					ReceiveNewData(fds[i].fd);
			}
		}
	}
	CloseFds();
}

void Server::AcceptNewClient()
{
	Client cli;
	struct sockaddr_in cliadd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(cliadd);
	
	int incofd = accept(_serverSocket, (sockaddr *)&(cliadd), &len);
	if(incofd == -1)
	{
		std::cout << "accept() failed" << std::endl;
		return;
	}
	if(fcntl(incofd, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cout << "fcntl() failed" << std::endl;
		return;
	}
	NewPoll.fd = incofd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	cli.setFd(incofd);
	cli.setIPaddr(inet_ntoa((cliadd.sin_addr)));
	clients.push_back(cli);
	fds.push_back(NewPoll);
	std::cout << "Client <" << incofd << "> Connected" << std::endl;
}

Client *Server::getClient(int fd)
{
	std::vector<Client>::iterator it;
	for(it = clients.begin(); it != clients.end(); it++)
	{
		if(it->getFd() == fd)
			return &(*it);
	}
	return NULL;
}


void Server::removeClient(int fd)
{
	std::vector<Channel>::iterator it;
	for(it = channels.begin(); it != channels.end(); it++)
	{
		it->remAdmins(fd);
		it->remClients(fd);
		it->remInvited(fd);
	}
	for(size_t i = 0; i < clients.size(); i++)
	{
		if(fd == clients[i].getFd())
		{
			clients.erase(clients.begin() + i);
		}
	}
	for(std::vector<struct pollfd>::iterator it = fds.begin(); it != fds.end(); it++)
	{
		if(it->fd == fd)
		{	
			fds.erase(it);
			break;
		}
	}
}

Channel *Server::getChannel(std::string channelname)
{
	std::vector<Channel>::iterator it;
	for(it = channels.begin(); it != channels.end(); it++)
	{
		if(it->getName() == channelname)
			return &(*it);
	}
	return NULL;
}


std::vector<std::string> Server::SplitRN(std::string buff)
{
	std::istringstream iss(buff);
	std::string line;
	std::vector<std::string> vec;
	while(std::getline(iss, line))
	{
		size_t pos = line.find_first_of("\r\n");
		if(pos != std::string::npos)
			line = line.substr(0, pos);
		vec.push_back(line);
	}
	return vec;
}

std::vector<std::string> Server::splitBuffCommand(std::string buff)
{
	std::istringstream iss(buff);
	std::string token;
	std::vector<std::string> vec;
	while(iss >> token)
	{
		vec.push_back(token);
		token.clear();	
	}
	return vec;
}


void Server::ReceiveNewData(int fd)
{
	char buff[1024];
	std::vector<std::string> tmp;
	memset(buff, 0, sizeof(buff));
	Client *client = getClient(fd);
	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if(bytes <= 0)
	{
		QUIT(fd, tmp);
	}
	else
	{
		client->setBuff(buff);
		if(client->getBuff().find_first_of("\r\n") == std::string::npos)
			return;
		tmp = SplitRN(client->getBuff());
		for(size_t i = 0; i < tmp.size(); i++)
			parseCommand(fd, tmp[i]);
		if(getClient(fd))
			getClient(fd)->clearBuffer();
	}
}

void Server::parseCommand(int fd, std::string tmp)
{
	std::vector<std::string> cmd = splitBuffCommand(tmp);
	if(cmd.empty())
		return;
	else if((cmd[0] == "PASS" || cmd[0] == "pass"))
		PASS(fd, cmd);
	else if((cmd[0] == "NICK" || cmd[0] == "nick"))
		NICK(fd, cmd);
	else if((cmd[0] == "USER" || cmd[0] == "user"))
		USER(fd, cmd);
	else if(getClient(fd)->getRegistered() == true)
	{
		if((cmd[0] == "JOIN" || cmd[0] == "join"))
			JOIN(fd, cmd);
		else if((cmd[0] == "MODE" || cmd[0] == "mode"))
			MODE(fd, cmd);
		else if((cmd[0] == "KICK" || cmd[0] == "kick"))
			KICK(fd, cmd);
		else if((cmd[0] == "INVITE" || cmd[0] == "invite"))
			INVITE(fd, cmd);
		else if((cmd[0] == "TOPIC" || cmd[0] == "topic"))
			TOPIC(fd, cmd);		
		else if((cmd[0] == "PART" || cmd[0] == "part"))
			PART(fd, cmd);
		else if((cmd[0] == "QUIT" || cmd[0] == "quit"))
			QUIT(fd, cmd);
		else if((cmd[0] == "PRIVMSG" || cmd[0] == "privmsg"))
			PRIVMSG(fd, cmd);
		else if(cmd.size())
			ERR_CMDNOTFOUND(getClient(fd), cmd[0]);
	}
	else if(!getClient(fd)->getRegistered())
		ERR_NOTREGISTERED(getClient(fd));
}

void Server::PASS(int fd, std::vector<std::string> cmd)
{
	Client *cli = getClient(fd);
	if(cmd.size() < 2)
		ERR_NEEDMOREPARAMS(cli, "PASS");
	else if(cli->getLogged() == true)
			ERR_ALREADYREGISTERED(cli);
	else if(cmd[1] == _password)
			cli->setLogged(true);
	else if(cmd[1] != _password)
		ERR_PASSWDMISMATCH(cli);
}


void Server::NICK(int fd, std::vector<std::string> cmd)
{
	Client *cli = getClient(fd);
	
	if(!cli->getLogged())
	{
		ERR_NOTREGISTERED(cli);
		return;
	}
	else if(cmd.size() == 1)
	{
		ERR_NONICKNAMEGIVEN(cli);
		return;
	}
	else if(cmd[1].find_first_of('#') == 0 || cmd[1].find_first_of(':') == 0 || cmd.size() < 2)
	{
		ERR_ERRONEUSNICKNAME(cli, cmd[1]);
		return;
	}
	for(size_t i = 0; i < clients.size(); i++)
	{
		if(cmd[1] == clients[i].getNick())
		{
			ERR_NICKNAMEINUSE(cli, cmd[1]);
			return;
		}
	}
	if(cli->getRegistered())
	{
		sendMsg(cli, RPL_NICKCHANGE(cli->getNick(), cmd[1]));
		sendToAllChannels(RPL_NICKCHANGE(cli->getNick(), cmd[1]), cli->getFd());
	}
	cli->setNick(cmd[1]);
	cli->setNicked(true);
	if(cli->getUsered() && !cli->getRegistered())
	{
		cli->setRegistered(true);
		RPL_WELCOME(cli);
	}
}

void Server::USER(int fd, std::vector<std::string> cmd)
{
	Client *cli = getClient(fd);
	std::string name;

	if(!cli->getLogged())
		ERR_NOTREGISTERED(cli);
	else if(cmd.size() < 5)
		ERR_NEEDMOREPARAMS(cli, "USER");
	else if(!cli->getUser().empty())
		ERR_ALREADYREGISTERED(cli);
	else
	{
		cli->setUsername(cmd[1]);
		for(size_t i = 4; i < cmd.size(); i++)
		{
			name += cmd[i];
			if(i != cmd.size() - 1)
				name += " ";
		}
		cli->setRealname(name);
		cli->setUsered(true);
		if(cli->getNicked())
		{
			cli->setRegistered(true);
			RPL_WELCOME(cli);
		}
	}
}

Client *Server::getClientbyName(std::string name)
{
	std::vector<Client>::iterator it;
	for(it = clients.begin(); it != clients.end(); it++)
	{
		if(it->getNick() == name)
			return &(*it);
	}
	return NULL;
}

void Server::sendToAllChannels(std::string msg, int fd)
{
	std::vector<Channel>::iterator it;
	for (it = channels.begin(); it != channels.end(); it++)
	{
		if (it->getClient(fd))
			it->sendToChannel(msg, fd);
	}
}
