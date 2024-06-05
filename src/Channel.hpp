/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teo <teo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:45:39 by mneri             #+#    #+#             */
/*   Updated: 2024/06/05 17:43:52 by teo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <algorithm>
#include <ctime>
#include <sstream>
#include "Client.hpp"
#include "Error.hpp"

class Client;

class Channel
{
	private:
		std::string _name;
		std::string _password;
		std::string _topic;
		std::string _creationTime;
		std::vector<Client> clients;	
		std::vector<Client> admins;
		std::vector<Client> invited;
		bool inv_only;
		bool adm_topic;
		int client_cap;
		std::vector<std::string> modes;
	public:
		Channel();
		~Channel();
		//getters
		std::string getName();
		std::string getPassword();
		std::string getTopic();
		Client *getClient(int fd);
		Client *getAdmins(int fd);
		Client *getInvited(int fd);
		Client *getClientInChannel(int fd);
		Client *getAdminbyName(std::string adminName);
		Client *getClientbyName(std::string clientName);
		bool getInvonly();
		bool getAdmtopic();
		int getClientcap();
		std::vector<std::string> getModes();
		std::string getClientList();
		std::string getCreationTime();
		//setters
		void setName(std::string name);
		void setPassword(std::string password);
		void setTopic(std::string topic);
		void setInvonly(bool inv);
		void setClientcap(int inv);
		void setAdmtopic(bool adm);
		void setCreationTime();
		//misc
		void addClient(Client *client);
		void addAdmins(Client *client);
		void addInvited(Client *client);
		void addModes(std::string mode);
		void sendToChannel(std::string msg, int fd);
		std::string displayMode();
		size_t countClients();
		void remAdmins(int fd);
		void remClients(int fd);
		void remInvited(int fd);
		void addMode(Client *client, std::vector<std::string> cmd, std::string mode);
		void remMode(Client *client, std::vector<std::string> cmd,  std::string mode);
		void parseKickCommand(Client *client, std::vector<std::string> cmd);
		void parseTopicCommand(Client *client, std::vector<std::string> cmd);
		void parsePartCommand(Client *client, std::vector<std::string> cmd);

};