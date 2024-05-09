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
#include <istream>

class Client
{
	private:
		int _fd;
		std::string _IPaddr;
		std::string _username;
		std::string _nickname;
		std::string _buff;
		bool logged;
		// bool registered;
	public:
		Client();
		~Client();
		int getFd();
		void setFd(int fd);
		void setIPaddr(std::string ipadd);
		void setUsername(std::string username);
		void setNick(std::string nickname);
		void setBuff(std::string buff);
		void setLogged(bool bool_);
		bool getLogged();
		std::string getBuff(){return _buff;}
		std::string getNick();
};