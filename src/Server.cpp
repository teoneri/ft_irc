/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:32:20 by mneri             #+#    #+#             */
/*   Updated: 2024/05/09 17:59:42 by mneri            ###   ########.fr       */
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
	std::cout << "\e[1;32mServer " << _serverSocket << "connected\e[0;37m" << std::endl;
	std::cout << "Waiting to accept connection...\n";
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
	Client cli = Client();
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
	for(size_t i = 0; i < clients.size(); i++)
	{
		if(fd == clients[i].getFd())
		{
			return &clients[i];
		}
	}
	return NULL;
}

void Server::removeClient(int fd)
{
	for(size_t i = 0; i < clients.size(); i++)
	{
		if(fd == clients[i].getFd())
		{
			clients.erase(clients.begin() + i);
			return;
		}
	}
}

std::vector<std::string> Server::splitBuffCommand(std::string buff)
{
	std::vector<std::string> vec;
	std::istringstream iss(buff);
	std::string line;
	while(std::getline(iss, line))
	{
		size_t pos = line.find_first_of("\r\n");
		if(pos != std::string::npos)
			line = line.substr(0, pos);
		vec.push_back(line);
	}
	return vec;
}


void Server::ReceiveNewData(int fd)
{
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	Client *client = getClient(fd);
	ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);
	if(bytes <= 0)
	{
		std::cout << "Client disconnected\n";
		removeClient(fd);
		close(fd);
	}
	else
	{
		client->setBuff(buff);
		if(client->getBuff().find_first_of("\r\n") == std::string::npos)
			return;
		_cmd = splitBuffCommand(buff);
		parseCommand(fd);
		
	}
}

void Server::parseCommand(int fd)
{

	if((_cmd[0] == "PASS" || _cmd[0] == "pass"))
		PASS(fd);
	if((_cmd[0] == "NICK" || _cmd[0] == "nick"))
		NICK(fd);
}

void Server::PASS(int fd)
{
	Client *cli = getClient(fd);
	if(_cmd.size() < 2)
		ERR_NEEDMOREPARAMS(cli, "PASS");
	else if(_cmd[1] == _password)
	{
		if(cli->getLogged() == true)
			ERR_ALREADYREGISTERED(cli);
		else
			cli->setLogged(true);
	}
}

void Server::NICK(int fd)
{
	// Client *cli = getClient(fd);
	(void)fd;
}
