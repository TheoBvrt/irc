#include "Server.hpp"

Server::Server(int serverPort)
	: _serverPort(serverPort), _clientManager(*this)
{
}

Server::~Server()
{

}

Server::Server(const Server& other)
	: _serverPort(other._serverPort), _clientManager(*this)
{
	_socketBuffers = other._socketBuffers;
	_commandQueue = other._commandQueue;
}

Server& Server::operator=(const Server& other)
{
	if (this != &other)
    {
		_serverPort = other._serverPort;
		_socketBuffers = other._socketBuffers;
		_commandQueue = other._commandQueue;
	}
	return *this;
}

void Server::addCommandToQueue(const int fd, const std::string cmd)
{
	this->_commandQueue.push_back(cmd);
}

int Server::start()
{
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
		return (perror("socket"), 1);

	int opt = 1;
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	sockaddr_in serverAddress = {};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(this->_serverPort);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	if (bind(serverSocket, (struct sockaddr*)&serverAddress,
		sizeof(serverAddress)) < 0)
		return (perror("bind"), 1);

	std::cout << "BIND OK" << std::endl;

	if (listen(serverSocket, 5) < 0)
		return (perror("listen"), 1);

	std::cout << "LISTEN OK" << std::endl;

	std::vector<pollfd> pollfds;

	pollfd tmpPollFd;
	tmpPollFd.fd = serverSocket;
	tmpPollFd.events = POLLIN;
	tmpPollFd.revents = 0;

	pollfds.push_back(tmpPollFd);

	while (true)
	{
		poll(pollfds.data(), pollfds.size(), 1000);

		for (size_t i = 0; i < pollfds.size(); i++)
		{
			if (pollfds[i].revents & POLLIN)
			{
				if (pollfds[i].fd == serverSocket)
				{
					int newClientFd = accept(serverSocket, NULL, NULL);

					tmpPollFd.fd = newClientFd;
					tmpPollFd.events = POLLIN;
					tmpPollFd.revents = 0;
					pollfds.push_back(tmpPollFd);
		
					
					this->_clientManager.addClient(newClientFd);
				}
				else
				{
					char buffer[1024];

					int bytesReceived = recv(pollfds[i].fd, buffer, sizeof(buffer), 0);

					if (bytesReceived == 0)
					{
						std::cout << "Client disconnected: " << pollfds[i].fd << std::endl;

						this->_clientManager.deleteClient(pollfds[i].fd);
						close(pollfds[i].fd);
						pollfds.erase(pollfds.begin() + i);
						i--;
					}
					else if (bytesReceived < 0)
					{
						std::cerr << "recv error" << std::endl;
						close(pollfds[i].fd);
						pollfds.erase(pollfds.begin() + i);
						i--;
					}
					else
					{
						buffer[bytesReceived] = '\0';
						Client* client = this->_clientManager.getClient(pollfds[i].fd);

						client->fillBuffer(buffer, bytesReceived, *this);
					}
				}
			}
		}
		for (int i = 0; i < this->_commandQueue.size(); i ++)
			std::cout << "cmd : " << this->_commandQueue[i] << std::endl;

		std::cout << "(" << this->_clientManager.getClientsSize() << ")" << std::endl;
	}
	close(serverSocket);
	return 0;
}