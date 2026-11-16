NAME = ft_irc
SRCS = main.cpp $(wildcard ./srcs/*.cpp)

OBJS = ${SRCS:.cpp=.o}
CC = c++
RM = rm -f
CFLAGS = -Iheaders -std=c++98

all : ${NAME}

%.o : %.cpp
	${CC} ${CFLAGS} -c $< -o $@

${NAME} : ${OBJS}
	$(CC) $(OBJS) -o $(NAME)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all