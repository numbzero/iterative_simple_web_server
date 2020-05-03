CC = gcc
CCFLAGS = -Wall -Werror -Wextra
CLEAN = rm
CLEAN_FLAGS = -f
SRC = *.c
OBJ = *.o
NAME = web_server

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $^ -o $@

$(OBJ): $(SRC)
	$(CC) $(CCFLAGS) -c $^

re: fclean all

clean:
	$(CLEAN) $(CLEAN_FLAGS) $(OBJ)

fclean: clean
	$(CLEAN) $(CLEAN_FLAGS) $(NAME)