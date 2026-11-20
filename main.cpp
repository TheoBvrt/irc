#include "ft_irc.hpp"

int main(int argc, char *argv[])
{
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	bind(serverSocket, (struct sockaddr*)&serverAddress,
		sizeof(serverAddress));
	listen(serverSocket, 5);

	std::vector<pollfd> pollfds;

	pollfd tmpPollFd;
	tmpPollFd.fd = serverSocket;
	tmpPollFd.events = POLLIN;
	tmpPollFd.revents = 0;

	pollfds.push_back(tmpPollFd);

	while (true)
	{
		poll(pollfds.data(), pollfds.size(), 5000);

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

					std::cout << newClientFd << std::endl;
				}
				else
				{
					char buffer[1024];

					int bytesReceived = recv(pollfds[i].fd, buffer, sizeof(buffer), 0);

					if (bytesReceived == 0)
					{
		
						std::cout << "Client disconnected: " << pollfds[i].fd << std::endl;

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
						std::cout << "Received: " << buffer << std::endl;
					}
				}
			}
		}
		
	}

	close(serverSocket);
		return 0;
}