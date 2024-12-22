NAME = minishell
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
RM = rm -f
LIBFT = ./libft
SRC_DIR = ./src
LEXER_DIR = ./src/lexus

SRC =	$(SRC_DIR)/commands.c \
		$(SRC_DIR)/input.c \
		$(SRC_DIR)/minishell.c \
		$(SRC_DIR)/signal.c \
		$(SRC_DIR)/utils.c	\
		$(LEXER_DIR)/lexer.c \
		$(LEXER_DIR)/lexus_utils.c \
		$(LEXER_DIR)/operators.c \
		$(LEXER_DIR)/tokenise.c \
		$(LEXER_DIR)/dollar.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		@echo "Compiling this crap"
		@make -C $(LIBFT)  && make clean -C $(LIBFT)
		cc $(CFLAGS) $(OBJS) -lreadline -lncurses -o $(NAME) ./libft/libft.a 
		@echo "All good you can rest(no)"
clean:
		$(RM) $(OBJS)

fclean:	clean
		@make fclean -C $(LIBFT)
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: