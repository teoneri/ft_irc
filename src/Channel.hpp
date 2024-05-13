/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:45:39 by mneri             #+#    #+#             */
/*   Updated: 2024/05/13 16:39:52 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

class Client;

class Channel
{
	private:
		std::string _name;
		std::string _password;
		std::string _topic;
		std::vector<Client> clients;	
		std::vector<Client> admins;
	public:
		Channel();
		~Channel();
		std::string getName();
		std::string getPassword();
		std::string getTopic();
		void setName(std::string name);
		void setPassword(std::string password);
		void setTopic(std::string topic);
		Client *getClient(int fd);
		Client *getAdmins(int fd);
		void addClient(Client *client);
		void addAdmins(Client *client);
};