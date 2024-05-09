/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:29:06 by mneri             #+#    #+#             */
/*   Updated: 2024/05/09 16:47:33 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>  
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h>  
#include <fcntl.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <poll.h> 
#include <csignal>
#include <string.h>
#include <sstream>
#include "Client.hpp"
#include "Error.hpp"

class Server
{
	private:
		int _port;
		int _serverSocket;
		std::string _password;
		static bool _signal;
		std::vector<Client> clients;
		std::vector<struct pollfd> fds;
		std::vector<std::string> _cmd;
		struct sockaddr_in add;
		struct pollfd NewPoll;
	public:
		Server();
		void ServerInit(int port, std::string pass);
		void SerSocket();
		void AcceptNewClient();
		void ReceiveNewData(int fd);
		static void SignalHandler(int signum);
		void CloseFds();
		void removeClient(int fd);
		Client *getClient(int fd);
		std::vector<std::string> splitBuffCommand(std::string buff);
		void parseCommand(int fd);
		void PASS(int fd);
		void NICK(int fd);

};