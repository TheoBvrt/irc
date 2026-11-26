#ifndef SERVER_HPP
# define SERVER_HPP

# include "ft_irc.hpp"
# include "ClientManager.hpp"

class Server {
	private:
		int _serverPort;
		std::map<int, std::string> _socketBuffers;
		std::vector<std::string> _commandQueue;
	
		ClientManager _clientManager;
	public:
		Server(int serverPort);
		~Server();
		Server(const Server& other);
		Server& operator=(const Server& other);
		
		int start();
		void addCommandToQueue(const int fd, const std::string cmd);
};

#endif