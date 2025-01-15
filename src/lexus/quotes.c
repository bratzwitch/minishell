#include "../../include/minishell.h"

char *append_to_final_str(char *final_str, const char *start, size_t len)
{
    char *token_value;
    char *temp;

    token_value = strndup(start, len);
    temp = ft_strjoin(final_str, token_value);
    free(token_value);
    free(final_str);
    return (temp);
}

char *handle_single_quotes(char **input, char *final_str)
{
    char *current = *input + 1;
    char *start = current;

    while (*current && *current != '\'')
        current++;
    if (*current != '\'')
    {
        printf("Unmatched single quote detected.\n");
        free(final_str);
        return (NULL);
    }
    final_str = append_to_final_str(final_str, start, current - start);
    *input = current + 1;
    return (final_str);
}

char *process_double_quote(char **input, char *final_str)
{
    char *current = *input + 1;
    char *start = current;

    while (*current && *current != '\"')
    {
        if (*current == '$')
        {
            final_str = dollar(&current, final_str, &start);
            if (!final_str)
                return (NULL);
        }
        else
            current++;
    }
    if (*current != '\"')
    {
        printf("Unmatched double quote detected.\n");
        free(final_str);
        return (NULL);
    }
    final_str = append_to_final_str(final_str, start, current - start);
    *input = current + 1;
    return (final_str);
}
