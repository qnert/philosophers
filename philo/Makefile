CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRCS = ./srcs/philo.c ./srcs/check.c ./srcs/utils.c ./srcs/timestamp.c ./srcs/routine_funcs.c ./srcs/init.c ./srcs/actions.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
