#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"

class Server {
	private:
		int _serverPort;
		std::map<int, std::string> _socketBuffers;
	
	public:
		Server(int serverPort);
		~Server();
		Server(const Server& other);
		Server& operator=(const Server& other);
		
		int start();
};

#endif