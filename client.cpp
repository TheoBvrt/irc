#include "./headers/ft_irc.hpp"

int main(int argc, char *argv[])
{
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

	connect(clientSocket, (struct sockaddr*)&serverAddress,
		sizeof(serverAddress));

	const char* message = argv[1];
	send(clientSocket, message, strlen(message), 0);

	close(clientSocket);

	return 0;
}