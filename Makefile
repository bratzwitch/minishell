NAME = minishell

CFLAGS = -Wall -Wextra -Werror 

LIBFT = ./lib_ft

SRC =	minishell.c
			

OBJS = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
		@echo "Compiling this crap"
		cc $(CFLAGS) $(OBJS) -lreadline -lncurses -o  $(NAME)
		@echo "All good you can rest(no)"
clean:
		$(RM) $(OBJS)

fclean:	clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

.SILENT: