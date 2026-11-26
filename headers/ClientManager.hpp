#ifndef CLIENT_MANAGER_HPP
# define CLIENT_MANAGER_HPP

# include "ft_irc.hpp"
# include "Client.hpp"

class Client;
class Server;

class ClientManager {
	private:
		std::vector<Client> _clients;
		Server& _server;
	public:
		ClientManager(Server& server);
		~ClientManager();
		ClientManager(const ClientManager& other);
		ClientManager& operator=(const ClientManager& other);

		Client* getClient(const int fd);
		Client* getClient(const std::string nickName);

		void addClient(const int fd);
		void deleteClient(const int fd);
		void deleteClient(const std::string nickName);
		int getClientsSize() const ;
		
};

#endif