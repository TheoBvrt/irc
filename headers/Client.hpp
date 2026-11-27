#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"

class Server;

class Client {
	private:
		int _fd;

		std::string _buffer;
		std::string _nickName;
		std::string _userName;
		std::string _realName;
		std::string _hostName;
		std::string _ipAddress;

		bool _isOperator;
		bool _isInvisible;
		bool _isRegistered;
		bool _isAuthentifcated;

	public:
		Client(const int fd);
		~Client();
		Client(const Client& other);
		Client& operator=(const Client& other);

		int getFd(void) const;
		std::string getNickName(void) const;
		
		void fillBuffer(const char buffer[1024], int bytesReceived, Server& server);
};

#endif