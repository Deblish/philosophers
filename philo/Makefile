NAME = philo
CC = cc
INCLUDES = -Iincludes
CFLAGS = -Wall -Wextra -Werror
HEADER = philo.h

SOURCES = srcs/libft.c \
		  srcs/time.c \
		  srcs/parse.c \
		  srcs/monitor.c \
		  srcs/table.c \
		  srcs/routine.c \
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
