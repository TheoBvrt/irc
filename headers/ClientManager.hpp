#ifndef CLIENT_MANAGER_HPP
# define CLIENT_MANAGER_HPP

# include "ft_irc.hpp"
# include "Client.hpp"
class Client;

class ClientManager {
	private:
		std::vector<Client> _clients;
	public:
		ClientManager();
		~ClientManager();
		ClientManager(const ClientManager& other);
		ClientManager& operator=(const ClientManager& other);

		Client* getClient(const int fd);
		Client* getClient(const std::string nickName);

		void addClient();
		void deleteClientByFd();
};

#endif