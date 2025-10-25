NAME_SERVER = server
NAME_CLIENT = client

SRC_SERVER = server.c
SRC_CLIENT = client.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

clean:
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	@echo "Cleaned almost everything."

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	@echo "Cleaned everything."

re: fclean all

.PHONY: all clean fclean re