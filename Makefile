NAME = minishell
#CFLAGS = -g
CFLAGS = -Wall -Wextra -Werror -g
SRC = src/main.c src/hashTable.c src/path.c src/loop.c src/builtins/environment.c
INCLUDES = ./includes/
LIBFT = ./libft/
LIBFT_A = ./libft/libft.a
OBJECTS = $(SRC:.c=.o)


all: $(NAME)


$(NAME): $(OBJECTS)

	make -C $(LIBFT) bonus
	gcc $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBFT_A)

clean:
	make clean -C $(LIBFT)
	rm -rf $(OBJS)
	rm -rf src/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: all
	./push_swap 1 2 3

