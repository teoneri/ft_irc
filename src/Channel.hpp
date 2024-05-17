/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:45:39 by mneri             #+#    #+#             */
/*   Updated: 2024/05/17 17:43:23 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Client.hpp"
#include "Error.hpp"

class Client;

class Channel
{
	private:
		std::string _name;
		std::string _password;
		std::string _topic;
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
		bool getInvonly();
		bool getAdmtopic();
		int getClientcap();
		std::string getTopic();
		std::string getPassword();
		std::vector<std::string> getModes();
		//setters
		void setName(std::string name);
		void setPassword(std::string password);
		void setTopic(std::string topic);
		void setInvonly(bool inv);
		void setClientcap(int inv);
		void setAdmtopic(bool adm);
		//misc
		void addClient(Client *client);
		void addAdmins(Client *client);
		void addInvited(Client *client);
		void addModes(std::string mode);
		void sendToChannel(std::string msg);
		std::string displayMode();
		size_t countClients();
		void addMode(Client *client, std::string cmd);
		void remMode(Client *client, std::string cmd);

};