#include "ClientManager.hpp"

ClientManager::ClientManager(Server& server)
	: _server(server)
{
}

ClientManager::ClientManager(const ClientManager& other)
	: _server(other._server)
{
	*this = other;
}

ClientManager::~ClientManager()
{

}

ClientManager& ClientManager::operator=(const ClientManager& other)
{
	if (this != &other)
	{
		_clients = other._clients;
	}
	return *this;
}

void ClientManager::addClient(const int fd)
{
	Client newClient(fd);

	this->_clients.push_back(newClient);
}

void ClientManager::deleteClient(const int fd)
{
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i].getFd() == fd)
		{
			this->_clients.erase(this->_clients.begin() + i);
			return ;
		}
	}
}

void ClientManager::deleteClient(const std::string nickName)
{
	for (size_t i = 0; i < this->_clients.size(); i++)
	{
		if (this->_clients[i].getNickName() == nickName)
		{
			this->_clients.erase(this->_clients.begin() + i);
			return ;
		}
	}
}

Client* ClientManager::getClient(const int fd)
{
	std::vector<Client>::iterator it;

	for (it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		if (it->getFd() == fd)
			return &(*it); 
	}

	return (NULL);
}

Client* ClientManager::getClient(const std::string nickName)
{
	std::vector<Client>::iterator it;

	for (it = this->_clients.begin(); it != this->_clients.end(); ++it) {
		if (it->getNickName() == nickName)
			return &(*it); 
	}

	return (NULL);
}

int ClientManager::getClientsSize() const {
	return (this->_clients.size());
}