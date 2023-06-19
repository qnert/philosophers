CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

SRCS = ./srcs/philo.c ./srcs/check.c ./srcs/utils.c ./srcs/timestamp.c ./srcs/routine_funcs.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cd ft_printf && make
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./ft_printf/libftprintf.a

clean:
	rm -f $(OBJS)
	cd ft_printf && make fclean

fclean: clean
	rm -f $(NAME)

re: fclean all
