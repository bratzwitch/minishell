NAME := minishell
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
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/pipe_utils.c \
		$(SRC_DIR)/piping.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/utils2.c \
		$(SRC_DIR)/utils3.c \
		$(SRC_DIR)/validate.c \
		$(LEXER_DIR)/dollar.c \
		$(LEXER_DIR)/lexer.c \
		$(LEXER_DIR)/lexus_utils.c \
		$(LEXER_DIR)/operators.c \
		$(LEXER_DIR)/quotes.c \
		$(LEXER_DIR)/handles.c \
		$(LEXER_DIR)/tokenise.c \
		$(EXEC_DIR)/builtins.c \
		$(EXEC_DIR)/execute.c \
		$(EXEC_DIR)/heredoc.c \
		$(EXEC_DIR)/redirections.c \
		$(EXEC_DIR)/redir_handlers.c \
		$(EXEC_DIR)/exec_utils.c \
		$(EXEC_DIR)/builtins/cd.c \
		$(EXEC_DIR)/builtins/echo.c \
		$(EXEC_DIR)/builtins/env_pwd_exit.c \
		$(EXEC_DIR)/builtins/export_utils.c \
		$(EXEC_DIR)/builtins/export.c \
		$(EXEC_DIR)/builtins/unset.c

OBJS := $(SRC:.c=.o)

all: $(NAME)

go:
	valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --show-reachable=yes --error-limit=no --suppressions=minishell.supp ./minishell

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