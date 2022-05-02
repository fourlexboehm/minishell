NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g
SRC = src/main.c src/hashTable.c src/path.c src/loop.c src/builtins/environment.c src/parser.c src/signals.c src/tokensUtils.c \
src/expander.c src/executor.c src/builtins/cd.c src/localvars.c src/tokenUtils2.c src/lexer.c src/expander2.c src/expanderUtils.c
INCLUDES = ./includes/
LIBFT = ./libft/
LIBFT_A = ./libft/libft.a
OBJECTS = $(SRC:.c=.o)


all: $(NAME)


.c.o:
	@gcc $(CFLAGS) -c $< -o $(<:.c=.o) -I$(INCLUDES)

$(NAME): $(OBJECTS)

	@make -C $(LIBFT) bonus
	@gcc $(CFLAGS) -o $(NAME) $(OBJECTS) leakcheck.c $(LIBFT_A) -lreadline
	#/opt/homebrew/Cellar/readline/8.1.2/lib/libhistory.a /opt/homebrew/Cellar/readline/8.1.2/lib/libreadline.a

clean:
	@make clean -C $(LIBFT)
	@rm -rf $(OBJS)
	@rm -rf src/*.o
	@rm -rf src/builtins/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all
