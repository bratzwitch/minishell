#include "../../include/minishell.h"

char *append_to_final_str(char *final_str, const char *start, size_t len)
{
    char *new_str;
    size_t old_len;

    old_len = ft_strlen(final_str);
    new_str = malloc(old_len + len + 1);
    if (!new_str)
        return (NULL);
    strcpy(new_str, final_str);
    strncat(new_str, start, len);
    free(final_str);
    return (new_str);
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

char *handle_double_quote(char **input, char *final_str)
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
