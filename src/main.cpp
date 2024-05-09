/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <mneri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:47:36 by mneri             #+#    #+#             */
/*   Updated: 2024/05/09 16:03:12 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"

int main(int argc, char **argv)
{
	Server ser = Server();
	int port = checkPort(argv[1]);
	if(argc == 3)
	{
		if(!port)
		{
			std::cout << "Invalid port\n";
			return 0;
		}	
		try
		{
			signal(SIGINT, Server::SignalHandler);
			signal(SIGQUIT, Server::SignalHandler);
			ser.ServerInit(port, argv[2]);
		}
		catch(const std::exception& e)
		{
			ser.CloseFds();
			std::cerr << e.what() << '\n';
		}
		std::cout << "The Server is Offline" << std::endl;
	}
}