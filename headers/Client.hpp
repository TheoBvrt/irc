#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "ft_irc.hpp"

class Client {
    private:
        int _fd;

        std::string _buffer;
        std::string _nickName;
        std::string _userName;
        std::string _realName;
        std::string _hostNamel;
        std::string _ipAddress;

        bool _isOperator;
        bool _isInvisible;
        bool _isRegistered;
        bool _isAuthentifcated;

    public:
        Client();
        ~Client();
        Client(const Client& other);
        Client& operator=(const Client& other);

		int getFd(void) const;
		std::string getNickName(void) const;
};

#endif