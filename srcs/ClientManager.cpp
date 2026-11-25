#include "ClientManager.hpp"

ClientManager::ClientManager()
{
}

ClientManager::~ClientManager()
{
}

ClientManager::ClientManager(const ClientManager& other)
{
	*this = other;
}

ClientManager& ClientManager::operator=(const ClientManager& other)
{
	if (this != &other)
	{
		_clients = other._clients;
	}
	return *this;
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