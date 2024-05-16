/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:45:39 by mneri             #+#    #+#             */
/*   Updated: 2024/05/16 17:50:32 by mneri            ###   ########.fr       */
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
	public:
		Channel();
		~Channel();
		std::string getName();
		std::string getPassword();
		std::string getTopic();
		void setName(std::string name);
		void setPassword(std::string password);
		void setTopic(std::string topic);
		std::string getTopic();
		std::string getPassword();
		Client *getClient(int fd);
		Client *getAdmins(int fd);
		Client *getInvited(int fd);
		void addClient(Client *client);
		void addAdmins(Client *client);
		void addInvited(Client *client);
		bool getInvonly();
		void setInvonly(bool inv);
		void sendToChannel(std::string msg);
};