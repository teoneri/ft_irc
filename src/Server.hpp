/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:29:06 by mneri             #+#    #+#             */
/*   Updated: 2024/06/03 17:04:56 by mneri            ###   ########.fr       */
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
#include "Utils.hpp"
#include "Channel.hpp"

class Client;
class Channel;

class Server
{
	private:
		int _port;
		int _serverSocket;
		static bool _signal;
		struct sockaddr_in add;
		std::vector<struct pollfd> fds;
		struct pollfd NewPoll;
		std::string _password;
		std::vector<Client> clients;
		std::vector<Channel> channels;
		std::vector<std::string> _cmd;
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
		Client *getClientbyName(std::string name);
		Channel *getChannel(std::string channelname);
		std::vector<std::string> SplitRN(std::string buff);
		std::vector<std::string> splitBuffCommand(std::string buff);
		void parseCommand(int fd, std::string tmp);
		void channelFound(Client *client, Channel *channel, std::vector<std::string> cmd, int fd);
		void channelNotFound(Client *client, std::string name);
		void parseInviteCommand(Client *client, std::vector<std::string> cmd, Channel *channel);
		void parseMsgCommand(Client *client, std::vector<std::string> cmd, Channel *channel, Client *recipient);
		void PASS(int fd, std::vector<std::string> cmd);
		void NICK(int fd, std::vector<std::string> cmd);
		void USER(int fd, std::vector<std::string> cmd);
		void JOIN(int fd, std::vector<std::string> cmd);
		void MODE(int fd, std::vector<std::string> cmd);
		void KICK(int fd, std::vector<std::string> cmd);
		void INVITE(int fd, std::vector<std::string> cmd);
		void TOPIC(int fd, std::vector<std::string> cmd);
		void PART(int fd, std::vector<std::string> cmd);
		void QUIT(int fd, std::vector<std::string> cmd);
		void PRIVMSG(int fd, std::vector<std::string> cmd);

};