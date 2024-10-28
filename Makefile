LIBFT = Libft/libft.a
SOURCES = server.c client.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./Libft/

all: server client $(LIBFT)

server: server.o $(LIBFT)
	$(CC) -o $@ $^ -L Libft/ -lft

client: client.o $(LIBFT)
	$(CC) -o $@ $^ -L Libft/ -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C Libft/

clean:
	rm -f $(OBJECTS)
	@make -C Libft/ clean

fclean: clean
	rm -f server client
	@make -C Libft/ fclean

re: fclean all

.PHONY: all clean fclean re
