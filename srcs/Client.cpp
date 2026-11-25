#include "Client.hpp"

Client::Client()
{
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
		_hostNamel = other._hostNamel;
		_ipAddress = other._ipAddress;
		_isOperator = other._isOperator;
		_isInvisible = other._isInvisible;
		_isRegistered = other._isRegistered;
		_isAuthentifcated = other._isAuthentifcated;
	}
	return *this;
}

int Client::getFd(void) const {
	return (this->_fd);
}

std::string Client::getNickName(void) const {
	return (this->_nickName);
} 