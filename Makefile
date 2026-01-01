NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes

SRCS = $(shell find . -name "*.c" ! -path "./tests/*")
OBJ_DIR = .obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
READLINE_FLAGS = -lreadline -lncurses

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(READLINE_FLAGS) $(INCLUDES)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

val: re
	@valgrind --show-leak-kinds=all --leak-check=full --track-fds=all --suppressions=$(PWD)/readline.supp ./minishell

test: re
	@git clone https://github.com/LucasKuhn/minishell_tester
	@cd minishell_tester && (./tester || true) && cd ..
	@rm -rf minishell_tester

test_quotes: $(NAME)
	@$(CC) -o tests/test_quote_handling tests/test_quote_handling.c $(CFLAGS) $(INCLUDES) \
		core/parse/expander/quote_utils.c \
		core/parse/lexer/quote_removal.c \
		core/parse/expander/expand_utils_1.c \
		core/utils/string/*.c \
		core/utils/memory/*.c
	@tests/test_quote_handling
	@rm -f tests/test_quote_handling

.PHONY: all re clean fclean val readline.supp test test_quotes