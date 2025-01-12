NAME = philo
CC = cc
INCLUDES = -Iincludes
CFLAGS = -Wall -Wextra -Werror #-g -O0
HEADER = philo.h

SOURCES = srcs/ft_atoi.c \
		  srcs/time.c \
		  srcs/parse.c \
		  srcs/philo_states.c \
		  srcs/getters.c \
		  srcs/setters.c \
		  srcs/monitor_routine.c \
		  srcs/table_inits.c \
		  srcs/philo_routine.c \
		  srcs/simulation.c \
		  srcs/main.c \

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
