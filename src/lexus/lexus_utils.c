#include "../../include/minishell.h"

bool ft_isspace(const char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

bool ft_is_special_character(const char *current)
{
	return (*current == '<' || *current == '>' || *current == '|' ||
			strncmp(current, "<<", 2) == 0 || strncmp(current, ">>", 2) == 0); // original ft, dont forget to replace
}
