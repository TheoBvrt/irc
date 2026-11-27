#ifndef CLIENT_HPP
# define CLIENT_HPP

class Command {
	private:
		
	public:
		Command();
		~Command();
		Command(const Command& other);
		Command& operator=(const Command& other);
};

#endif