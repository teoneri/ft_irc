/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:45:39 by mneri             #+#    #+#             */
/*   Updated: 2024/05/07 15:48:01 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"

class Client;

class Channel
{
	private:
		std::string name;
		std::string password;
		std::vector<Client> clients;	
		std::vector<Client> admins;
		
};