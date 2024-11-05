LIBFT = Libft/libft.a
SOURCES = server.c client.c
SOURCES_BONUS = server_bonus.c client_bonus.c
OBJECTS = $(SOURCES:.c=.o)
OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./Libft/

all: server client $(LIBFT)
bonus: $(OBJECTS_BONUS) server_bonus client_bonus $(LIBFT)

server: server.o $(LIBFT)
	$(CC) -o $@ $^ -L Libft/ -lft

client: client.o $(LIBFT)
	$(CC) -o $@ $^ -L Libft/ -lft

server_bonus: server_bonus.o $(LIBFT)
	$(CC) -o $@ $^ -L Libft/ -lft

client_bonus: client_bonus.o $(LIBFT)
	$(CC) -o $@ $^ -L Libft/ -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C Libft/

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)
	@make -C Libft/ clean

fclean: clean
	rm -f server client server_bonus client_bonus
	@make -C Libft/ fclean

re: fclean all

.PHONY: all clean fclean re
