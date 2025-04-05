NAME_C = client
NAME_S = server

CC = cc
FLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC_C = client.c
SRC_S = server.c

OBJ_C = $(SRC_C:.c=.o)
OBJ_S = $(SRC_S:.c=.o)

COMPILE = $(CC) $(FLAGS)

all: $(NAME_C) $(NAME_S)

$(NAME_C): $(SRC_C)
	$(COMPILE) $(SRC_C) -o $(NAME_C)

$(NAME_S): $(SRC_S)
	$(COMPILE) $(SRC_S) -o $(NAME_S)

clean:
	$(RM) $(OBJ_C) $(OBJ_S)

fclean: clean
	$(RM) $(NAME_C) $(NAME_S)

re: fclean all

.PHONY: all clean fclean re
