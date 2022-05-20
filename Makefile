NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g
SRC = src/main.c src/loop.c  \
src/environment/hashTable.c src/environment/path.c  src/builtins/environment.c  src/builtins/cd.c src/environment/localvars.c \
src/lexer/tokenUtils2.c src/lexer/tokensUtils.c src/lexer/lexer.c \
src/expander/expanderUtils.c src/expander/expander.c src/expander/expander2.c \
src/parser/parser.c src/parser/parsingUtils.c src/parser/parsingUtils2.c src/parser/makeRedirects.c src/parser/heredoc.c \
src/executor/executor.c src/executor/executorUtils.c src/executor/signals.c \

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
	@rm -rf src/parser/*.o
	@rm -rf src/lexer/*.o
	@rm -rf src/expander/*.o
	@rm -rf src/builtins/*.o
	@rm -rf src/executor/*.o
	@rm -rf src/environment/*.o



fclean: clean
	rm -rf $(NAME)

re: fclean all
