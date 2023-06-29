CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo_bonus

SRCS =

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
