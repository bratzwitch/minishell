NAME := minishell
# For Mac:
# CFLAGS := -Wall -Wextra -Werror -g -fPIE -I/opt/homebrew/opt/readline/include
# LDFLAGS := -L/opt/homebrew/opt/readline/lib -lreadline -lncurses
CFLAGS := -Wall -Wextra -Werror -fPIE -g
LDFLAGS := -lreadline -lncurses
CC := cc
RM := rm -f
LIBFT_DIR := ./libft
SRC_DIR := ./src
LEXER_DIR := ./src/lexus
EXEC_DIR := ./src/execute
		
SRC :=	$(SRC_DIR)/minishell.c \
		$(SRC_DIR)/processes.c \
		$(SRC_DIR)/redirections.c \
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/pipe_utils.c \
		$(SRC_DIR)/piping.c \
		$(SRC_DIR)/utils.c \
		$(LEXER_DIR)/dollar.c \
		$(LEXER_DIR)/lexer.c \
		$(LEXER_DIR)/lexus_utils.c \
		$(LEXER_DIR)/operators.c \
		$(LEXER_DIR)/tokenise.c \
		$(EXEC_DIR)/builtins.c \
		$(EXEC_DIR)/execute.c \
		$(EXEC_DIR)/builtins/cd.c \
		$(EXEC_DIR)/builtins/echo.c \
		$(EXEC_DIR)/builtins/env_pwd_exit.c \
		$(EXEC_DIR)/builtins/export.c \
		$(EXEC_DIR)/builtins/unset.c

OBJS := $(SRC:.c=.o)

all: $(NAME)

go:
	valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=minishell.supp ./minishell

$(NAME): $(OBJS)
		@echo "Compiling this crap"
		@make -C $(LIBFT_DIR)
		$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBFT_DIR)/libft.a
		@echo "All good you can rest(no)" 
		@echo "  ⣿⣿⣿⣿⣿⣿⣿⠿⠿⢛⣋⣙⣋⣩⣭⣭⣭⣭⣍⣉⡛⠻⢿⣿⣿⣿⣿"
		@echo "  ⣿⣿⣿⠟⣋⣥⣴⣾⣿⣿⣿⡆⣿⣿⣿⣿⣿⣿⡿⠟⠛⠗⢦⡙⢿⣿⣿ "
		@echo "  ⣿⡟⡡⠾⠛⠻⢿⣿⣿⣿⡿⠃⣿⡿⣿⠿⠛⠉⠠⠴⢶⡜⣦⡀⡈⢿⣿ "
		@echo "  ⡿⢀⣰⡏⣼⠋⠁⢲⡌⢤⣠⣾⣷⡄⢄⠠⡶⣾⡀⠀⣸⡷⢸⡷⢹⠈⣿ "
		@echo "  ⡇⢘⢿⣇⢻⣤⣠⡼⢃⣤⣾⣿⣿⣿⢌⣷⣅⡘⠻⠿⢛⣡⣿⠀⣾⢠⣿ "
		@echo "  ⣷⠸⣮⣿⣷⣨⣥⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⢁⡼⠃⣼⣿ "
		@echo "  ⡟⠛⠛⠛⣿⠛⠛⢻⡟⠛⠛⢿⡟⠛⠛⡿⢻⡿⠛⡛⢻⣿⠛⡟⠛⠛⢿ "
		@echo "  ⡇⢸⣿⠀⣿⠀⠛⢻⡇⠸⠃⢸⡇⠛⢛⡇⠘⠃⢼⣷⡀⠃⣰⡇⠸⠇⢸ "
		@echo "  ⡇⢸⣿⠀⣿⠀⠛⢻⡇⢰⣿⣿⡇⠛⠛⣇⢸⣧⠈⣟⠃⣠⣿⡇⢰⣾⣿ "
		@echo "  ⣿⣿⣿⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢋⣿⠙⣷⢸⣷⠀⣿⣿⣿ "
		@echo "  ⣿⣿⣿⡇⢻⣿⣿⣿⡿⠿⢿⣿⣿⣿⠟⠋⣡⡈⠻⣇⢹⣿⣿⢠⣿⣿⣿ "
		@echo "  ⣿⣿⣿⣿⠘⣿⣿⣿⣿⣯⣽⣉⣿⣟⣛⠷⠙⢿⣷⣌⠀⢿⡇⣼⣿⣿⣿ "
		@echo "  ⣿⣿⣿⡿⢀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣤⡙⢿⢗⣀⣁⠈⢻⣿⣿ "
		@echo "  ⣿⡿⢋⣴⣿⣎⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡉⣯⣿⣷⠆⠙⢿ "
		@echo "  ⣏⠀⠈⠧⠡⠉⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠉⢉⣁⣀⣀⣾ "
clean:
		@make clean -C $(LIBFT_DIR)
		@$(RM) $(OBJS)

fclean:	clean
		@make fclean -C $(LIBFT_DIR)
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: $(NAME) $(OBJS)

# explanations to the assignment operators:
# 	1. = (Simple Assignment):
# 		The value is expanded every time the variable is used.
# 	2. := (Immediate Assignment):
# 		The value is expanded immediately when the variable is defined.
# 	3. ?= (Conditional Assignment):
# 		The value is assigned only if the variable is not already defined.
# 	4. += (Append Assignment):
# 		The value is appended to the existing value of the variable.

# why does Makefile compiles the files with and without specifying "all"?
# 	When you run make without specifying a target,
# 	make uses the first target defined in the Makefile as the default target.