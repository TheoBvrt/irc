#include "Client.hpp"
#include "Server.hpp"

Client::Client(const int fd)
{
	this->_fd = fd;
}

Client::~Client()
{
}

Client::Client(const Client& other)
{
	*this = other;
}

Client& Client::operator=(const Client& other)
{
	if (this != &other)
	{
		_fd = other._fd;
		_buffer = other._buffer;
		_nickName = other._nickName;
		_userName = other._userName;
		_realName = other._realName;
		_hostName = other._hostName;
		_ipAddress = other._ipAddress;
		_isOperator = other._isOperator;
		_isInvisible = other._isInvisible;
		_isRegistered = other._isRegistered;
		_isAuthentifcated = other._isAuthentifcated;
	}
	return *this;
}

void Client::fillBuffer(const char buffer[1024], int bytesReceived, Server& server) {
	this->_buffer.append(buffer, bytesReceived);

	size_t pos = this->_buffer.find("\r\n");
	while (pos != std::string::npos)
	{
		server.addCommandToQueue(this->_fd, this->_buffer.substr(0, pos));
		this->_buffer.erase(0, pos + 2);
		pos = this->_buffer.find("\r\n");
	}
}

int Client::getFd(void) const {
	return (this->_fd);
}

std::string Client::getNickName(void) const {
	return (this->_nickName);
}